/**
 * @author      : Louis M (prog@tioui.com)
 * @created     : Fri, 08 Mar 2024 19:51:46 +0000
 * @license     : MIT
 * Class that encapsulate Archipelago server randomization
 */



#ifndef RANDOMIZER_ARCHIPELAGO_H

#define RANDOMIZER_ARCHIPELAGO_H

#include "Randomizer.h"
#include <map>
#include "subprojects/apclientpp/apclient.hpp"

/**
 * Used to communicate with the Archipelago server
 */
class APClient;

/**
 * A type of Item
 */
enum ItemType {
    ITEM_TYPE_INGREDIENT,
    ITEM_TYPE_RECIPE,
    ITEM_TYPE_COLLECTIBLE,
    ITEM_TYPE_HEALTH,
    ITEM_TYPE_WOK,
    ITEM_TYPE_SONG,
    ITEM_TYPE_TRANSTURTLE,
    ITEM_TYPE_DOOR
};

/**
 * Used to link Item of Archipelago to the Check of the Randomizer base class
 */
typedef struct apItem {
    int64_t itemId;
    std::string item;
    int count;
    ItemType type;
} apitem_t;

/**
 * Used to link Location of Archipelago to the Check of the Randomizer base class
 */
typedef struct apLocation {
    int64_t locationId;
    std::string name;
} aplocation_t;


/**
 * The color to used in a segment of server text
 */
typedef enum ServerTextColor {
    SERVER_TEXT_COLOR_NORMAL,
    SERVER_TEXT_COLOR_USER,
    SERVER_TEXT_COLOR_LOCATION,
    SERVER_TEXT_COLOR_TRAP_ITEM,
    SERVER_TEXT_COLOR_FILLER_ITEM,
    SERVER_TEXT_COLOR_USEFUL_ITEM,
    SERVER_TEXT_COLOR_PROGRESSION_ITEM,
    SERVER_TEXT_COLOR_LOCATION_FOUND,
    SERVER_TEXT_COLOR_LOCATION_NOT_FOUND
} ServerTextColor_t;

/**
 * The information about a server text segment to show to the screen
 */
typedef struct serverSegmentTextInfo {
    ServerTextColor_t color;
    std::string text;
} serverSegmentTextInfo_t;

/**
 * A server text segment to show to the screen
 */
typedef struct serverSegmentText {
    TTFText *text;
    float width;
} serverSegmentText_t;


/**
 * A server text line to show to the screen
 */
typedef struct serverText {
    std::vector<serverSegmentText_t *> segments;
    std::vector<serverSegmentTextInfo_t *> *segmentInfos;
    RenderObject *background;
    float height;
    std::time_t time;
    bool shown;
} serverText_t;

#define PRINT_SERVER_TEXT_DELAY 3
#define PRINT_SERVER_TEXT_BETWEEN_DELAY 1


/**
 * A randomizer for the Archipelago system
 */
class RandomizerArchipelago : public Randomizer {

public:



    /**
     * Constructor that does not connect to a server
     * @param seedNumber
     */
    explicit RandomizerArchipelago(std::string seedNumber);

    /**
     * Constructor that connect to an Archipelago server
     * @param server The address and port of the Archipelago server
     * @param name The player name on the archipelago server
     * @param password The password of the room on the archipelago server
     * @param selfMessage the user want only server message for or from himself.
     * @param noChat The user don't want any chat message from server.
     * @param deathLink True if Archipelago Death link packets should be used.
     * @param userDataFolder The data to store user informations.
     */
    explicit RandomizerArchipelago(const std::string& server, const std::string& name, const std::string& password,
                                   bool selfMessage, bool noChat, bool deathLink, std::string userDataFolder);

    /**
     * Destructor of the current object
     */
    ~RandomizerArchipelago() override;

    /**
     * Try to connect to the server (try secure and not secure unless specified)
     *
     * @param server The server URI (including port number
     */
    void tryConnection(const std::string& server);

    /**
     * Activate a randomizer check
     * @param check The check to activate
    */
    void activateCheck(std::string check) override;

    /**
     * Lunched at each game loop iteration
     */
    void update() override;

    /**
     * Launched when the game is ending
     */
    void endingGame() override;

    /**
     * A new or saves game has been load
     * @param newGame True if a new game is launched.
     */
    void onLoad(bool newGame) override;

    /**
     * When a game is closing a game (return to menu).
     */
    void onClose() override;

    /**
     * Show a quick message on the screen.
     * @param text The text to show
     */
    void showQuickMessage(const std::string &aText) override;

    /**
     * Launched when a scene is loading
     *
     * @param scene The scene name that is loading
     */
    void onLoadScene(std::string scene) override;

    /**
     * Is the final boss is accessible.
     * @return True if the final boss is accessible. False if not.
     */
    bool accessFinalBoss() override;

    /**
     * Show what is missing to access the final boss.
     */
    bool showHintFinalBoss() override;

    /**
     * The unique String for the Randomizer
     * @return The String of the Randomizer
     */
    std::string getUniqueString() override;

    /**
     * Add information about locations in `data`.
     *
     * @param data Where the information about item should be put.
     */
    void appendLocationsHelpData(std::string &data) override;

    /**
     * When a game state is removed
     */
    void removeState() override;

protected:

    /**
     * Get a new ingredient to receive in the local game
     * @param ingredientName The name of the ingredient to receive
     * @param count The number of ingredient to receive
     */
    void receivingIngredient(const std::string& ingredientName, int count) override;

    /**
     * Received an health upgrade
     */
    void receivingUpgradeHealth() override;

    /**
     * Check if it is the end of the four gods run
     */
    void manageFourGodsEnding() override;

private:

    /**
     * Constructor that does not connect to a server
     */
    RandomizerArchipelago();

    /**
     * Unique identifier of the `apClient`
     */
    std::string uuid;

    /**
     * Used to communicate with the Archipelago server
     */
    APClient *apClient;

    /**
     * The address of the Archipelago server
     */
    std::string serverAddress;

    /**
     * The username of the Archipelago Player
     */
    std::string name;

    /**
     * The password of the Archipelago multiworld game
     */
    std::string password;

    /**
     * True if the Archipelago server is connected
     */
    int connected;

    /**
     * True if the room info message has received from the Archipelago server
     */
    int hasRoomInfo;

    /**
     * True if the room info message has received from the Archipelago server
     */
    int hasSlotInfo;

    /**
     * A sync has been asked
     */
    bool syncing;

    /**
     * Is the current Slot have the death link enable.
     */
    bool deathLink;

    /**
     * Pause the death link management, waiting for Naija to get back on her feets (so to speak)
     */
    bool deathLinkPause;

    /**
     * Every item of the Arcipelago Randomizer
     */
    std::vector<apitem_t> *apItems;

    /**
     * Every location of the Arcipelago Randomizer
     */
    std::vector<aplocation_t> *apLocations;

    /**
     * The time start of the presently shown quick message
     */
    std::time_t currentQuickMessageTime;

    /**
     * A quick message recently showed in game.
     */
    std::queue<std::string> *nextQuickMessages;

    /**
     * Set every APClient callback
     */
    void initialiseCallback();

    /**
     * Initialise every apitem_t element of the apItems list
     */
    void initialiseApItems();

    /**
     * Initialise every aplocation_t element of the apLocations list
     */
    void initialiseApLocations();

    /**
     * Launched when a data storage retreive message has been received.
     * @param map Contain the key and json value in the datas torage
     */
    void onDataStorageRetreived(const std::map<std::string,nlohmann::json>& map);

    /**
     * Launched when the socket has been connected to the Archipelago server
     */
    void onSocketConnected();

    /**
     * Launched when the socket has been disconnected to the Archipelago server
     */
    void onSocketDisconnected();

    /**
     * Launched when the Archipelago send Room Info message
     */
    void onRoomInfoHandler();

    /**
     * Initialise the goal options
     *
     * @param jsonText The "slot_data" json file
     */
    void initialiseGoal(const nlohmann::json& jsonText);

    /**
    * Initialise the standard options
    *
    * @param jsonText The "slot_data" json file
    */
    void initialiseOptions(const nlohmann::json& jsonText);

    /**
     * Launched when a slot has been connected.
     * @param jsonText The "slot_data" json file
     */
    void onSlotConnected (const nlohmann::json& jsonText);

    /**
     * Launched when a socket error is detected.
     * \param text The error message
     */
    void onSockerError (const std::string& text);

    /**
     * Launched when a connection to an archipelago slot has been refused
     * \param texts Every messages
     */
    void onSlotRefused (const std::list<std::string>& texts);

    /**
     * Launched when the Archipelago send some new items to received
     * @param items A list of item to received
     */
    void onItemsReceived (const std::list<APClient::NetworkItem>& items);

    /**
     * Launched when the Archipelago send some new message th show
     * @param json The message th show
     */
    void onPrintJson (const APClient::PrintJSONArgs& json);

    /**
     * Launched when the Archipelago server send a bounce message
     * @param json The message
     */
    void onBounceMessageReceived (const nlohmann::json& json);

    /**
     * Translate a TextNode from `onPrintJson` to a showable text
     * @param node The TextNode to translate
     * @return The translated text
     */
    std::string translateJsonDataToString(const APClient::TextNode& ande);

    /**
     * Get an apitem_t from the Id of the Item
     * @param id The id of the item
     * @return The apitem_t associate to the ID
     */
    apitem_t *getApItemById(int64_t id);

    /**
     * Update the APClient to handle items.
     * @param noMutex Do not use mutex protection in the update
     */
    void connectionUpdate(bool noMutex = false);

    /**
     * The mutex used to synchrnize the apClient.
     */
    std::mutex apMutex;

    /**
     * Show only message from AP Server that are related to the current player
     */
    bool selfMessageOnly;

    /**
     * Don't show chat message from AP Server
     */
    bool noChatMessage;

    /**
     * True if the server has been disconnected and is trying to reconnect.
     */
    bool hasBeenDisconnected;

    /**
     * Check if the Text node is related to the current player.
     * @param aData The text node
     * @return True if the text node is related to the current player
     */
    bool selfRelatedJson(const std::list<APClient::TextNode>& aData);

    /**
     * The types of items in each location.
     */
    std::vector<int> *locationsItemTypes;

    /**
     * Save information about the Archipelago slot. Usefull if the user want to play offline.
     */
    void saveConnectionInfo();

    /**
     * Load information about the Archipelago slot. Usefull if the user want to play offline.
     */
    void loadConnectionInfo();

    /**
     * Update the Archipelago server data storage to put new values in it.
     * @param unconditional True if the value is assing even if it was not modified from before assignment
     */
    void updateDataStorage(bool unconditional = false);

    /**
     * Update the `dataStorageInfo` using data in the Archipelago data storage.
     */
    void updateDataStorageInfo();

    /**
     * Set a single Archipelago data storage value
     * @param id The ID of the key
     * @param value The value to set
     * @param unconditional True if the value is assing even if it was not modified from before assignment
     */
    void setDataStorage(std::string id, int value, bool unconditional);

    /**
     * Initialise the `dataStorageInfo` to default values
     */
    void initialisedDataStorageInfo();

    /**
     * A reply to an AP location scout message
     * @param aItems Every items that has been scout
     */
    void onLocationInfo(const std::list<APClient::NetworkItem>& aItems);

    /**
     * True if the player is playing offline
     */
    bool isOffline;

    /**
     * Every flags that has been send to Archipelago data storage
     */
    std::unordered_map<std::string, int> *dataStorageInfo;

    /**
     * Every scene name translated to area name
     */
    std::unordered_map<std::string, std::string> *areaInfo;

    /**
     * The last area send to tracker
     */
    std::string lastArea;

    /**
     * Initialise the values in areaInfo
     */
    void initialiseAreaInfo();

    /**
     * Goal has been send
     */
    bool isGoal;

    /**
     * The four gods goal message has been shown
     */
    bool fourGodsGoalMessage;

    /**
     * The throne as location is managed by the server
     */
    bool throneAsLocationManagedByServer;

    /**
     * Every item of the Arcipelago Randomizer
     */
    std::vector<serverText_t *> *serverTexts;

    /**
     * Print some line segments back to back to make a complete line
     * @param segments The segments to print as a line
     */
    void printServerText(std::vector<serverSegmentTextInfo_t *> *segments);

    /**
     * Create the visual element of a server text
     * @param aServerText The information of the server text
     */
    void createServerTextRenderObjects(serverText_t *aServerText);

    /**
     * Update the drawing of every server textx
     */
    void updatePrintServerText();

    /**
     * Clear the content of the `serverTexts` list
     */
    void emptyServerText();

    /**
     * The timestamp when the game state is removed
     */
    int removeStateTick;

};

const int FLAG_SUNTEMPLE_LIGHTCRYSTAL            = 112;

const int FLAG_SAVE_HAS_INFO                     = 1500;
const int FLAG_SAVE_AQUARIAN_TRANSLATE           = 1501;
const int FLAG_SAVE_SECRET_NEEDED                = 1502;
const int FLAG_SAVE_MINI_BOSSES_TO_KILLED        = 1503;
const int FLAG_SAVE_BIG_BOSSES_TO_KILLED         = 1504;
const int FLAG_SAVE_INFINITE_HOT_SOUP            = 1505;
const int FLAG_SAVE_MAX_INGREDIENTS_AMOUNT       = 1506;
const int FLAG_SAVE_RANDOMIZED_INGREDIENTS_SIZE  = 1520;
const int FLAG_SAVE_RANDOMIZED_INGREDIENTS_START = 1521;
const int FLAG_SAVE_RANDOMIZED_INGREDIENTS_END   = 1599;

const int FLAG_SAVE_LOCATION_ITEM_TYPES_SIZE     = 1600;
const int FLAG_SAVE_LOCATION_ITEM_TYPES_START    = 1601;
const int FLAG_SAVE_LOCATION_ITEM_TYPES_END      = 1999;

// Identifier for the `dataStorageInfo`
#define ID_MINIBOSS_NAUTILUSPRIME "miniboss_nautilusprime"
#define ID_MINIBOSS_KINGJELLY "miniboss_kingjelly"
#define ID_MINIBOSS_MERGOG "miniboss_mergog"
#define ID_MINIBOSS_CRAB "miniboss_crab"
#define ID_MINIBOSS_OCTOMUN "miniboss_octomun"
#define ID_MINIBOSS_MANTISSHRIMP "miniboss_mantisshrimp"
#define ID_MINIBOSS_PRIESTS "miniboss_priests"
#define ID_MINIBOSS_BLASTER "miniboss_blaster"
#define ID_ENERGYBOSSDEAD "energybossdead"
#define ID_SUNKENCITY_BOSS "sunkencity_boss"
#define ID_BOSS_FOREST "boss_forest"
#define ID_BOSS_MITHALA "boss_mithala"
#define ID_BOSS_SUNWORM "boss_sunworm"
#define ID_REMOVE_TONGUE "tongue_removed"
#define ID_SECRET01 "secret01"
#define ID_SECRET02 "secret02"
#define ID_SECRET03 "secret03"
#define ID_SUN_CRYSTAL_OBTAINED "sun_crystal_obtained"


#endif /* end of include guard RANDOMIZER_ARCHIPELAGO_H */