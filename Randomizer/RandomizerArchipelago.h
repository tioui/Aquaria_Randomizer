/**
 * @author      : Louis M (prog@tioui.com)
 * @created     : Fri, 08 Mar 2024 19:51:46 +0000
 * @license     : MIT
 * Class that encapsulate Archipelago server randomization
 */



#ifndef RANDOMIZER_ARCHIPELAGO_H

#define RANDOMIZER_ARCHIPELAGO_H

#include "Randomizer.h"
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
    ITEM_TYPE_TRANSTURTLE
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
     * @param deathLink True if Archipelago Death link packets should be used.
     */
    explicit RandomizerArchipelago(const std::string& server, const std::string& name, const std::string& password,
                                   bool selfMessage, bool deathLink);

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
    void showHintFinalBoss() override;

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

private:

    /**
     * Constructor that does not connect to a server
     */
    RandomizerArchipelago();

    /**
     * Unique identifier of the `apClient`
     */
    char uuid[33];

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
     */
    void connectionUpdate();

    /**
     * The mutex used to synchrnize the apClient.
     */
    std::mutex apMutex;

    /**
     * Show only message from AP Server that are related to the current player
     */
    bool selfMessageOnly;

    /**
     * True if the server has been disconnected and is trying to reconnect.
     */
    bool hasBeenDisconnected;

    /**
     * Check if the Text node is related to the current player.
     * @param aData
     * @return
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
     * True if the player is playing offline
     */
    bool isOffline;

};

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


#endif /* end of include guard RANDOMIZER_ARCHIPELAGO_H */