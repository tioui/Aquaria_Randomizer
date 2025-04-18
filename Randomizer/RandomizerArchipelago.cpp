/**
 * @author      : Louis M (prog@tioui.com)
 * @created     : Fri, 08 Mar 2024 19:51:46 +0000
 * @license     : MIT
 * Class that encapsulate Archipelago server randomization
*/
#include "RandomizerArchipelago.h"
#include "subprojects/apclientpp/apclient.hpp"
#include "subprojects/apclientpp/apuuid.hpp"
#include "../Aquaria/Avatar.h"
#include "../Aquaria/Game.h"
#include "../Aquaria/DSQ.h"

#define AP_VERSION_SUPPORT {0,5,1}
#define AP_BASE 698000
#define ITEM_INDEX_FLAG 1399

typedef enum APItemType {
    TRASH = -1,
    PROGRESSION = -2,
    USEFULL = -3,
    TRAP = -5
} APItemType;

/**
 * Base constructor
 */
RandomizerArchipelago::RandomizerArchipelago(): Randomizer(){
    name = "";
    password = "";
    serverAddress = "";
    selfMessageOnly = false;
    noChatMessage = false;
    hasBeenDisconnected = false;
    hasRoomInfo = false;
    hasSlotInfo = false;
    syncing = false;
    secretsNeeded = false;
    deathLink = false;
    isOffline = true;
    betweenState = false;
    currentQuickMessageTime = 0;
    deathLinkPause = false;
    apClient = nullptr;
    throneAsLocationManagedByServer = false;
    golemAsLocationManagedByServer = false;
    clearError();
    nextQuickMessages = new std::queue<std::string>();
    serverTexts = new std::vector<serverText_t *>();
    dataStorageInfo = new std::unordered_map<std::string, int>;
    initialisedDataStorageInfo();
    lastArea = "";
    areaInfo = new std::unordered_map<std::string, std::string>;
    initialiseAreaInfo();
    apItems = new std::vector<apitem_t>();
    locationsItemTypes = new std::vector<int>();
    initialiseApItems();
    apLocations = new std::vector<aplocation_t>();
    initialiseApLocations();
}

/**
 * Constructor that does not connect to a server
 * @param aSeedNumberPlayerName The seed number and the player name of the game
 */
RandomizerArchipelago::RandomizerArchipelago(std::string aSeedNumberPlayerName): RandomizerArchipelago(){
    int lSeparator = aSeedNumberPlayerName.find("_");
    if (lSeparator != std::string::npos) {
        setUid(aSeedNumberPlayerName.substr(0, lSeparator));
        name = aSeedNumberPlayerName.substr(lSeparator + 1, std::string::npos);
    } else {
        setError("Missing separator between the seed number and the user name.");
    }

}

/**
 * Extract the hostname from a complete server address (aka remove the port number).
 *
 * For example, if the server address is "archipelago.gg:12345", the return will be "archipelago.gg"
 *
 * @param aServer The server address (with or without the port number)
 * @return The server hostname without the port number
 */
std::string extractHostname(const std::string &aServer) {
    unsigned long lEndPosition = aServer.find(":");
    std::string lResult;
    if (lEndPosition != std::string::npos && lEndPosition > 0) {
        lResult = aServer.substr(0, lEndPosition);
    } else {
        lResult = aServer;
    }
    return lResult;
}

/**
 * Constructor that connect to an Archipelago server
 * @param aServer The address and port of the Archipelago server
 * @param aName The player name on the archipelago server
 * @param aPassword The password of the room on the archipelago server
 * @param aSelfMessage the user want only server message for or from himself.
 * @param aNoChat The user don't want any chat message from server.
 * @param aDeathLink True if Archipelago Death link packets should be used.
 * @param aUserDataFolder The data to store user informations.
 */
RandomizerArchipelago::RandomizerArchipelago(const std::string& aServer, const std::string& aName,
                                             const std::string& aPassword, bool aSelfMessage,
                                             bool aNoChat, bool aDeathLink,
                                             std::string aUserDataFolder): RandomizerArchipelago(){
    name = aName;
    password = aPassword;
    serverAddress = aServer;
    selfMessageOnly = aSelfMessage;
    syncing = true;
    deathLink = aDeathLink;
    isOffline = false;
    noChatMessage = aNoChat;
    std::string lHostname = extractHostname(aServer);
    uuid = ap_get_uuid(aUserDataFolder + "/uuid.dat", lHostname);
    tryConnection(aServer);
    if (hasRoomInfo && hasSlotInfo) {
        std::cout << "Seed number:" << apClient->get_seed() << std::endl;
        setUid(apClient->get_seed());
    } else {
        if (!hasError()) {
            setError("Connection failed!");
        }
    }
}


/**
 * Try to connect to the server (try secure and not secure unless specified)
 *
 * @param server The server URI (including port number
 */
void RandomizerArchipelago::tryConnection(const std::string& aServer) {
    bool mustRetry = true;
    std::string lcacert = "cacert.pem";
    std::string lServer = aServer;
    std::transform(lServer.begin(), lServer.end(), lServer.begin(), ::tolower);
    if (lServer.compare(0, 6, "wss://") == 0 || lServer.compare(0, 5, "ws://") == 0) {
        mustRetry = false;
    } else {
        lServer = "wss://" + aServer;
    }
    bool timeOut = false;
    serverAddress = lServer;
    hasRoomInfo = false;
    hasSlotInfo = false;
    clearError();
    const char *appAppImageMountDir = getenv("APPDIR");
    if (appAppImageMountDir) {
        lcacert = "/usr/share/cacert.pem";
        lcacert.insert(0, appAppImageMountDir);
    }
    apClient = new APClient(uuid, "Aquaria",lServer, lcacert);
    initialiseCallback();
    std::chrono::time_point lStart = std::chrono::system_clock::now();
    while (!(hasRoomInfo && hasSlotInfo) && !hasError() && !timeOut) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        apClient->poll();
        std::chrono::time_point lNow = std::chrono::system_clock::now();
        auto lDuration = std::chrono::duration_cast<std::chrono::seconds>(lNow - lStart);
        timeOut = lDuration.count() > 5;
    }
    if (hasError() && mustRetry) {
        tryConnection("ws://" + aServer);
    }
}

/**
 * Destructor of the current object
 */
RandomizerArchipelago::~RandomizerArchipelago(){
    emptyServerText();
    delete(serverTexts);
    delete(apClient);
    delete(apLocations);
    delete(apItems);
}

/**
 * Set every APClient callback
 */
void RandomizerArchipelago::initialiseCallback(){
    apClient->set_socket_connected_handler([&](){
        onSocketConnected();
    });
    apClient->set_socket_disconnected_handler([&](){
        onSocketDisconnected();
    });
    apClient->set_socket_error_handler([&](const std::string& aText){
        onSockerError(aText);
    });
    apClient->set_room_info_handler([&](){
        onRoomInfoHandler();
    });
    apClient->set_slot_connected_handler([&](const nlohmann::json& aJsonText){
        onSlotConnected(aJsonText);
    });
    apClient->set_slot_refused_handler([&](const std::list<std::string>& aTexts){
        onSlotRefused(aTexts);
    });
    apClient->set_items_received_handler([&](const std::list<APClient::NetworkItem>& aItems){
        onItemsReceived(aItems);
    });
    apClient->set_print_json_handler([&](const APClient::PrintJSONArgs& aJson){
        onPrintJson(aJson);
    });
    apClient->set_bounced_handler([&](const nlohmann::json& aJson){
        onBounceMessageReceived(aJson);
    });
    apClient->set_location_info_handler([&](const std::list<APClient::NetworkItem>& aItems){
        onLocationInfo(aItems);
    });
    apClient->set_retrieved_handler([&](const std::map<std::string,nlohmann::json>& aMap){
        onDataStorageRetreived(aMap);
    });
}

/**
 * Launched when the socket has been connected to the Archipelago server
 */
void RandomizerArchipelago::onSocketConnected(){
    connected = true;
}

/**
 * Launched when a data storage retreive message has been received.
 * @param aMap Contain the key and json value in the datas torage
 */
void RandomizerArchipelago::onDataStorageRetreived(const std::map<std::string,nlohmann::json>& aMap) {
    for (const auto& aPair : aMap) {
        if (!aPair.second.is_null()) {
            unsigned long lIdPosition = aPair.first.find("@");
            if (lIdPosition != std::string::npos) {
                std::string lId = aPair.first.substr(lIdPosition + 1, std::string::npos);
                auto lMap = dataStorageInfo->find(lId);
                if (lMap != dataStorageInfo->end()) {
                    int lValue = aPair.second.at(0);
                    lMap->second = lValue;
                }
            }
        }
    }
}

/**
 * Launched when the socket has been disconnected to the Archipelago server
 */
void RandomizerArchipelago::onSocketDisconnected(){
    connected = false;
}

/**
 * Launched when a socket error is detected.
 * \param aText The error message
 */
void RandomizerArchipelago::onSockerError (const std::string& aText) {
    setError(aText);
}

/**
 * Launched when a connection to an archipelago slot has been refused
 * \param aTexts Every text message
 */
void RandomizerArchipelago::onSlotRefused (const std::list<std::string>& aTexts){
    std::stringstream lMessageStream;
    bool first = true;
    lMessageStream << "Connection to slot refused: ";
    for (std::string lText : aTexts) {
        if (first) {
            first = false;
        } else {
            lMessageStream << "; ";
        }
        lMessageStream << lText;
    }

    setError(lMessageStream.str());
}

/**
 * Launched when the the Archipelago send Room Info message
 */
void RandomizerArchipelago::onRoomInfoHandler(){
    std::list<std::string> tags;
    if (deathLink) {
        tags.emplace_back("DeathLink");
    }
    if (inGame) {
        const int item_handling_flags_all = 7;
        apClient->ConnectSlot(name, password, item_handling_flags_all, tags, AP_VERSION_SUPPORT);
    } else {
        apClient->ConnectSlot(name, password, 0,
                              tags, AP_VERSION_SUPPORT);
    }
    hasRoomInfo = true;
}

/**
 * Initialise the goal options
 *
 * @param jsonText The "slot_data" json file
 */
void RandomizerArchipelago::initialiseGoal(const nlohmann::json& aJsonText) {
    if (aJsonText.contains("goal")) {
        if (aJsonText["goal"] == 1) {
            secretsNeeded = true;
            killCreatorGoal = true;
            killFourGodsGoal = false;
        } else if (aJsonText["goal"] == 2) {
            secretsNeeded = false;
            killCreatorGoal = false;
            killFourGodsGoal = true;
        } else if (aJsonText["goal"] == 3) {
            secretsNeeded = false;
            killCreatorGoal = true;
            killFourGodsGoal = true;
        } else {
            secretsNeeded = false;
            killCreatorGoal = true;
            killFourGodsGoal = false;
        }
    }
    if (aJsonText.contains("secret_needed")) {
        secretsNeeded = aJsonText["secret_needed"];
    }
    if (aJsonText.contains("kill_creator_goal")) {
        killCreatorGoal = aJsonText["kill_creator_goal"];
    }
    if (aJsonText.contains("four_gods_goal")) {
        killFourGodsGoal = aJsonText["four_gods_goal"];
    }
    if (aJsonText.contains("minibosses_to_kill")) {
        miniBossesToKill = aJsonText["minibosses_to_kill"];
    }
    if (aJsonText.contains("bigbosses_to_kill")) {
        bigBossesToKill = aJsonText["bigbosses_to_kill"];
    }
}

/**
 * Initialise the standard options
 *
 * @param jsonText The "slot_data" json file
 */
void RandomizerArchipelago::initialiseOptions(const nlohmann::json& aJsonText) {
    int lAquarianTranslated = false;
    int lBlindGoal = false;
    std::list<int64_t> locationsId;
    if (aJsonText.contains("aquarian_translate")) {
        lAquarianTranslated = aJsonText["aquarian_translate"];
        setIsAquarianTranslated(lAquarianTranslated);
    } else if (aJsonText.contains("aquarianTranslate")){ // To remove when the PR 3533 has been accepted
        lAquarianTranslated = aJsonText["aquarianTranslate"];
        setIsAquarianTranslated(lAquarianTranslated);
    }
    if (aJsonText.contains("skip_first_vision")) {
        skipFirstVision = aJsonText["skip_first_vision"];
    }
    if (aJsonText.contains("skip_final_boss_3rd_form")) {
        skipFinalBoss3rdForm = aJsonText["skip_final_boss_3rd_form"];
    }
    if (aJsonText.contains("infinite_hot_soup")) {
        infiniteHotSoup = aJsonText["infinite_hot_soup"];
    }
    if (aJsonText.contains("unconfine_home_water_energy_door")) {
        unconfine_home_water_energy_door = aJsonText["unconfine_home_water_energy_door"];
    }
    if (aJsonText.contains("unconfine_home_water_transturtle")) {
        unconfine_home_water_transturtle = aJsonText["unconfine_home_water_transturtle"];
    }
    if (aJsonText.contains("maximum_ingredient_amount")) {
        maximumIngredientAmount = aJsonText["maximum_ingredient_amount"];
    }
    if (aJsonText.contains("open_body_tongue")) {
        removeTongue = aJsonText["open_body_tongue"];
    }
    if (aJsonText.contains("throne_as_location")) {
        throneAsLocationManagedByServer = true;
    }
    if (aJsonText.contains("golem_as_location")) {
        golemAsLocationManagedByServer = true;
    }
    if (aJsonText.contains("blind_goal")) {
        lBlindGoal = aJsonText["blind_goal"];
        setBlindGoal(lBlindGoal);
    } else if (aJsonText.contains("blindGoal")) { // To remove when the PR 3533 has been accepted
        lBlindGoal = aJsonText["blindGoal"];
        setBlindGoal(lBlindGoal);
    }
    if (aJsonText.contains("save_healing")) {
        bool lSaveHeal = aJsonText["save_healing"];
        setSaveHeal(lSaveHeal);
    }
    ingredientReplacement->clear();
    for (int lElement : aJsonText["ingredientReplacement"]) {
        ingredientReplacement->push_back(lElement);
    }
    locationsItemTypes->clear();
    for (int i = 0; i < apLocations->size(); i = i + 1) {
        if (killFourGodsGoal) {
            bool lIndexFound = false;
            for (int j = 0; !lIndexFound && j < LOCATIONS_FOUR_GODS_SIZE; j = j + 1) {
                if (i == locationsOrderFourGods[j]) {
                    lIndexFound = true;
                }
            }
            if (lIndexFound) {
                locationsId.push_back(i + AP_BASE);
                locationsItemTypes->push_back(USEFULL);
            } else {
                locationsItemTypes->push_back(TRASH);
            }
        } else {
            locationsId.push_back(i + AP_BASE);
            locationsItemTypes->push_back(USEFULL);
        }
    }
    apClient->LocationScouts(locationsId);
}

/**
 * Launched when a slot has been connected.
 * @param aJsonText The "slot_data" json file
 */
void RandomizerArchipelago::onSlotConnected (const nlohmann::json& aJsonText){
    if (!hasSlotInfo) {
        hasSlotInfo = true;
        bool is_valid_version = true;
        std::string ldump = aJsonText.dump();
        if (aJsonText.contains("required_client_version")) {
            std::vector<int> *lVersion = new std::vector<int>();
            for (int lElement : aJsonText["required_client_version"]) {
                lVersion->push_back(lElement);
            }
            if (lVersion->size() >= 3) {
                int lVersionMajor = lVersion->at(0);
                int lVersionMinor = lVersion->at(1);
                int lVersionRevision = lVersion->at(2);
                if (
                        lVersionMajor > VERSION_MAJOR ||
                        (lVersionMajor == VERSION_MAJOR && lVersionMinor > VERSION_MINOR) ||
                        (lVersionMajor == VERSION_MAJOR && lVersionMinor == VERSION_MINOR &&
                            lVersionRevision > VERSION_REVISION)) {
                    std::stringstream lError;
                    lError << "This client does not support the world. Please update the client to version ";
                    lError << lVersionMajor << "." << lVersionMinor << "." << lVersionRevision << "\n";
                    setError(lError.str());
                    is_valid_version = false;
                }
            }
            free(lVersion);
        }
        if (is_valid_version) {
            initialiseGoal(aJsonText);
            initialiseOptions(aJsonText);
            updateDataStorageInfo();
        }
    }
}
/**
 * A reply to an AP location scout message
 * @param aItems Every items that has been scout
 */
void RandomizerArchipelago::onLocationInfo(const std::list<APClient::NetworkItem>& aItems) {
    for (APClient::NetworkItem lItem : aItems) {
        if (lItem.player == apClient->get_player_number()) {
            locationsItemTypes->at(lItem.location - AP_BASE) = lItem.item;
        } else {
            locationsItemTypes->at(lItem.location - AP_BASE) = -(static_cast<int>(lItem.flags) + 1);
        }
    }
}

/**
 * Save information about the Archipelago slot. Usefull if the user want to play offline.
 */
void RandomizerArchipelago::saveConnectionInfo() {
    dsq->continuity.setFlag(FLAG_SAVE_HAS_INFO, 1);
    dsq->continuity.setFlag(FLAG_SAVE_AQUARIAN_TRANSLATE, getIsAquarianTranslated());
    dsq->continuity.setFlag(FLAG_SAVE_SECRET_NEEDED, secretsNeeded);
    dsq->continuity.setFlag(FLAG_SAVE_MINI_BOSSES_TO_KILLED, miniBossesToKill);
    dsq->continuity.setFlag(FLAG_SAVE_BIG_BOSSES_TO_KILLED, bigBossesToKill);
    dsq->continuity.setFlag(FLAG_SAVE_INFINITE_HOT_SOUP, infiniteHotSoup);
    dsq->continuity.setFlag(FLAG_SAVE_MAX_INGREDIENTS_AMOUNT, maximumIngredientAmount);
    dsq->continuity.setFlag(FLAG_SAVE_RANDOMIZED_INGREDIENTS_SIZE, ingredientReplacement->size());
    for (int i = 0; i < ingredientReplacement->size() || i > FLAG_SAVE_RANDOMIZED_INGREDIENTS_END; i = i + 1) {
        dsq->continuity.setFlag(FLAG_SAVE_RANDOMIZED_INGREDIENTS_START + i, ingredientReplacement->at(i));
    }
    dsq->continuity.setFlag(FLAG_SAVE_LOCATION_ITEM_TYPES_SIZE, locationsItemTypes->size());
    for (int i = 0; i < locationsItemTypes->size() || i > FLAG_SAVE_LOCATION_ITEM_TYPES_END; i = i + 1) {
        dsq->continuity.setFlag(FLAG_SAVE_LOCATION_ITEM_TYPES_START + i, locationsItemTypes->at(i));
    }
}

/**
 * Save information about the Archipelago slot. Usefull if the user want to play offline.
 */
void RandomizerArchipelago::loadConnectionInfo() {
    setIsAquarianTranslated(dsq->continuity.getFlag(FLAG_SAVE_AQUARIAN_TRANSLATE));
    secretsNeeded = dsq->continuity.getFlag(FLAG_SAVE_SECRET_NEEDED);
    miniBossesToKill = dsq->continuity.getFlag(FLAG_SAVE_MINI_BOSSES_TO_KILLED);
	bigBossesToKill = dsq->continuity.getFlag(FLAG_SAVE_BIG_BOSSES_TO_KILLED);
	infiniteHotSoup = dsq->continuity.getFlag(FLAG_SAVE_INFINITE_HOT_SOUP);
	maximumIngredientAmount = dsq->continuity.getFlag(FLAG_SAVE_MAX_INGREDIENTS_AMOUNT);
	ingredientReplacement->clear();
    for (int i = 0; i < dsq->continuity.getFlag(FLAG_SAVE_RANDOMIZED_INGREDIENTS_SIZE); i = i + 1) {
        ingredientReplacement->push_back(dsq->continuity.getFlag(FLAG_SAVE_RANDOMIZED_INGREDIENTS_START + i));
    }
    locationsItemTypes->clear();
    for (int i = 0; i < dsq->continuity.getFlag(FLAG_SAVE_LOCATION_ITEM_TYPES_SIZE); i = i + 1) {
        locationsItemTypes->push_back(dsq->continuity.getFlag(FLAG_SAVE_LOCATION_ITEM_TYPES_START + i));
    }
}

/**
 * Launched when the Archipelago send a new item to receive
 * @param aItems A list of item to received
 */
void RandomizerArchipelago::onItemsReceived (const std::list<APClient::NetworkItem>& aItems){
    for (APClient::NetworkItem lItem : aItems) {
        if (lItem.index > dsq->continuity.getFlag(ITEM_INDEX_FLAG)) {
            apClient->Sync();
            syncing = true;
        } else if (lItem.index == dsq->continuity.getFlag(ITEM_INDEX_FLAG)) {
            apitem_t *lApItem = getApItemById(lItem.item);
            receivingItem(lApItem->item, lApItem->count);
            dsq->continuity.setFlag(ITEM_INDEX_FLAG, lItem.index + 1);
        }
    }
}


/**
 * Launched when the Archipelago send some new message th show
 * @param aJson The message th show
 */
void RandomizerArchipelago::onPrintJson (const APClient::PrintJSONArgs& aJson){
    if (inGame && (aJson.type != "Tutorial")) {
        if (aJson.type != "ItemSend" || !selfMessageOnly || selfRelatedJson(aJson.data)) {
            if (!noChatMessage || (aJson.type != "Chat" && aJson.type != "Goal" && aJson.type != "Collect" &&
                aJson.type != "Release" && aJson.type != "Join" && aJson.type != "Part" &&
                (aJson.type != "Hint" || selfRelatedJson(aJson.data)) && aJson.type != "TagsChanged" &&
                aJson.type != "CommandResult" && aJson.type != "AdminCommandResult")) {
                std::vector<serverSegmentTextInfo_t *> *lSegments = new std::vector<serverSegmentTextInfo_t *>();
                for (const APClient::TextNode& lNode : aJson.data) {
                    serverSegmentTextInfo_t *lSegment = new serverSegmentTextInfo_t;
                    if (lNode.type == "player_id") {
                        int lPlayerId = std::stoi(lNode.text);
                        lSegment->text = apClient->get_player_alias(lPlayerId);
                        if (apClient->get_player_number() == lPlayerId) {
                            lSegment->color = SERVER_TEXT_COLOR_USER;
                        } else {
                            lSegment->color = SERVER_TEXT_COLOR_NORMAL;
                        }
                    } else if(lNode.type == "item_id") {
                        lSegment->text = apClient->get_item_name(std::stoi(lNode.text),
                            apClient->get_player_game(lNode.player));
                        if (lNode.flags == 1) {
                            lSegment->color = SERVER_TEXT_COLOR_PROGRESSION_ITEM;
                        } else if (lNode.flags == 2) {
                            lSegment->color = SERVER_TEXT_COLOR_USEFUL_ITEM;
                        } else if (lNode.flags == 4) {
                            lSegment->color = SERVER_TEXT_COLOR_TRAP_ITEM;
                        } else {
                            lSegment->color = SERVER_TEXT_COLOR_FILLER_ITEM;
                        }
                    } else if(lNode.type == "location_id") {
                        lSegment->text = apClient->get_location_name(std::stoi(lNode.text),
                            apClient->get_player_game(lNode.player));
                        lSegment->color = SERVER_TEXT_COLOR_LOCATION;
                    } else if (lNode.type == "hint_status") {
                        lSegment->text = lNode.text;
                        if (lNode.text == "(priority)") {
                            lSegment->color = SERVER_TEXT_COLOR_PROGRESSION_ITEM;
                        } else if (lNode.text == "(not found)") {
                            lSegment->color = SERVER_TEXT_COLOR_LOCATION_NOT_FOUND;
                        } else if (lNode.text == "(found)") {
                            lSegment->color = SERVER_TEXT_COLOR_LOCATION_FOUND;
                        } else {
                            lSegment->text = lNode.text;
                            lSegment->color = SERVER_TEXT_COLOR_NORMAL;
                        }
                    } else {
                        lSegment->text = lNode.text;
                        lSegment->color = SERVER_TEXT_COLOR_NORMAL;
                    }
                    lSegments->push_back(lSegment);
                }
                printServerText(lSegments);
            }
        }
    }
}

/**
 * Create the visual element of a server text
 * @param aServerText The information of the server text
 */
void RandomizerArchipelago::createServerTextRenderObjects(serverText_t *aServerText) {
    int width = 10;
    aServerText->shown = false;
    aServerText->height = 1;
    for (int i = 0; i < aServerText->segmentInfos->size(); i = i + 1) {
        TTFText *lText = new TTFText(&dsq->fontArialSmallest);
        lText->setText(aServerText->segmentInfos->at(i)->text);
        lText->followCamera = 1;
        if (aServerText->segmentInfos->at(i)->color == SERVER_TEXT_COLOR_USER) {
            lText->color = Vector(1.0, 0.0, 1.0);
        } else if (aServerText->segmentInfos->at(i)->color == SERVER_TEXT_COLOR_LOCATION) {
            lText->color = Vector(0.0, 1.0, 0.0);
        } else if (aServerText->segmentInfos->at(i)->color == SERVER_TEXT_COLOR_TRAP_ITEM) {
            lText->color = Vector(0.5, 0.5, 0.5);
        }else if (aServerText->segmentInfos->at(i)->color == SERVER_TEXT_COLOR_USEFUL_ITEM) {
            lText->color = Vector(0.0, 0.80, 0.80);
        } else if (aServerText->segmentInfos->at(i)->color == SERVER_TEXT_COLOR_PROGRESSION_ITEM) {
            lText->color = Vector(0.5, 0.60, 0.80);
        } else {
            lText->color = Vector(1.0, 1.0, 1.0);
        }
        serverSegmentText_t *lSegment = new serverSegmentText_t;
        lSegment->text = lText;
        lSegment->width = lText->getStringWidth(aServerText->segmentInfos->at(i)->text);
        if (aServerText->segmentInfos->at(i)->text.at(aServerText->segmentInfos->at(i)->text.size() - 1) == ' ') {
            lSegment->width = lSegment->width + 5.0f;
        }
        if (i < aServerText->segmentInfos->size() - 1 && aServerText->segmentInfos->at(i + 1)->text.at(0) == ' ') {
            lSegment->width = lSegment->width + 5.0f;
        }
        if (aServerText->height < lText->getHeight()) {
            aServerText->height = lText->getHeight();
        }
        width = width + lSegment->width;
        aServerText->segments.push_back(lSegment);
    }
    Quad *lBack = new Quad();
    lBack->color = Vector(0.0, 0.0, 0.0);
    lBack->alpha = 0.6f;
    lBack->setWidthHeight(width, aServerText->height);
    lBack->position = Vector(50.0f + (width / 2), 0.0f);
    lBack->followCamera = 1;
    dsq->getTopStateData()->addRenderObject(lBack, LR_SERVER_TEXT);

    aServerText->background = lBack;
}

/**
 * Print some line segments back to back to make a complete line
 * @param aSegments The segments to print as a line
 */
void RandomizerArchipelago::printServerText(std::vector<serverSegmentTextInfo_t *> *aSegments) {
    serverText_t *lServerText = new serverText_t;
    lServerText->segmentInfos = aSegments;
    auto lNow = std::chrono::system_clock::now();
    lServerText->time = std::chrono::system_clock::to_time_t(lNow);
    if (serverTexts->size() > 0 &&
        serverTexts->at(serverTexts->size() - PRINT_SERVER_TEXT_BETWEEN_DELAY)->time + 1 > lServerText->time) {
        lServerText->time = serverTexts->at(serverTexts->size() - PRINT_SERVER_TEXT_BETWEEN_DELAY)->time + 1;
    }
    if (!betweenState) {
        createServerTextRenderObjects(lServerText);
    }

    serverTexts->push_back(lServerText);
}

void RandomizerArchipelago::updatePrintServerText() {
    if (!betweenState) {
        for (std::vector<serverText_t *>::iterator lIterator = serverTexts->begin(); lIterator != serverTexts->end();) {
            auto lNow = std::chrono::system_clock::now();
            auto lTime = std::chrono::system_clock::from_time_t ((*lIterator)->time);
            auto lDuration = std::chrono::duration_cast<std::chrono::seconds>(lNow - lTime);
            if (lDuration.count() > PRINT_SERVER_TEXT_DELAY) {
                for (std::vector<serverSegmentText_t *>::iterator lSegment = (*lIterator)->segments.begin(); lSegment != (*lIterator)->segments.end();) {
                    if ((*lSegment)->text != nullptr) {
                        (*lSegment)->text->safeKill();
                        (*lSegment)->text = nullptr;
                    }
                    delete(*lSegment);
                    (*lIterator)->segments.erase(lSegment);
                }
                if ((*lIterator)->background != nullptr) {
                    (*lIterator)->background->safeKill();
                    (*lIterator)->background = nullptr;
                }
                serverTexts->erase(lIterator);
            } else {
                ++lIterator;
            }
        }
        int serverTextsSize = serverTexts->size();
        for (int i = 0; i < std::min(serverTextsSize, 5); i = i + 1) {
            float y = 550.0f - (i * 20.0f);
            float x = 50.0f;
            if (serverTexts->at(i)->background != nullptr) {
                serverTexts->at(i)->background->position = Vector(serverTexts->at(i)->background->position.x,
                        y - 2.0f);
            }
            for (auto & lSegment : (*serverTexts)[i]->segments) {
                if (lSegment->text != nullptr) {
                    lSegment->text->position = Vector(x, y);
                    x = x + lSegment->width;
                    if (!serverTexts->at(i)->shown) {
                        dsq->getTopStateData()->addRenderObject(lSegment->text, LR_SERVER_TEXT);
                    }
                }
            }
            serverTexts->at(i)->shown = true;
        }
    }

}

/**
 * Clear the content of the `serverTexts` list
 */
void RandomizerArchipelago::emptyServerText() {
    for (std::vector<serverText_t *>::iterator lIterator = serverTexts->begin(); lIterator != serverTexts->end();) {
        for (std::vector<serverSegmentText_t *>::iterator lSegment = (*lIterator)->segments.begin();
             lSegment != (*lIterator)->segments.end();) {
            delete(*lSegment);
            (*lIterator)->segments.erase(lSegment);
        }
        for (std::vector<serverSegmentTextInfo_t *>::iterator lSegmentInfo = (*lIterator)->segmentInfos->begin();
             lSegmentInfo != (*lIterator)->segmentInfos->end();) {
            delete(*lSegmentInfo);
            (*lIterator)->segmentInfos->erase(lSegmentInfo);
        }
        delete((*lIterator)->segmentInfos);
        (*lIterator)->segmentInfos = nullptr;
        serverTexts->erase(lIterator);
    }
    serverTexts->clear();
}

/**
 * Check if the Text node is related to the current player.
 * @param aData The text node
 * @return True if the text node is related to the current player
 */
bool RandomizerArchipelago::selfRelatedJson(const std::list<APClient::TextNode>& aData) {
    bool lResult = false;
    for (const APClient::TextNode& lNode : aData) {
        if (lNode.type == "player_id") {
            if (apClient->get_player_number() == std::stoi(lNode.text)) {
                lResult = true;
            }
        }
    }
    return lResult;
}

/**
 * Launched when the Archipelago server send a bounce message
 * @param aJson The message
 */
void RandomizerArchipelago::onBounceMessageReceived (const nlohmann::json& aJson){
    if (deathLink) {
        auto lTags = aJson.find("tags");
        auto lDatas = aJson.find("data");
        if (lTags != aJson.end() && lTags->is_array()
            && std::find(lTags->begin(), lTags->end(), "DeathLink") != lTags->end()
            && dsq->game->avatar)
        {
            if (lDatas != aJson.end() && lDatas->is_object()) {
                nlohmann::json lData = *lDatas;
                if (lData["source"].get<std::string>() != apClient->get_slot()) {
                    std::string source = lData["source"].is_string() ?
                            lData["source"].get<std::string>().c_str() : "Unknown";
                    std::string cause = lData["cause"].is_string() ?
                            lData["cause"].get<std::string>().c_str() : "Unknown";
                    showText("Died by the hands of " + source + " : " + cause);
                    dsq->game->avatar->health = 0;
                }
            }
            else {
                debugLog("Bad deathlink packet!");
            }
        }
    }
}

/**
 * Translate a TextNode from `onPrintJson` to a showable text
 * @param aNode The TextNode to translate
 * @return The translated text
 */
std::string RandomizerArchipelago::translateJsonDataToString(const APClient::TextNode& aNode) {
    std::string lResult;
    if (aNode.type == "player_id") {
        lResult = apClient->get_player_alias(std::stoi(aNode.text));
    } else if(aNode.type == "item_id") {
        lResult = apClient->get_item_name(std::stoi(aNode.text), apClient->get_player_game(aNode.player));
    } else if(aNode.type == "location_id") {
        lResult = apClient->get_location_name(std::stoi(aNode.text), apClient->get_player_game(aNode.player));
    } else {
        lResult = aNode.text;
    }
    return lResult;
}

/**
 * Get an apitem_t from the Id of the Item
 * @param aId The id of the item
 * @return The apitem_t associate to the ID
 */
apitem_t *RandomizerArchipelago::getApItemById(int64_t aId) {
    apitem_t *lResult = nullptr;
    for (int i = 0; i < apItems->size() && !lResult; i = i + 1) {
        if (apItems->at(i).itemId == aId) {
            lResult = &apItems->at(i);
        }
    }
    return lResult;
}

/**
 * Get a new ingredient to receive in the local game
 * @param aIngredientName The name of the ingredient to receive
 * @param aCount The number of ingredient to receive
 */
void RandomizerArchipelago::receivingIngredient(const std::string& aIngredientName, int aCount) {
    if (isOffline) {
        if (infiniteHotSoup && aIngredientName == "hotsoup") {
            Randomizer::receivingIngredient(aIngredientName, aCount);
        } else {
            dsq->game->pickupItemEffects("ap/useful");
        }
    } else {
        Randomizer::receivingIngredient(aIngredientName, aCount);
    }
}

/**
 * Received an health upgrade
 */
void RandomizerArchipelago::receivingUpgradeHealth() {
    if (!isOffline) {
        Randomizer::receivingUpgradeHealth();
    } else {
        dsq->game->pickupItemEffects("ap/useful");
    }
}

/**
 * Activate a randomizer check
 * @param aCheck The check to activate
 */
void RandomizerArchipelago::activateCheck(std::string aCheck) {
    check_t *lCheck = getCheck(aCheck);
    bool lhad_flag = dsq->continuity.getFlag(lCheck->flag);
    dsq->continuity.setFlag(lCheck->flag, 1);
    std::list<int64_t> lIds;
    for(int i = 0; i < apLocations->size() && lIds.empty(); i = i + 1) {
        if (aCheck == apLocations->at(i).name) {
            lIds.push_back(apLocations->at(i).locationId);
            if (!syncing && !lhad_flag && apLocations->at(i).locationId - AP_BASE < locationsItemTypes->size()) {
                int lItemType = locationsItemTypes->at(apLocations->at(i).locationId - AP_BASE);
                if (lItemType == TRASH) {
                    dsq->game->pickupItemEffects("ap/trash");
                } else if (lItemType == PROGRESSION) {
                    dsq->game->pickupItemEffects("ap/progression");
                } else if (lItemType == USEFULL) {
                    dsq->game->pickupItemEffects("ap/useful");
                } else if (lItemType == TRAP) {
                    dsq->game->pickupItemEffects("ap/trap");
                } else if (isOffline) {
                    apitem_t *lApItem = getApItemById(lItemType);
                    // Todo: Removing the exception when the doors are official
                    if (lCheck->flag == 1319 && !dsq->continuity.getFlag(FLAG_MITHALAS_THRONEROOM)) {
                        receivingItem(lApItem->item, lApItem->count);
                    }
                    if (lCheck->flag == 1320 && !dsq->continuity.getFlag(FLAG_REMOVE_TONGUE)) {
                        receivingItem(lApItem->item, lApItem->count);
                    }
                }
            }
            if (!isOffline) {
                // Todo: Removing the exception when the doors are official
                if (
                    (lCheck->flag != 1319 && lCheck->flag != 1320) ||
                    (lCheck->flag == 1319 && throneAsLocationManagedByServer) ||
                    (lCheck->flag == 1320 && golemAsLocationManagedByServer)
                    ) {
                        std::lock_guard<std::mutex> lock(apMutex);
                    apClient->LocationChecks(lIds);
                } else {
                    if (!throneAsLocationManagedByServer && lCheck->flag == 1319 &&
                        !dsq->continuity.getFlag(FLAG_MITHALAS_THRONEROOM)) {
                        receivingItem(lCheck->item, 1);
                    }
                    if (!golemAsLocationManagedByServer && lCheck->flag == 1320 &&
                        !dsq->continuity.getFlag(FLAG_REMOVE_TONGUE)) {
                        receivingItem(lCheck->item, 1);
                    }
                }
            }
        }
    }
}

/**
 * Update the APClient to handle items.
 * @param aNoMutex Do not use mutex protection in the update
 */
void RandomizerArchipelago::connectionUpdate(bool aNoMutex) {
    const int item_handling_flags_all = 7;
    if (!isOffline) {
        std::list<std::string> tags;
        if (deathLink) {
            tags.emplace_back("DeathLink");
        }
        if (apClient->get_state() != APClient::State::DISCONNECTED) {
            if (aNoMutex) {
                apClient->ConnectUpdate(item_handling_flags_all,tags);
                apClient->poll();
            } else {
                std::lock_guard<std::mutex> lock(apMutex);
                apClient->ConnectUpdate(item_handling_flags_all,tags);
                apClient->poll();
            }

        }
    }
}

/**
 * Lunched at each game loop iteration
 */
void RandomizerArchipelago::update(){
    Randomizer::update();
    if (!isOffline) {
        try {
            std::lock_guard<std::mutex> lock(apMutex);
            apClient->poll();
            if (apClient->get_state() == APClient::State::DISCONNECTED) {
                hasBeenDisconnected = true;
                if (nextMessagesSize() == 0) {
                    showText("Disconnected from server. Trying to reconnect.");
                }
            } else if (apClient->get_state() == APClient::State::SOCKET_CONNECTED ||
                       apClient->get_state() == APClient::State::SLOT_CONNECTED) {
                if (hasBeenDisconnected) {
                    connectionUpdate(true);
                    apClient->Sync();
                    syncing = true;
                }
                hasBeenDisconnected = false;
                       }
        } catch (const websocketpp::exception& lException) {
            hasBeenDisconnected = true;
            showText("Disconnected from server. Trying to reconnect.");
        }
        if (inGame) {
            updatePrintServerText();
            updateDataStorage();
            if (syncing) {
                for (const check_t& lCheck : *checks) {
                    if (dsq->continuity.getFlag(lCheck.flag)) {
                        activateCheck(lCheck.id);
                    }
                }
                syncing = false;
            }
            if (dsq->game->avatar && dsq->game->avatar->isEntityDead()) {
                if (deathLink && !deathLinkPause) {
                    deathLinkPause = true;
                    deathLinkPause = true;
                    nlohmann::json data{
                            {"time", apClient->get_server_time()},
                            {"cause", "Naija did not make it."},
                            {"source", apClient->get_slot()},
                    };
                    apClient->Bounce(data, {}, {}, { "DeathLink" });
                }
            } else {
                deathLinkPause = false;
            }
        }
    }
    auto lNow = std::chrono::system_clock::now();
    if (currentQuickMessageTime) {
        auto lTime = std::chrono::system_clock::from_time_t (currentQuickMessageTime);
        auto lDuration = std::chrono::duration_cast<std::chrono::seconds>(lNow - lTime);
        if (lDuration.count() > 1) {
            currentQuickMessageTime = 0;
            if (!nextQuickMessages->empty()) {
                std::string lMessage = nextQuickMessages->front();
                nextQuickMessages->pop();
                showQuickMessage(lMessage);
            }
        }
    }
}

/**
 * Check if it is the end of the four gods run
 */
void RandomizerArchipelago::manageFourGodsEnding() {
    if (killCreatorGoal) {
        Randomizer::manageFourGodsEnding();
    } else {
        if (!isGoal && dsq->continuity.getFlag(FLAG_ENERGYBOSSDEAD) && dsq->continuity.getFlag(FLAG_BOSS_MITHALA) &&
                dsq->continuity.getFlag(FLAG_BOSS_FOREST) && dsq->continuity.getFlag(FLAG_BOSS_SUNWORM)) {
            if (miniBossCount() >= miniBossesToKill) {
                std::lock_guard<std::mutex> lock(apMutex);
                apClient->StatusUpdate(APClient::ClientStatus::GOAL);
                isGoal = true;
            } else {
                if (!fourGodsGoalMessage) {
                    showHint(miniBossCount(), miniBossesToKill, "mini bosses beaten");
                    fourGodsGoalMessage = true;
                }
            }
            if (dsq->continuity.getFlag(FLAG_BLIND_GOAL) != 0) {
                dsq->continuity.setFlag(FLAG_BLIND_GOAL, 0);
            }
        }
    }
}

/**
 * Set a single Archipelago data storage value
 * @param aId The ID of the key
 * @param aValue The value to set
 */
void RandomizerArchipelago::setDataStorage(std::string aId, int aValue, bool aUnconditional) {
    if (!isOffline && (aUnconditional || (dataStorageInfo->at(aId) != aValue))) {
        APClient::DataStorageOperation lOperation;
        std::list<APClient::DataStorageOperation> lOperationList;
        nlohmann::json lData{aValue};

        lOperation.operation = "replace";
        lOperation.value = lData;
        lOperationList.push_back(lOperation);
        apClient->Set(std::to_string(apClient->get_player_number()) + "@" + aId,
                      0, false, lOperationList);
        dataStorageInfo->at(aId) = aValue;
    }
}

/**
 * Initialise the `dataStorageInfo` to default values.
 */
void RandomizerArchipelago::initialisedDataStorageInfo() {
    dataStorageInfo->emplace(std::make_pair<std::string,int>(std::string(ID_MINIBOSS_NAUTILUSPRIME), 0));
    dataStorageInfo->emplace(std::make_pair<std::string,int>(std::string(ID_MINIBOSS_KINGJELLY), 0));
    dataStorageInfo->emplace(std::make_pair<std::string,int>(std::string(ID_MINIBOSS_MERGOG), 0));
    dataStorageInfo->emplace(std::make_pair<std::string,int>(std::string(ID_MINIBOSS_CRAB), 0));
    dataStorageInfo->emplace(std::make_pair<std::string,int>(std::string(ID_MINIBOSS_OCTOMUN), 0));
    dataStorageInfo->emplace(std::make_pair<std::string,int>(std::string(ID_MINIBOSS_MANTISSHRIMP), 0));
    dataStorageInfo->emplace(std::make_pair<std::string,int>(std::string(ID_MINIBOSS_PRIESTS), 0));
    dataStorageInfo->emplace(std::make_pair<std::string,int>(std::string(ID_MINIBOSS_BLASTER), 0));
    dataStorageInfo->emplace(std::make_pair<std::string,int>(std::string(ID_ENERGYBOSSDEAD), 0));
    dataStorageInfo->emplace(std::make_pair<std::string,int>(std::string(ID_SUNKENCITY_BOSS), 0));
    dataStorageInfo->emplace(std::make_pair<std::string,int>(std::string(ID_BOSS_FOREST), 0));
    dataStorageInfo->emplace(std::make_pair<std::string,int>(std::string(ID_BOSS_MITHALA), 0));
    dataStorageInfo->emplace(std::make_pair<std::string,int>(std::string(ID_BOSS_SUNWORM), 0));
    dataStorageInfo->emplace(std::make_pair<std::string,int>(std::string(ID_SECRET01), 0));
    dataStorageInfo->emplace(std::make_pair<std::string,int>(std::string(ID_SECRET02), 0));
    dataStorageInfo->emplace(std::make_pair<std::string,int>(std::string(ID_SECRET03), 0));
    dataStorageInfo->emplace(std::make_pair<std::string,int>(std::string(ID_SUN_CRYSTAL_OBTAINED), 0));
    dataStorageInfo->emplace(std::make_pair<std::string,int>(std::string(ID_REMOVE_TONGUE), 0));
}

/**
 * Initialise the `dataStorageInfo` to default values.
 */
void RandomizerArchipelago::updateDataStorageInfo() {
    std::list<std::string> lIdList;
    lIdList.push_back(std::to_string(apClient->get_player_number()) + "@" + ID_MINIBOSS_NAUTILUSPRIME);
    lIdList.push_back(std::to_string(apClient->get_player_number()) + "@" + ID_MINIBOSS_KINGJELLY);
    lIdList.push_back(std::to_string(apClient->get_player_number()) + "@" + ID_MINIBOSS_MERGOG);
    lIdList.push_back(std::to_string(apClient->get_player_number()) + "@" + ID_MINIBOSS_CRAB);
    lIdList.push_back(std::to_string(apClient->get_player_number()) + "@" + ID_MINIBOSS_OCTOMUN);
    lIdList.push_back(std::to_string(apClient->get_player_number()) + "@" + ID_MINIBOSS_MANTISSHRIMP);
    lIdList.push_back(std::to_string(apClient->get_player_number()) + "@" + ID_MINIBOSS_PRIESTS);
    lIdList.push_back(std::to_string(apClient->get_player_number()) + "@" + ID_MINIBOSS_BLASTER);
    lIdList.push_back(std::to_string(apClient->get_player_number()) + "@" + ID_ENERGYBOSSDEAD);
    lIdList.push_back(std::to_string(apClient->get_player_number()) + "@" + ID_SUNKENCITY_BOSS);
    lIdList.push_back(std::to_string(apClient->get_player_number()) + "@" + ID_BOSS_FOREST);
    lIdList.push_back(std::to_string(apClient->get_player_number()) + "@" + ID_BOSS_MITHALA);
    lIdList.push_back(std::to_string(apClient->get_player_number()) + "@" + ID_BOSS_SUNWORM);
    lIdList.push_back(std::to_string(apClient->get_player_number()) + "@" + ID_SECRET01);
    lIdList.push_back(std::to_string(apClient->get_player_number()) + "@" + ID_SECRET02);
    lIdList.push_back(std::to_string(apClient->get_player_number()) + "@" + ID_SECRET03);
    lIdList.push_back(std::to_string(apClient->get_player_number()) + "@" + ID_SUN_CRYSTAL_OBTAINED);
    lIdList.push_back(std::to_string(apClient->get_player_number()) + "@" + ID_REMOVE_TONGUE);
    if (!isOffline) {
        apClient->Get(lIdList);
    }
}

/**
 * Update the Archipelago server data storage to put new values in it.
     * @param unconditional True if the value is assing even if it was not modified from before assignment
 */
void RandomizerArchipelago::updateDataStorage(bool aUnconditional) {
    setDataStorage(ID_MINIBOSS_NAUTILUSPRIME, dsq->continuity.getFlag(FLAG_MINIBOSS_NAUTILUSPRIME), aUnconditional);
    setDataStorage(ID_MINIBOSS_KINGJELLY, dsq->continuity.getFlag(FLAG_MINIBOSS_KINGJELLY), aUnconditional);
    setDataStorage(ID_MINIBOSS_MERGOG, dsq->continuity.getFlag(FLAG_MINIBOSS_MERGOG), aUnconditional);
    setDataStorage(ID_MINIBOSS_CRAB, dsq->continuity.getFlag(FLAG_MINIBOSS_CRAB), aUnconditional);
    setDataStorage(ID_MINIBOSS_OCTOMUN, dsq->continuity.getFlag(FLAG_MINIBOSS_OCTOMUN), aUnconditional);
    setDataStorage(ID_MINIBOSS_MANTISSHRIMP, dsq->continuity.getFlag(FLAG_MINIBOSS_MANTISSHRIMP), aUnconditional);
    setDataStorage(ID_MINIBOSS_PRIESTS, dsq->continuity.getFlag(FLAG_MINIBOSS_PRIESTS), aUnconditional);
    setDataStorage(ID_MINIBOSS_BLASTER, dsq->continuity.getFlag(FLAG_MINIBOSS_BLASTER), aUnconditional);
    setDataStorage(ID_ENERGYBOSSDEAD, dsq->continuity.getFlag(FLAG_ENERGYBOSSDEAD), aUnconditional);
    setDataStorage(ID_SUNKENCITY_BOSS, dsq->continuity.getFlag(FLAG_SUNKENCITY_BOSS), aUnconditional);
    setDataStorage(ID_BOSS_FOREST, dsq->continuity.getFlag(FLAG_BOSS_FOREST), aUnconditional);
    setDataStorage(ID_BOSS_MITHALA, dsq->continuity.getFlag(FLAG_BOSS_MITHALA), aUnconditional);
    setDataStorage(ID_BOSS_SUNWORM, dsq->continuity.getFlag(FLAG_BOSS_SUNWORM), aUnconditional);
    setDataStorage(ID_SECRET01, dsq->continuity.getFlag(FLAG_SECRET01), aUnconditional);
    setDataStorage(ID_SECRET02, dsq->continuity.getFlag(FLAG_SECRET02), aUnconditional);
    setDataStorage(ID_SECRET03, dsq->continuity.getFlag(FLAG_SECRET03), aUnconditional);
    setDataStorage(ID_SUN_CRYSTAL_OBTAINED, dsq->continuity.getFlag(FLAG_SUNTEMPLE_LIGHTCRYSTAL), aUnconditional);
    setDataStorage(ID_REMOVE_TONGUE, dsq->continuity.getFlag(FLAG_REMOVE_TONGUE), aUnconditional);
}

/**
 * Launched when the game is ending
 */
void RandomizerArchipelago::endingGame() {
    if (!isOffline) {
        if (
                (killCreatorGoal && !killFourGodsGoal && miniBossCount() >= miniBossesToKill &&
                    bigBossCount() >= bigBossesToKill && (!secretsNeeded || (secretsFound() == 3))) ||
                (killFourGodsGoal && killCreatorGoal && dsq->continuity.getFlag(FLAG_ENERGYBOSSDEAD) &&
                    dsq->continuity.getFlag(FLAG_BOSS_MITHALA) && dsq->continuity.getFlag(FLAG_BOSS_FOREST) &&
                    dsq->continuity.getFlag(FLAG_BOSS_SUNWORM) && miniBossCount() >= miniBossesToKill)
        ){
            std::lock_guard<std::mutex> lock(apMutex);
            apClient->StatusUpdate(APClient::ClientStatus::GOAL);
            debugLog("Goal completed!");
        } else {
            showText("You are missing some prerequisite to get the goal.");
        }
    }
}

/**
 * A now or saves game has been load
   @param aNewGame True if a new game is launched.
 */
void RandomizerArchipelago::onLoad(bool aNewGame){
    Randomizer::onLoad(aNewGame);
    emptyServerText();
    lastArea = "";
    if (killFourGodsGoal) {
        dsq->continuity.setFlag(FLAG_REMOVE_TONGUE, 1);
    }
    if (aNewGame) {
        if (isOffline) {
            dsq->toggleCursor(true);
            dsq->confirm("Error, cannot start a new game\nwhen offline. Closing...","", true, 0.0);
            dsq->Core::instantQuit();
        } else {
            saveConnectionInfo();
        }
    } else {
        if (isOffline) {
            if (dsq->continuity.getFlag(FLAG_SAVE_HAS_INFO)) {
                loadConnectionInfo();
            } else {
                dsq->toggleCursor(true);
                dsq->confirm("Error, cannot use this save\ngame offline. Closing...","", true, 0.0);
                dsq->Core::instantQuit();
            }
        } else {
            saveConnectionInfo();
        }
    }
    if (!isOffline) {
        initialisedDataStorageInfo();
        updateDataStorage(true);
        connectionUpdate();
        apClient->Sync();
        syncing = true;
    }
}

/**
 * When a game is closing a game (return to menu).
 */
void RandomizerArchipelago::onClose(){
    Randomizer::onClose();
    if (!isOffline) {
        std::lock_guard<std::mutex> lock(apMutex);
        apClient->ConnectUpdate(0, {});
    }
}

/**
 * Launched when a scene is loading
 *
 * @param aScene The scene name that is loading
 */
void RandomizerArchipelago::onLoadScene(std::string aScene) {
    Randomizer::onLoadScene(aScene);
    int lTimeDelay = ceil((dsq->getTicks() - removeStateTick) / 1000);
    for (std::vector<serverText_t *>::iterator lIterator = serverTexts->begin(); lIterator != serverTexts->end();++lIterator) {
        createServerTextRenderObjects((*lIterator));
        (*lIterator)->time = (*lIterator)->time + lTimeDelay;
    }
    dsq->game->tileCache.precacheTex("ap/progression");
    dsq->game->tileCache.precacheTex("ap/useful");
    dsq->game->tileCache.precacheTex("ap/trash");
    dsq->game->tileCache.precacheTex("ap/trap");
    for (const auto& aArea: *areaInfo) {
        if (aScene == aArea.first && lastArea != aArea.second) {
            lastArea = aArea.second;
            nlohmann::json data{
                                {"time", apClient->get_server_time()},
                                {"area", aArea.second},
                        };
            apClient->Bounce(data, {}, {apClient->get_player_number()}, {});
        }
    }
    betweenState = false;
}
/**
 * When a new state is appied in the game
 */
void RandomizerArchipelago::removeState() {
    betweenState = true;
    Randomizer::removeState();
    for (std::vector<serverText_t *>::iterator lIterator = serverTexts->begin(); lIterator != serverTexts->end();++lIterator) {
        for (std::vector<serverSegmentText_t *>::iterator lSegment = (*lIterator)->segments.begin(); lSegment != (*lIterator)->segments.end();) {
            if ((*lSegment)->text != nullptr) {
                (*lSegment)->text->safeKill();
                (*lSegment)->text = nullptr;
            }
            delete(*lSegment);
            (*lIterator)->segments.erase(lSegment);
        }
        if ((*lIterator)->background != nullptr) {
            (*lIterator)->background->safeKill();
            (*lIterator)->background = nullptr;
        }
    }
    removeStateTick = dsq->getTicks();
}

/**
 * Is the final boss is accessible.
 * @return True if the final boss is accessible. False if not.
 */
bool RandomizerArchipelago::accessFinalBoss() {
    return !isOffline and Randomizer::accessFinalBoss();
}

/**
 * Show what is missing to access final boss.
 */
bool RandomizerArchipelago::showHintFinalBoss() {
    bool lResult = false;
    if (!isOffline) {
        lResult = Randomizer::showHintFinalBoss();
    } else {
        showText("You cannot beat the creator while offline. Please connect to the Archipelago server.");
        dsq->continuity.setFlag(FLAG_BLIND_GOAL, 0);
    }
    return lResult;
}

/**
 * Show a quick message on the screen.
 * @param aText The text to show
 */
void RandomizerArchipelago::showQuickMessage(const std::string &aText){
    if (currentQuickMessageTime) {
        nextQuickMessages->push(aText);
    } else {
        auto lNow = std::chrono::system_clock::now();
        std::time_t currentTime = std::chrono::system_clock::to_time_t(lNow);
        currentQuickMessageTime = currentTime;
        dsq->screenMessage(aText);
    }
}

/**
 * The unique String for the Randomizer
 * @return The String of the Randomizer
 */
std::string RandomizerArchipelago::getUniqueString() {
    return getUid() + "_" + name;
}

/**
 * Add information about locations in `data`.
 *
 * @param aData Where the information about item should be put.
 */
void RandomizerArchipelago::appendLocationsHelpData(std::string &aData) {
    if (isOffline) {
        Randomizer::appendLocationsHelpData(aData);
    } else {
        std::stringstream lMessageStream;
        lMessageStream << "[Locations obtained]\n[Local] (AP) Name\n";
        int lCount = LOCATIONS_SIZE;
        const int *lLocationsOrder = locationsOrder;
        if (killFourGodsGoal) {
            lCount = LOCATIONS_FOUR_GODS_SIZE;
            lLocationsOrder = locationsOrderFourGods;
        }
        for (int i = 0; i < lCount; i = i + 1) {
            if (dsq->continuity.getFlag(checks->at(lLocationsOrder[i]).flag)) {
                lMessageStream << "   [X]      ";
            } else {
                lMessageStream << "    [ ]       ";
            }
            bool lFound = false;
            if (checks->at(lLocationsOrder[i]).flag == 1319 && !throneAsLocationManagedByServer) {
                lMessageStream << "      ";
            }
            if (checks->at(lLocationsOrder[i]).flag == 1320 && !golemAsLocationManagedByServer) {
                lMessageStream << "      ";
            }
            for (int j = 0; j < apLocations->size() && !lFound ; j = j + 1) {
                if ((checks->at(lLocationsOrder[i]).flag != 1319 && checks->at(lLocationsOrder[i]).flag != 1320) ||
                    (throneAsLocationManagedByServer && checks->at(lLocationsOrder[i]).flag == 1319) ||
                    (golemAsLocationManagedByServer && checks->at(lLocationsOrder[i]).flag == 1320)) {
                    if (apLocations->at(j).name == checks->at(lLocationsOrder[i]).id) {
                        for (int64_t laLocation : apClient->get_checked_locations()) {
                            if (laLocation == apLocations->at(j).locationId) {
                                lMessageStream << "(X) ";
                                lFound = true;
                            }
                        }
                        if (!lFound) {
                            lMessageStream << "( )  ";
                            lFound = true;
                        }
                    }
                }

            }
            lMessageStream << checks->at(lLocationsOrder[i]).location;
            lMessageStream << "\n";
        }
        lMessageStream << "\n\n";
        aData += lMessageStream.str();
    }
}

/**
 * Initialise areaInfo
 */
void RandomizerArchipelago::initialiseAreaInfo() {
    areaInfo->insert(std::make_pair<std::string,std::string>("cathedral04", "cathedralunderground"));
    areaInfo->insert(std::make_pair<std::string,std::string>("cathedral03", "cathedralunderground"));
    areaInfo->insert(std::make_pair<std::string,std::string>("energytemple01", "energytemple"));
    areaInfo->insert(std::make_pair<std::string,std::string>("energytemple02", "energytemple"));
    areaInfo->insert(std::make_pair<std::string,std::string>("energytemple04", "energytemple"));
    areaInfo->insert(std::make_pair<std::string,std::string>("energytemple05", "energytemple"));
    areaInfo->insert(std::make_pair<std::string,std::string>("energytemple06", "energytemple"));
    areaInfo->insert(std::make_pair<std::string,std::string>("energytemplevision", "energytemple"));
    areaInfo->insert(std::make_pair<std::string,std::string>("mainarea", "homewater"));
    areaInfo->insert(std::make_pair<std::string,std::string>("bubblecave02", "icecave"));
    areaInfo->insert(std::make_pair<std::string,std::string>("frozenveil", "icecave"));
    areaInfo->insert(std::make_pair<std::string,std::string>("icecave", "icecave"));
    areaInfo->insert(std::make_pair<std::string,std::string>("fishcave", "kelpforest"));
    areaInfo->insert(std::make_pair<std::string,std::string>("forest02", "kelpforest"));
    areaInfo->insert(std::make_pair<std::string,std::string>("forest03", "kelpforest"));
    areaInfo->insert(std::make_pair<std::string,std::string>("forest04", "kelpforest"));
    areaInfo->insert(std::make_pair<std::string,std::string>("forest05", "kelpforest"));
    areaInfo->insert(std::make_pair<std::string,std::string>("forestspritecave", "kelpforest"));
    areaInfo->insert(std::make_pair<std::string,std::string>("forestvision", "kelpforest"));
    areaInfo->insert(std::make_pair<std::string,std::string>("mermogcave", "kelpforest"));
    areaInfo->insert(std::make_pair<std::string,std::string>("tree01", "kelpforest"));
    areaInfo->insert(std::make_pair<std::string,std::string>("tree02", "kelpforest"));
    areaInfo->insert(std::make_pair<std::string,std::string>("cathedral02", "mithalascathedral"));
    areaInfo->insert(std::make_pair<std::string,std::string>("mithalasvision", "mithalascathedral"));
    areaInfo->insert(std::make_pair<std::string,std::string>("mithalas01", "mithalascity"));
    areaInfo->insert(std::make_pair<std::string,std::string>("mithalas02", "mithalascitycastle"));
    areaInfo->insert(std::make_pair<std::string,std::string>("vedhacave", "naijashome"));
    areaInfo->insert(std::make_pair<std::string,std::string>("openwater02", "openwater"));
    areaInfo->insert(std::make_pair<std::string,std::string>("openwater03", "openwater"));
    areaInfo->insert(std::make_pair<std::string,std::string>("openwater04", "openwater"));
    areaInfo->insert(std::make_pair<std::string,std::string>("openwater05", "openwater"));
    areaInfo->insert(std::make_pair<std::string,std::string>("openwater06", "arnassiruins"));
    areaInfo->insert(std::make_pair<std::string,std::string>("seahorse", "arnassiruins"));
    areaInfo->insert(std::make_pair<std::string,std::string>("songcave02", "songcave"));
    areaInfo->insert(std::make_pair<std::string,std::string>("songcave", "songcave"));
    areaInfo->insert(std::make_pair<std::string,std::string>("suntemple", "suntemple"));
    areaInfo->insert(std::make_pair<std::string,std::string>("sunwormtest", "suntemple"));
    areaInfo->insert(std::make_pair<std::string,std::string>("abyss01", "abyss"));
    areaInfo->insert(std::make_pair<std::string,std::string>("abyss03", "abyss"));
    areaInfo->insert(std::make_pair<std::string,std::string>("sunkencity01", "sunkencity"));
    areaInfo->insert(std::make_pair<std::string,std::string>("sunkencity02", "sunkencity"));
    areaInfo->insert(std::make_pair<std::string,std::string>("boilerroom", "sunkencity"));
    areaInfo->insert(std::make_pair<std::string,std::string>("final01", "thebody"));
    areaInfo->insert(std::make_pair<std::string,std::string>("final02", "thebody"));
    areaInfo->insert(std::make_pair<std::string,std::string>("final03", "thebody"));
    areaInfo->insert(std::make_pair<std::string,std::string>("final04", "thebody"));
    areaInfo->insert(std::make_pair<std::string,std::string>("finalboss02", "thebody"));
    areaInfo->insert(std::make_pair<std::string,std::string>("finalboss", "thebody"));
    areaInfo->insert(std::make_pair<std::string,std::string>("finalescape", "thebody"));
    areaInfo->insert(std::make_pair<std::string,std::string>("licave", "theveil"));
    areaInfo->insert(std::make_pair<std::string,std::string>("octocave", "theveil"));
    areaInfo->insert(std::make_pair<std::string,std::string>("turtlecave", "theveil"));
    areaInfo->insert(std::make_pair<std::string,std::string>("veil01", "theveil"));
    areaInfo->insert(std::make_pair<std::string,std::string>("veil02", "theveil"));
    areaInfo->insert(std::make_pair<std::string,std::string>("veil03", "theveil"));
    areaInfo->insert(std::make_pair<std::string,std::string>("naijacave", "versecave"));
    areaInfo->insert(std::make_pair<std::string,std::string>("trainingcave", "versecave"));
}

/**
 * Initialise every apitem_t element of the apItems list
 */
void RandomizerArchipelago::initialiseApItems(){
    apItems->push_back({AP_BASE + 0, "collectible_anemone", 1, ITEM_TYPE_COLLECTIBLE});
    apItems->push_back({AP_BASE + 1, "collectible_arnassi_statue", 1, ITEM_TYPE_COLLECTIBLE});
    apItems->push_back({AP_BASE + 2, "collectible_big_seed", 1, ITEM_TYPE_COLLECTIBLE});
    apItems->push_back({AP_BASE + 3, "collectible_bio_seed", 1, ITEM_TYPE_COLLECTIBLE});
    apItems->push_back({AP_BASE + 4, "collectible_blackpearl", 1, ITEM_TYPE_COLLECTIBLE});
    apItems->push_back({AP_BASE + 5, "collectible_blaster", 1, ITEM_TYPE_COLLECTIBLE});
    apItems->push_back({AP_BASE + 6, "collectible_crab_costume", 1, ITEM_TYPE_COLLECTIBLE});
    apItems->push_back({AP_BASE + 7, "collectible_dumbo", 1, ITEM_TYPE_COLLECTIBLE});
    apItems->push_back({AP_BASE + 8, "collectible_energy_boss", 1, ITEM_TYPE_COLLECTIBLE});
    apItems->push_back({AP_BASE + 9, "collectible_energy_statue", 1, ITEM_TYPE_COLLECTIBLE});
    apItems->push_back({AP_BASE + 10, "collectible_energy_temple", 1, ITEM_TYPE_COLLECTIBLE});
    apItems->push_back({AP_BASE + 11, "collectible_gold_star", 1, ITEM_TYPE_COLLECTIBLE});
    apItems->push_back({AP_BASE + 12, "collectible_golden_gear", 1, ITEM_TYPE_COLLECTIBLE});
    apItems->push_back({AP_BASE + 13, "collectible_jelly_beacon", 1, ITEM_TYPE_COLLECTIBLE});
    apItems->push_back({AP_BASE + 14, "collectible_jelly_costume", 1, ITEM_TYPE_COLLECTIBLE});
    apItems->push_back({AP_BASE + 15, "collectible_jelly_plant", 1, ITEM_TYPE_COLLECTIBLE});
    apItems->push_back({AP_BASE + 16, "collectible_mithala_doll", 1, ITEM_TYPE_COLLECTIBLE});
    apItems->push_back({AP_BASE + 17, "collectible_mithalan_costume", 1, ITEM_TYPE_COLLECTIBLE});
    apItems->push_back({AP_BASE + 18, "collectible_mithalas_banner", 1, ITEM_TYPE_COLLECTIBLE});
    apItems->push_back({AP_BASE + 19, "collectible_mithalas_pot", 1, ITEM_TYPE_COLLECTIBLE});
    apItems->push_back({AP_BASE + 20, "collectible_mutant_costume", 1, ITEM_TYPE_COLLECTIBLE});
    apItems->push_back({AP_BASE + 21, "collectible_nautilus", 1, ITEM_TYPE_COLLECTIBLE});
    apItems->push_back({AP_BASE + 22, "collectible_piranha", 1, ITEM_TYPE_COLLECTIBLE});
    apItems->push_back({AP_BASE + 23, "collectible_seahorse_costume", 1, ITEM_TYPE_COLLECTIBLE});
    apItems->push_back({AP_BASE + 24, "collectible_seed_bag", 1, ITEM_TYPE_COLLECTIBLE});
    apItems->push_back({AP_BASE + 25, "collectible_skull", 1, ITEM_TYPE_COLLECTIBLE});
    apItems->push_back({AP_BASE + 26, "collectible_spore_seed", 1, ITEM_TYPE_COLLECTIBLE});
    apItems->push_back({AP_BASE + 27, "collectible_stone_head", 1, ITEM_TYPE_COLLECTIBLE});
    apItems->push_back({AP_BASE + 28, "collectible_sun_key", 1, ITEM_TYPE_COLLECTIBLE});
    apItems->push_back({AP_BASE + 29, "collectible_teen_costume", 1, ITEM_TYPE_COLLECTIBLE});
    apItems->push_back({AP_BASE + 30, "collectible_treasure_chest", 1, ITEM_TYPE_COLLECTIBLE});
    apItems->push_back({AP_BASE + 31, "collectible_trident_head", 1, ITEM_TYPE_COLLECTIBLE});
    apItems->push_back({AP_BASE + 32, "collectible_turtle_egg", 1, ITEM_TYPE_COLLECTIBLE});
    apItems->push_back({AP_BASE + 33, "collectible_upsidedown_seed", 1, ITEM_TYPE_COLLECTIBLE});
    apItems->push_back({AP_BASE + 34, "collectible_urchin_costume", 1, ITEM_TYPE_COLLECTIBLE});
    apItems->push_back({AP_BASE + 35, "collectible_walker", 1, ITEM_TYPE_COLLECTIBLE});
    apItems->push_back({AP_BASE + 36, "ingredient_Vedha'sCure-All", 1, ITEM_TYPE_RECIPE});
    apItems->push_back({AP_BASE + 37, "ingredient_Zuuna'sperogi", 1, ITEM_TYPE_RECIPE});
    apItems->push_back({AP_BASE + 38, "ingredient_arcanepoultice", 1, ITEM_TYPE_RECIPE});
    apItems->push_back({AP_BASE + 39, "ingredient_berryicecream", 1, ITEM_TYPE_RECIPE});
    apItems->push_back({AP_BASE + 40, "ingredient_butterysealoaf", 1, ITEM_TYPE_RECIPE});
    apItems->push_back({AP_BASE + 41, "ingredient_coldborscht", 1, ITEM_TYPE_RECIPE});
    apItems->push_back({AP_BASE + 42, "ingredient_coldsoup", 1, ITEM_TYPE_RECIPE});
    apItems->push_back({AP_BASE + 43, "ingredient_crabcake", 1, ITEM_TYPE_RECIPE});
    apItems->push_back({AP_BASE + 44, "ingredient_divinesoup", 1, ITEM_TYPE_RECIPE});
    apItems->push_back({AP_BASE + 45, "ingredient_dumboicecream", 1, ITEM_TYPE_RECIPE});
    apItems->push_back({AP_BASE + 46, "ingredient_fishoil", 1, ITEM_TYPE_INGREDIENT});
    apItems->push_back({AP_BASE + 47, "ingredient_glowingegg", 1, ITEM_TYPE_INGREDIENT});
    apItems->push_back({AP_BASE + 48, "ingredient_handroll", 1, ITEM_TYPE_RECIPE});
    apItems->push_back({AP_BASE + 49, "ingredient_healingpoultice", 1, ITEM_TYPE_RECIPE});
    apItems->push_back({AP_BASE + 50, "ingredient_heartysoup", 1, ITEM_TYPE_RECIPE});
    apItems->push_back({AP_BASE + 51, "ingredient_hotborscht", 1, ITEM_TYPE_RECIPE});
    apItems->push_back({AP_BASE + 52, "ingredient_hotsoup", 1, ITEM_TYPE_RECIPE});
    apItems->push_back({AP_BASE + 53, "ingredient_icecream", 1, ITEM_TYPE_RECIPE});
    apItems->push_back({AP_BASE + 54, "ingredient_leadershiproll", 1, ITEM_TYPE_RECIPE});
    apItems->push_back({AP_BASE + 55, "ingredient_leafpoultice", 1, ITEM_TYPE_RECIPE});
    apItems->push_back({AP_BASE + 56, "ingredient_leechingpoultice", 1, ITEM_TYPE_RECIPE});
    apItems->push_back({AP_BASE + 57, "ingredient_legendarycake", 1, ITEM_TYPE_RECIPE});
    apItems->push_back({AP_BASE + 58, "ingredient_loafoflife", 1, ITEM_TYPE_RECIPE});
    apItems->push_back({AP_BASE + 59, "ingredient_longlifesoup", 1, ITEM_TYPE_RECIPE});
    apItems->push_back({AP_BASE + 60, "ingredient_magicsoup", 1, ITEM_TYPE_RECIPE});
    apItems->push_back({AP_BASE + 61, "ingredient_mushroom", 2, ITEM_TYPE_INGREDIENT});
    apItems->push_back({AP_BASE + 62, "ingredient_perogi", 1, ITEM_TYPE_RECIPE});
    apItems->push_back({AP_BASE + 63, "ingredient_plantleaf", 1, ITEM_TYPE_INGREDIENT});
    apItems->push_back({AP_BASE + 64, "ingredient_plumpperogi", 1, ITEM_TYPE_RECIPE});
    apItems->push_back({AP_BASE + 65, "ingredient_poisonloaf", 1, ITEM_TYPE_RECIPE});
    apItems->push_back({AP_BASE + 66, "ingredient_poisonsoup", 1, ITEM_TYPE_RECIPE});
    apItems->push_back({AP_BASE + 67, "ingredient_rainbowmushroom", 1, ITEM_TYPE_INGREDIENT});
    apItems->push_back({AP_BASE + 68, "ingredient_rainbowsoup", 1, ITEM_TYPE_RECIPE});
    apItems->push_back({AP_BASE + 69, "ingredient_redberry", 1, ITEM_TYPE_INGREDIENT});
    apItems->push_back({AP_BASE + 70, "ingredient_redbulb", 2, ITEM_TYPE_INGREDIENT});
    apItems->push_back({AP_BASE + 71, "ingredient_rottencake", 1, ITEM_TYPE_RECIPE});
    apItems->push_back({AP_BASE + 72, "ingredient_rottenloaf", 8, ITEM_TYPE_RECIPE});
    apItems->push_back({AP_BASE + 73, "ingredient_rottenmeat", 1, ITEM_TYPE_RECIPE});
    apItems->push_back({AP_BASE + 74, "ingredient_royalsoup", 1, ITEM_TYPE_RECIPE});
    apItems->push_back({AP_BASE + 75, "ingredient_seacake", 1, ITEM_TYPE_RECIPE});
    apItems->push_back({AP_BASE + 76, "ingredient_sealoaf", 1, ITEM_TYPE_RECIPE});
    apItems->push_back({AP_BASE + 77, "ingredient_sharkfinsoup", 1, ITEM_TYPE_RECIPE});
    apItems->push_back({AP_BASE + 78, "ingredient_sightpoultice", 1, ITEM_TYPE_RECIPE});
    apItems->push_back({AP_BASE + 79, "ingredient_smallbone", 2, ITEM_TYPE_INGREDIENT});
    apItems->push_back({AP_BASE + 80, "ingredient_smallegg", 1, ITEM_TYPE_INGREDIENT});
    apItems->push_back({AP_BASE + 81, "ingredient_smalltentacle", 2, ITEM_TYPE_INGREDIENT});
    apItems->push_back({AP_BASE + 82, "ingredient_specialbulb", 1, ITEM_TYPE_INGREDIENT});
    apItems->push_back({AP_BASE + 83, "ingredient_specialcake", 1, ITEM_TYPE_RECIPE});
    apItems->push_back({AP_BASE + 84, "ingredient_spicymeat", 2, ITEM_TYPE_INGREDIENT});
    apItems->push_back({AP_BASE + 85, "ingredient_spicyroll", 1, ITEM_TYPE_RECIPE});
    apItems->push_back({AP_BASE + 86, "ingredient_spicysoup", 1, ITEM_TYPE_RECIPE});
    apItems->push_back({AP_BASE + 87, "ingredient_spiderroll", 1, ITEM_TYPE_RECIPE});
    apItems->push_back({AP_BASE + 88, "ingredient_swampcake", 1, ITEM_TYPE_RECIPE});
    apItems->push_back({AP_BASE + 89, "ingredient_tastycake", 1, ITEM_TYPE_RECIPE});
    apItems->push_back({AP_BASE + 90, "ingredient_tastyroll", 1, ITEM_TYPE_RECIPE});
    apItems->push_back({AP_BASE + 91, "ingredient_toughcake", 1, ITEM_TYPE_RECIPE});
    apItems->push_back({AP_BASE + 92, "ingredient_turtlesoup", 1, ITEM_TYPE_RECIPE});
    apItems->push_back({AP_BASE + 93, "ingredient_vedhaseacrisp", 1, ITEM_TYPE_RECIPE});
    apItems->push_back({AP_BASE + 94, "ingredient_veggiecake", 1, ITEM_TYPE_RECIPE});
    apItems->push_back({AP_BASE + 95, "ingredient_veggieicecream", 1, ITEM_TYPE_RECIPE});
    apItems->push_back({AP_BASE + 96, "ingredient_veggiesoup", 1, ITEM_TYPE_RECIPE});
    apItems->push_back({AP_BASE + 97, "ingredient_volcanoroll", 1, ITEM_TYPE_RECIPE});
    apItems->push_back({AP_BASE + 98, "upgrade_health", 1, ITEM_TYPE_HEALTH});
    apItems->push_back({AP_BASE + 99, "upgrade_wok", 1, ITEM_TYPE_WOK});
    apItems->push_back({AP_BASE + 100, "ingredient_eeloil", 2, ITEM_TYPE_INGREDIENT});
    apItems->push_back({AP_BASE + 101, "ingredient_fishmeat", 2, ITEM_TYPE_INGREDIENT});
    apItems->push_back({AP_BASE + 102, "ingredient_fishoil", 3, ITEM_TYPE_INGREDIENT});
    apItems->push_back({AP_BASE + 103, "ingredient_glowingegg", 2, ITEM_TYPE_INGREDIENT});
    apItems->push_back({AP_BASE + 104, "ingredient_healingpoultice", 2, ITEM_TYPE_RECIPE});
    apItems->push_back({AP_BASE + 105, "ingredient_hotsoup", 2, ITEM_TYPE_RECIPE});
    apItems->push_back({AP_BASE + 106, "ingredient_leadershiproll", 2, ITEM_TYPE_RECIPE});
    apItems->push_back({AP_BASE + 107, "ingredient_leafpoultice", 3, ITEM_TYPE_RECIPE});
    apItems->push_back({AP_BASE + 108, "ingredient_plantleaf", 2, ITEM_TYPE_INGREDIENT});
    apItems->push_back({AP_BASE + 109, "ingredient_plantleaf", 3, ITEM_TYPE_INGREDIENT});
    apItems->push_back({AP_BASE + 110, "ingredient_rottenmeat", 2, ITEM_TYPE_INGREDIENT});
    apItems->push_back({AP_BASE + 111, "ingredient_rottenmeat", 8, ITEM_TYPE_INGREDIENT});
    apItems->push_back({AP_BASE + 112, "ingredient_sealoaf", 2, ITEM_TYPE_RECIPE});
    apItems->push_back({AP_BASE + 113, "ingredient_smallbone", 3, ITEM_TYPE_INGREDIENT});
    apItems->push_back({AP_BASE + 114, "ingredient_smallegg", 2, ITEM_TYPE_INGREDIENT});
    apItems->push_back({AP_BASE + 115, "song_li", 1, ITEM_TYPE_SONG});
    apItems->push_back({AP_BASE + 116, "song_shield", 1, ITEM_TYPE_SONG});
    apItems->push_back({AP_BASE + 117, "song_beast", 1, ITEM_TYPE_SONG});
    apItems->push_back({AP_BASE + 118, "song_sun", 1, ITEM_TYPE_SONG});
    apItems->push_back({AP_BASE + 119, "song_nature", 1, ITEM_TYPE_SONG});
    apItems->push_back({AP_BASE + 120, "song_energy", 1, ITEM_TYPE_SONG});
    apItems->push_back({AP_BASE + 121, "song_bind", 1, ITEM_TYPE_SONG});
    apItems->push_back({AP_BASE + 122, "song_fish", 1, ITEM_TYPE_SONG});
    apItems->push_back({AP_BASE + 123, "song_spirit", 1, ITEM_TYPE_SONG});
    apItems->push_back({AP_BASE + 124, "song_dual", 1, ITEM_TYPE_SONG});
    apItems->push_back({AP_BASE + 125, "transport_veil01", 1, ITEM_TYPE_TRANSTURTLE});
    apItems->push_back({AP_BASE + 126, "transport_veil02", 1, ITEM_TYPE_TRANSTURTLE});
    apItems->push_back({AP_BASE + 127, "transport_openwater03", 1, ITEM_TYPE_TRANSTURTLE});
    apItems->push_back({AP_BASE + 128, "transport_forest04", 1, ITEM_TYPE_TRANSTURTLE});
    apItems->push_back({AP_BASE + 129, "transport_mainarea", 1, ITEM_TYPE_TRANSTURTLE});
    apItems->push_back({AP_BASE + 130, "transport_abyss03", 1, ITEM_TYPE_TRANSTURTLE});
    apItems->push_back({AP_BASE + 131, "transport_finalboss", 1, ITEM_TYPE_TRANSTURTLE});
    apItems->push_back({AP_BASE + 132, "transport_forest05", 1, ITEM_TYPE_TRANSTURTLE});
    apItems->push_back({AP_BASE + 133, "transport_seahorse", 1, ITEM_TYPE_TRANSTURTLE});
    apItems->push_back({AP_BASE + 134, "door_to_cathedral", 1, ITEM_TYPE_DOOR});
    apItems->push_back({AP_BASE + 135, "trap_poison", 1, ITEM_TYPE_TRAP});
    apItems->push_back({AP_BASE + 136, "trap_blind", 1, ITEM_TYPE_TRAP});
    apItems->push_back({AP_BASE + 137, "trap_rainbow", 1, ITEM_TYPE_TRAP});
    apItems->push_back({AP_BASE + 138, "trap_mute", 1, ITEM_TYPE_TRAP});
    apItems->push_back({AP_BASE + 139, "progressive_recipe_loaf", 1, ITEM_TYPE_RECIPE});
    apItems->push_back({AP_BASE + 140, "progressive_recipe_soup", 1, ITEM_TYPE_RECIPE});
    apItems->push_back({AP_BASE + 141, "progressive_recipe_cake", 1, ITEM_TYPE_RECIPE});
    apItems->push_back({AP_BASE + 142, "progressive_recipe_poultice", 1, ITEM_TYPE_RECIPE});
    apItems->push_back({AP_BASE + 143, "progressive_recipe_roll", 1, ITEM_TYPE_RECIPE});
    apItems->push_back({AP_BASE + 144, "progressive_recipe_perogi", 1, ITEM_TYPE_RECIPE});
    apItems->push_back({AP_BASE + 145, "progressive_recipe_ice_cream", 1, ITEM_TYPE_RECIPE});
    apItems->push_back({AP_BASE + 146, "door_to_body", 1, ITEM_TYPE_DOOR});

}
/**
 * Initialise every aplocation_t element of the apLocations list
 */
void RandomizerArchipelago::initialiseApLocations() {
    apLocations->push_back({AP_BASE + 0, "bulb_turtlecave"});
    apLocations->push_back({AP_BASE + 1, "bulb_openwater_tl_1"});
    apLocations->push_back({AP_BASE + 2, "bulb_openwater_tl_2"});
    apLocations->push_back({AP_BASE + 3, "bulb_openwater_tl_3"});
    apLocations->push_back({AP_BASE + 4, "bulb_openwater_tr_1"});
    apLocations->push_back({AP_BASE + 5, "bulb_openwater_tr_2"});
    apLocations->push_back({AP_BASE + 6, "bulb_openwater_tr_3"});
    apLocations->push_back({AP_BASE + 7, "bulb_openwater_tr_4"});
    apLocations->push_back({AP_BASE + 8, "bulb_openwater_tr_5"});
    apLocations->push_back({AP_BASE + 9, "bulb_openwater_tr_6"});
    apLocations->push_back({AP_BASE + 10, "bulb_openwater_bl_1"});
    apLocations->push_back({AP_BASE + 11, "bulb_openwater_bl_2"});
    apLocations->push_back({AP_BASE + 12, "bulb_skeleton_path_1"});
    apLocations->push_back({AP_BASE + 13, "bulb_skeleton_path_2"});
    apLocations->push_back({AP_BASE + 14, "bulb_arnassi_1"});
    apLocations->push_back({AP_BASE + 15, "bulb_arnassi_2"});
    apLocations->push_back({AP_BASE + 16, "bulb_arnassi_3"});
    apLocations->push_back({AP_BASE + 17, "bulb_sunworm_1"});
    apLocations->push_back({AP_BASE + 18, "bulb_sunworm_2"});
    apLocations->push_back({AP_BASE + 19, "bulb_sunworm_3"});
    apLocations->push_back({AP_BASE + 20, "bulb_sunworm_4"});
    apLocations->push_back({AP_BASE + 21, "bulb_tutorial_1"});
    apLocations->push_back({AP_BASE + 22, "bulb_tutorial_2"});
    apLocations->push_back({AP_BASE + 23, "bulb_tutorial_3"});
    apLocations->push_back({AP_BASE + 24, "bulb_abyss_l_1"});
    apLocations->push_back({AP_BASE + 25, "bulb_abyss_l_2"});
    apLocations->push_back({AP_BASE + 26, "bulb_abyss_l_3"});
    apLocations->push_back({AP_BASE + 27, "bulb_energy_temple_1_1"});
    apLocations->push_back({AP_BASE + 28, "bulb_energy_temple_2_1"});
    apLocations->push_back({AP_BASE + 29, "bulb_energy_temple_3_1"});
    apLocations->push_back({AP_BASE + 30, "bulb_mithalas_city_01"});
    apLocations->push_back({AP_BASE + 31, "bulb_mithalas_city_02"});
    apLocations->push_back({AP_BASE + 32, "bulb_mithalas_city_03"});
    apLocations->push_back({AP_BASE + 33, "bulb_mithalas_city_04"});
    apLocations->push_back({AP_BASE + 34, "bulb_mithalas_city_05"});
    apLocations->push_back({AP_BASE + 35, "bulb_mithalas_city_06"});
    apLocations->push_back({AP_BASE + 36, "bulb_mithalas_city_07"});
    apLocations->push_back({AP_BASE + 37, "bulb_mithalas_city_08"});
    apLocations->push_back({AP_BASE + 38, "bulb_mithalas_city_09"});
    apLocations->push_back({AP_BASE + 39, "bulb_mithalas_city_10"});
    apLocations->push_back({AP_BASE + 40, "bulb_mithalas_city_11"});
    apLocations->push_back({AP_BASE + 41, "bulb_mithalas_city_12"});
    apLocations->push_back({AP_BASE + 42, "bulb_cathedral_l_2"});
    apLocations->push_back({AP_BASE + 43, "bulb_boilerroom_1"});
    apLocations->push_back({AP_BASE + 44, "bulb_forest_tl_1"});
    apLocations->push_back({AP_BASE + 45, "bulb_forest_tl_2"});
    apLocations->push_back({AP_BASE + 46, "bulb_forest_tl_3"});
    apLocations->push_back({AP_BASE + 47, "bulb_forest_tl_4"});
    apLocations->push_back({AP_BASE + 48, "bulb_forest_tr_1"});
    apLocations->push_back({AP_BASE + 49, "bulb_forest_tr_2"});
    apLocations->push_back({AP_BASE + 50, "bulb_forest_tr_3"});
    apLocations->push_back({AP_BASE + 51, "bulb_forest_tr_4"});
    apLocations->push_back({AP_BASE + 52, "bulb_forest_tr_5"});
    apLocations->push_back({AP_BASE + 53, "bulb_forest_tr_6"});
    apLocations->push_back({AP_BASE + 54, "bulb_forest_bl_1"});
    apLocations->push_back({AP_BASE + 55, "bulb_forest_boss_room_1"});
    apLocations->push_back({AP_BASE + 56, "bulb_forest_sprite_cave_1"});
    apLocations->push_back({AP_BASE + 57, "bulb_forest_sprite_cave_2"});
    apLocations->push_back({AP_BASE + 58, "bulb_home_water_1"});
    apLocations->push_back({AP_BASE + 59, "bulb_home_water_2"});
    apLocations->push_back({AP_BASE + 60, "bulb_home_water_3"});
    apLocations->push_back({AP_BASE + 61, "bulb_home_water_4"});
    apLocations->push_back({AP_BASE + 62, "bulb_home_water_5"});
    apLocations->push_back({AP_BASE + 63, "bulb_home_water_6"});
    apLocations->push_back({AP_BASE + 64, "bulb_home_water_7"});
    apLocations->push_back({AP_BASE + 65, "bulb_home_water_8"});
    apLocations->push_back({AP_BASE + 66, "bulb_final_l_1"});
    apLocations->push_back({AP_BASE + 67, "bulb_final_l_2"});
    apLocations->push_back({AP_BASE + 68, "bulb_final_l_3"});
    apLocations->push_back({AP_BASE + 69, "bulb_final_l_4"});
    apLocations->push_back({AP_BASE + 70, "bulb_final_l_5"});
    apLocations->push_back({AP_BASE + 71, "bulb_song_cave_1"});
    apLocations->push_back({AP_BASE + 72, "bulb_song_cave_2"});
    apLocations->push_back({AP_BASE + 73, "bulb_song_cave_3"});
    apLocations->push_back({AP_BASE + 74, "bulb_song_cave_4"});
    apLocations->push_back({AP_BASE + 75, "bulb_song_cave_5"});
    apLocations->push_back({AP_BASE + 76, "bulb_veil_tl_1"});
    apLocations->push_back({AP_BASE + 77, "bulb_veil_tl_2"});
    apLocations->push_back({AP_BASE + 78, "bulb_veil_tl_3"});
    apLocations->push_back({AP_BASE + 79, "bulb_veil_tr_1"});
    apLocations->push_back({AP_BASE + 80, "bulb_veil_tr_2"});
    apLocations->push_back({AP_BASE + 81, "bulb_veil_b_1"});
    apLocations->push_back({AP_BASE + 82, "bulb_veil_b_2"});
    apLocations->push_back({AP_BASE + 83, "bulb_ice_cave_1"});
    apLocations->push_back({AP_BASE + 84, "bulb_ice_cave_2"});
    apLocations->push_back({AP_BASE + 85, "bulb_ice_cave_3"});
    apLocations->push_back({AP_BASE + 86, "bulb_ice_cave_4"});
    apLocations->push_back({AP_BASE + 87, "bulb_ice_cave_5"});
    apLocations->push_back({AP_BASE + 88, "bulb_king_jellyfish_cave_1"});
    apLocations->push_back({AP_BASE + 89, "bulb_bubble_cave_1"});
    apLocations->push_back({AP_BASE + 90, "bulb_bubble_cave_2"});
    apLocations->push_back({AP_BASE + 91, "bulb_sun_temple_1"});
    apLocations->push_back({AP_BASE + 92, "bulb_sun_temple_2"});
    apLocations->push_back({AP_BASE + 93, "bulb_sun_temple_3"});
    apLocations->push_back({AP_BASE + 94, "bulb_sun_temple_4"});
    apLocations->push_back({AP_BASE + 95, "bulb_sun_temple_5"});
    apLocations->push_back({AP_BASE + 96, "bulb_sun_temple_6"});
    apLocations->push_back({AP_BASE + 97, "bulb_final_c_1"});
    apLocations->push_back({AP_BASE + 98, "bulb_final_r_1"});
    apLocations->push_back({AP_BASE + 99, "bulb_final_r_2"});
    apLocations->push_back({AP_BASE + 100, "bulb_final_r_3"});
    apLocations->push_back({AP_BASE + 101, "bulb_final_b_1"});
    apLocations->push_back({AP_BASE + 102, "bulb_final_b_2"});
    apLocations->push_back({AP_BASE + 103, "bulb_final_boss_1"});
    apLocations->push_back({AP_BASE + 104, "bulb_final_boss_2"});
    apLocations->push_back({AP_BASE + 105, "bulb_final_boss_3"});
    apLocations->push_back({AP_BASE + 106, "bulb_final_boss_4"});
    apLocations->push_back({AP_BASE + 107, "bulb_starting_cave_1"});
    apLocations->push_back({AP_BASE + 108, "bulb_starting_cave_2"});
    apLocations->push_back({AP_BASE + 109, "bulb_abyss_r_1"});
    apLocations->push_back({AP_BASE + 110, "bulb_abyss_r_2"});
    apLocations->push_back({AP_BASE + 111, "bulb_abyss_r_3"});
    apLocations->push_back({AP_BASE + 112, "bulb_abyss_r_4"});
    apLocations->push_back({AP_BASE + 113, "bulb_cathedral_under_ground_1"});
    apLocations->push_back({AP_BASE + 114, "bulb_cathedral_under_ground_2"});
    apLocations->push_back({AP_BASE + 115, "bulb_cathedral_under_ground_3"});
    apLocations->push_back({AP_BASE + 116, "bulb_cathedral_under_ground_4"});
    apLocations->push_back({AP_BASE + 117, "bulb_cathedral_under_ground_5"});
    apLocations->push_back({AP_BASE + 118, "bulb_cathedral_under_ground_6"});
    apLocations->push_back({AP_BASE + 119, "bulb_naija_home_1"});
    apLocations->push_back({AP_BASE + 120, "bulb_naija_home_2"});
    apLocations->push_back({AP_BASE + 121, "bulb_mermog_cave_1"});
    apLocations->push_back({AP_BASE + 122, "bulb_octo_cave_1"});
    apLocations->push_back({AP_BASE + 123, "urn_mithalas_city_1"});
    apLocations->push_back({AP_BASE + 124, "urn_mithalas_city_2"});
    apLocations->push_back({AP_BASE + 125, "urn_mithalas_city_3"});
    apLocations->push_back({AP_BASE + 126, "urn_mithalas_city_4"});
    apLocations->push_back({AP_BASE + 127, "urn_mithalas_city_5"});
    apLocations->push_back({AP_BASE + 128, "urn_mithalas_city_6"});
    apLocations->push_back({AP_BASE + 129, "urn_mithalas_city_7"});
    apLocations->push_back({AP_BASE + 130, "urn_cathedral_l_1"});
    apLocations->push_back({AP_BASE + 131, "urn_cathedral_l_2"});
    apLocations->push_back({AP_BASE + 132, "urn_cathedral_l_3"});
    apLocations->push_back({AP_BASE + 133, "urn_cathedral_l_4"});
    apLocations->push_back({AP_BASE + 134, "urn_cathedral_l_5"});
    apLocations->push_back({AP_BASE + 135, "urn_cathedral_l_6"});
    apLocations->push_back({AP_BASE + 136, "urn_cathedral_r_01"});
    apLocations->push_back({AP_BASE + 137, "urn_cathedral_r_02"});
    apLocations->push_back({AP_BASE + 138, "urn_cathedral_r_03"});
    apLocations->push_back({AP_BASE + 139, "urn_cathedral_r_04"});
    apLocations->push_back({AP_BASE + 140, "urn_cathedral_r_05"});
    apLocations->push_back({AP_BASE + 141, "urn_cathedral_r_06"});
    apLocations->push_back({AP_BASE + 142, "urn_cathedral_r_07"});
    apLocations->push_back({AP_BASE + 143, "urn_cathedral_r_08"});
    apLocations->push_back({AP_BASE + 144, "urn_cathedral_r_09"});
    apLocations->push_back({AP_BASE + 145, "urn_cathedral_r_10"});
    apLocations->push_back({AP_BASE + 146, "urn_cathedral_r_11"});
    apLocations->push_back({AP_BASE + 147, "urn_cathedral_r_12"});
    apLocations->push_back({AP_BASE + 148, "urn_openwater_tr_1"});
    apLocations->push_back({AP_BASE + 149, "urn_openwater_tr_2"});
    apLocations->push_back({AP_BASE + 150, "urn_openwater_tr_3"});
    apLocations->push_back({AP_BASE + 151, "crate_sunkencity_2_1"});
    apLocations->push_back({AP_BASE + 152, "crate_sunkencity_2_2"});
    apLocations->push_back({AP_BASE + 153, "crate_sunkencity_2_3"});
    apLocations->push_back({AP_BASE + 154, "crate_sunkencity_1_1"});
    apLocations->push_back({AP_BASE + 155, "crate_sunkencity_1_2"});
    apLocations->push_back({AP_BASE + 156, "beating_simon"});
    apLocations->push_back({AP_BASE + 157, "health_egg_1"});
    apLocations->push_back({AP_BASE + 158, "health_egg_2"});
    apLocations->push_back({AP_BASE + 159, "health_egg_3"});
    apLocations->push_back({AP_BASE + 160, "health_egg_4"});
    apLocations->push_back({AP_BASE + 161, "health_egg_5"});
    apLocations->push_back({AP_BASE + 162, "collect_anemone"});
    apLocations->push_back({AP_BASE + 163, "collect_energy_temple"});
    apLocations->push_back({AP_BASE + 164, "collect_arnassi_statue"});
    apLocations->push_back({AP_BASE + 165, "collect_mithalas_banner"});
    apLocations->push_back({AP_BASE + 166, "collect_bio_seed"});
    apLocations->push_back({AP_BASE + 167, "collect_blackpearl"});
    apLocations->push_back({AP_BASE + 168, "collect_treasure_chest"});
    apLocations->push_back({AP_BASE + 169, "collect_energy_boss"});
    apLocations->push_back({AP_BASE + 170, "collect_energy_statue"});
    apLocations->push_back({AP_BASE + 171, "collect_golden_gear"});
    apLocations->push_back({AP_BASE + 172, "collect_jelly_plant"});
    apLocations->push_back({AP_BASE + 173, "collect_mithala_doll"});
    apLocations->push_back({AP_BASE + 174, "collect_mithalas_pot"});
    apLocations->push_back({AP_BASE + 175, "collect_big_seed"});
    apLocations->push_back({AP_BASE + 176, "collect_seed_bag"});
    apLocations->push_back({AP_BASE + 177, "collect_skull"});
    apLocations->push_back({AP_BASE + 178, "collect_jelly_beacon"});
    apLocations->push_back({AP_BASE + 179, "collect_spore_seed"});
    apLocations->push_back({AP_BASE + 180, "collect_gold_star"});
    apLocations->push_back({AP_BASE + 181, "collect_stone_head"});
    apLocations->push_back({AP_BASE + 182, "collect_sun_key"});
    apLocations->push_back({AP_BASE + 183, "collect_trident_head"});
    apLocations->push_back({AP_BASE + 184, "collect_turtle_egg"});
    apLocations->push_back({AP_BASE + 185, "collect_upsidedown_seed"});
    apLocations->push_back({AP_BASE + 186, "collect_walker"});
    apLocations->push_back({AP_BASE + 187, "collect_crab_costume"});
    apLocations->push_back({AP_BASE + 188, "collect_jelly_costume"});
    apLocations->push_back({AP_BASE + 189, "collect_mithalan_costume"});
    apLocations->push_back({AP_BASE + 190, "collect_mutant_costume"});
    apLocations->push_back({AP_BASE + 191, "collect_seahorse_costume"});
    apLocations->push_back({AP_BASE + 192, "collect_teen_costume"});
    apLocations->push_back({AP_BASE + 193, "collect_urchin_costume"});
    apLocations->push_back({AP_BASE + 194, "collect_nautilus"});
    apLocations->push_back({AP_BASE + 195, "collect_blaster"});
    apLocations->push_back({AP_BASE + 196, "collect_dumbo"});
    apLocations->push_back({AP_BASE + 197, "collect_piranha"});
    apLocations->push_back({AP_BASE + 198, "urn_cathedral_r_13"});
    apLocations->push_back({AP_BASE + 199, "li_cave"});
    apLocations->push_back({AP_BASE + 200, "song_shield_hint"});
    apLocations->push_back({AP_BASE + 201, "breaking_li_cage"});
    apLocations->push_back({AP_BASE + 202, "beating_mithalas"});
    apLocations->push_back({AP_BASE + 203, "beating_sun_god"});
    apLocations->push_back({AP_BASE + 204, "beating_drunian_god"});
    apLocations->push_back({AP_BASE + 205, "beating_energy_statue"});
    apLocations->push_back({AP_BASE + 206, "erulian_spirit"});
    apLocations->push_back({AP_BASE + 207, "fish_cave_puzzle"});
    apLocations->push_back({AP_BASE + 208, "beating_priests"});
    apLocations->push_back({AP_BASE + 209, "transturtle_veil01"});
    apLocations->push_back({AP_BASE + 210, "transturtle_veil02"});
    apLocations->push_back({AP_BASE + 211, "transturtle_openwater03"});
    apLocations->push_back({AP_BASE + 212, "transturtle_forest04"});
    apLocations->push_back({AP_BASE + 213, "transturtle_mainarea"});
    apLocations->push_back({AP_BASE + 214, "transturtle_abyss03"});
    apLocations->push_back({AP_BASE + 215, "transturtle_finalboss"});
    apLocations->push_back({AP_BASE + 216, "transturtle_forest05"});
    apLocations->push_back({AP_BASE + 217, "transturtle_seahorse"});
    apLocations->push_back({AP_BASE + 218, "sitting_on_throne"});
    apLocations->push_back({AP_BASE + 219, "beating_golem"});
}
