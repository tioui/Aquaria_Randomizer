/**
* @author      : Louis M (prog@tioui.com)
* @created     : Thu, 25 Jan 2024 17:21:06 +0000
* @license     : MIT
* Class that encapsulate every randomization functionalities
*/

#ifndef RANDOMIZER_H

#define RANDOMIZER_H


#include "../Aquaria/DSQ.h"
#include "../BBGE/ActionMapper.h"
#include <chrono>

typedef struct check {
int flag;
std::string id;
std::string item;
int count;
std::string message;
std::string location;
} check_t;


typedef struct ingredient {
std::string name;
IngredientType category;
} ingredient_t;

typedef struct collectible {
int flag;
std::string name;
std::string imageFile;
} collectible_t;

/**
* Used to link Location of Archipelago to the Check of the Randomizer base class
*/
typedef struct randoMessage {
std::string text;
float x;
float y;
} randomessage_t;

/**
* Class that encapsulate every randomization functionalities
*/
class Randomizer : public ActionMapper
{
public:
    // /**
    //  * Constructor for connecting to a multiworld randomizer server
    //  * @param name The name of the user
    //  * @param server The ip and port of the server
    //  */
    // Randomizer(std::string name, std::string server);
    /**
     * Constructor for the Randomizer
     */
    Randomizer();

    /**
     * Destructor of the object
     */
    virtual ~Randomizer();

    /**
     * Randomize the IngredientData using ingredient in continuity.
     * @param data The IngredientData to randomize
     * @return The randomized IngredientData.
     */
    IngredientData *getRandomizedIngredientData(IngredientData* data);

    /**
     * Activate a randomizer check
     * @param check The check to activate
    */
    virtual void activateCheck(std::string check) = 0;

    /**
     * True if an error occured at initialization. False means every thing is fine
     *
     * @return True if an error occured at initialization. False if not.
     */
     bool hasError() const;

    /**
     * If has_error is True, give the error message.
     *
     * @return The error message
     */
     std::string getErrorMessage();

     /**
      * Spawn a number of ingredient at a position in space, at a certain time.
      * @param ingredient The ingredient to spawn
      * @param position At what position to spawn the ingredient
      * @param times The number of ingredient to spawn
      * @param out Is the entity should spawn now.
      * @param aRandomized Is aIngredient should be randomized before spawn (default to true)
      * @return The (last) spawned ingredient;
      */
     Entity *spawnIngredient(const std::string &ingredient,
                             const Vector &position, int times, int out, bool aRandomized = true);

    /**
     * Spawn a ingredient from an entity.
     * @param entity The entity that spawn the ingredient
     * @param ingredientData The ingredient to spawn
     * @param randomized It ingredientData should be randomized before spawning (default true)
     */
    void spawnIngredientFromEntity(Entity *entity, IngredientData *ingredientData, bool randomized = true);

    /**
     * The unique ID for the Randomizer
     * @return The ID of the Randomizer
     */
    std::string getUid();

    /**
     * The unique String for the Randomizer
     * @return The String of the Randomizer
     */
    virtual std::string getUniqueString();

    /**
     * Lunched at each game loop iteration
     */
    virtual void update();

    /**
     * Get the file name (without path and extension) of the graphic file to show Aquarian text
     * @return The filename
     */
    std::string getAquarianGfx() const;

    /**
     * Is the Aquarian text in the game should be translated
     * @return True if the text should be translated
     */
    bool getIsAquarianTranslated() const;

    /**
     * Launched when the game is ending
     */
    virtual void endingGame() {};

    /**
     * A new or saves game has been load
     * @param newGame True if a new game is launched.
     */
    virtual void onLoad(bool newGame);

    /**
     * When a game is closing a game (return to menu).
     */
    virtual void onClose();

    /**
     * Show a quick message on the screen.
     * @param text The text to show
     */
    virtual void showQuickMessage(const std::string &aText);

    /**
     * Is the final boss is accessible.
     * @return True if the final boss is accessible. False if not.
     */
    virtual bool accessFinalBoss();

    /**
     * Show what is missing to access the final boss.
     */
    virtual void showHintFinalBoss();

    /**
     * Add information about receiving important item in `data`.
     *
     * @param data Where the information about item should be put.
     */
    void appendItemHelpData(std::string &data);

    /**
     * Add information about mini bosses beaten in `data`.
     *
     * @param data Where the information about item should be put.
     */
    void appendMiniBossHelpData(std::string &data);

    /**
     * Add information about big bosses beaten in `data`.
     *
     * @param data Where the information about item should be put.
     */
    void appendBigBossHelpData(std::string &data);

    /**
     * Add information about secrets obtained in `data`.
     *
     * @param data Where the information about item should be put.
     */
    void appendSecretHelpData(std::string &data);

    /**
     * Add information about locations in `data`.
     *
     * @param data Where the information about item should be put.
     */
    virtual void appendLocationsHelpData(std::string &data);

    /**
     * Show the transportation menu and return the selected destination flag.
     *
     * @return the selected destination flag
     */
    int askTransportation();

    /**
     * When the user pressed escape.
     */
    void onPressEscape();

    /**
     * True when the game should skip the final boss 3rd form (hide and seek)
     */
    bool mustSkipFinalBoss3rdForm() const;

    /**
     * Launched when a scene is loading
     *
     * @param scene The scene name that is loading
     */
    virtual void onLoadScene(std::string scene);

    /**
     * Retreive the maximum number of the same ingredients that can be stacked on the ingredient inventory
     * @return The maximum number
     */
    int getMaximumIngredientAmount() const;

protected:

    /**
     * A game is presently running. (not in title)
     */
    bool inGame;

    /**
     * The maximum number of the same ingredients that can be stacked on the ingredient inventory
     */
    int maximumIngredientAmount;

    /**
     * Replacement of every ingredients.
     */
    std::vector<int> *ingredientReplacement;

    /**
     * List of every collectible flags.
     */
    std::vector<collectible_t> *collectibles;

    /**
     * Put hasError to True and assign a message to getErrorMessage.
     * @param message The message to assign to getErrorMessage
     */
    void setError(std::string message);

    /**
     * Remove pending error
     */
    void clearError();

    /**
     * Retreive the index of a check
     * @param checkId The Id of the check to retreive
     * @return The index of the check in the CHECKS vector
     */
    int getCheckIndex(const std::string& checkId);

    /**
     * Retreive the check at a certain index
     * @param index The index of the check to retreive
     * @return The check
     */
    check_t * getCheckByIndex(int index);

    /**
     * Retreive a check structure from a check Id
     * @param checkId The Id of the check to retreive
     * @return A pointer to the check_t object
     */
    check_t *getCheck(const std::string& checkId);

    /**
     * Retreive a check structure from an item Id
     * @param item The item Id of the check to retreive
     * @return A pointer to the check_t object
     */
    check_t *getCheckByItem(const std::string& item);

    /**
     * Get a new item to activate in the local game
     * @param item The item to activate
     * @param count The number of element to receive
     */
    void receivingItem(const std::string& item, int count);

    /**
     * Element that can be droped by entities.
     */
    std::vector<ingredient_t> * ingredients;

    /**
     * Assign the unique ID for the Randomizer
     * @param uid The ID of the Randomizer
     */
    void setUid(std::string uid);

    /**
     * Is the Aquarian text in the game should be translated
     * @param value The value to assign to `isAquarianTranslated`
     */
    void setIsAquarianTranslated(bool value);

    /**
     * Is the Goal's requirement be hidden from the player?
     * @param value The value to assign to `blindGoal`
     */
    void setBlindGoal(bool value);

    /**
     * Is the Goal's requirement be hidden from the player?
     * @return The value to assign to `blindGoal`
     */
    bool getBlindGoal() const;

    /**
     * Ste the `removeTongue` attribute
     * @param value The value to assign to `removeTongue`
     */
    void setRemoveTongue(bool value);

    /**
     * True if the body tongue should be removed
     * @return The value to assign to `removeTongue`
     */
    bool getRemoveTongue() const;

    /**
     * Every checks of the Randomizer
     */
    std::vector<check_t> *checks;

    /**
     * Show a text in game at a certain position (with (x,y) between (0,0) and (800,600))
     * @param aText The text to show in game
     * @param aX The horizontal coordinate of the top corner of the text to show
     * @param aX The vertical coordinate of the top corner of the text to show
     */
    void showText(const std::string &aText, float aX = 0.0, float aY = 500.0);

    /**
     * All secrets needed for goal achievement
     */
    bool secretsNeeded;

    /**
     * Unconfine the home water area by opening the energy door to the open water area
     */
    bool unconfine_home_water_energy_door;

    /**
     * Unconfine the home water area by removing the rock to the transportation turtle
     */
    bool unconfine_home_water_transturtle;

    /**
     * Number of big bosses to kill
     */
    int bigBossesToKill;

    /**
     * Number of mini bosses to kill
     */
    int miniBossesToKill;

    /**
     * Skip first vision in the verse cave
     */
    bool skipFirstVision;

    /**
     * Skip the third form of the final boss
     */
    bool skipFinalBoss3rdForm;

    /**
     * As soon as the hot soup is learn, it will always be accessible never 0 count
     */
    bool infiniteHotSoup;

    /**
     * Tne number of mini bosses that as been slain.
     *
     * @return the number of mini bosses that as been beaten by the player
     */
    int miniBossCount();

    /**
     * Tne number of big bosses that as been slain.
     *
     * @return the number of big bosses that as been beaten by the player
     */
    int bigBossCount();

    /**
     * Tne number of secrets that has been found.
     *
     * @return the number of secrets founded by the player
     */
    int secretsFound();

    /**
     * The number of messages that need to be shown to screen.
     *
     * @return The size of the nextMessages queue.
     */
    unsigned long nextMessagesSize();

    /**
     * Get the recipe with a certain name.
     *
     * @param aName The name of the recipe to find
     * @return The recipe found.
     */
    Recipe * getRecipe(const std::string &aName);


    /**
     * Get a new ingredient to receive in the local game
     * @param ingredientName The name of the ingredient to receive
     * @param count The number of ingredient to receive
     */
    virtual void receivingIngredient(const std::string& ingredientName, int count);

    /**
    * Received an health upgrade
    */
    virtual void receivingUpgradeHealth();

    /**
     * Write the `text` to `messageStream` and put a check if `flag` is true
     *
     * @param messageStream The stream to write the text
     * @param text the text to write
     * @param flag write a check if true
     */
    void writeHelpData(std::stringstream *messageStream, const std::string& text, int flag);

private:

    /**
     * Unique ID for the randomizer
     */
    std::string uid;

    /**
     * Initialize every Checks
     */
    void initialiseChecks() const;

    /**
     * Initialize ingredients
     */
    void initialiseIngredients() const;

    /**
     * Initialize `collectibles`
     */
    void initialiseCollectibles() const;


    /**
     * True if an error occured at initialization. False means every thing is fine
     */
    bool error;

    /**
     * If has_error is True, give the error message.
     */
    std::string errorMessage;


    /**
     * Get a new collectible item to activate in the local game
     * @param check The collectible check item to activate
     */
    void receivingCollectible(check_t *check) const;


    /**
     * Get a new song item to activate in the local game
     * @param check The song check item to activate
     */
    void receivingSong(check_t *check);


    /**
     * Get a new transport to location
     * @param aCheck The transport item to activate
     */
    void receivingTransport(check_t *aCheck);

    /**
     * Spawn a number of recipe dish at a position in space, at a certain time.
     * @param recipe The recipe to spawn
     * @param position At what position to spawn the ingredients
     * @param times The number of ingredients to spawn
     * @param out Is the entity should spawn now.
     * @return The (last) spawned ingredient;
     */
    Entity *spawnRecipe(Recipe *recipe, const Vector &position, int times, int out);

    /**
     * Spawn a recipe dish from an entity.
     * @param entity The entity that spawn the recipe dish
     * @param recipe The recipe to spawn
     * @param ingredientData The ingredient that represent the recipe
     */
    void spawnRecipeFromEntity(Entity *entity, Recipe *recipe, IngredientData *ingredientData);

    /**
     * Retreive a random ingredient of a certain type (or of any type)
     * @param aType The Type of the ingredient (or any type if nothing)
     * @return the ingredient
     */
    ingredient_t *getRandomIngredient(IngredientType aType);

    /**
     * The time start of the presently shown message
     */
    std::time_t currentMessageTime;

    /**
     * A message recently showed in game.
     */
    std::queue<randomessage_t> *nextMessages;

    /**
     * Should Aquarian characters be translated to English.
     */
    bool isAquarianTranslated;

    /**
     * True if the user should not see the goal's requirement before the end of the game.
     */
    bool blindGoal;

    /**
     * True if the body tongue should be removed
     */
    bool removeTongue;

    /**
     * A health upgrade received must be apply again since the last time, naija was dead.
     */
    bool mustUpgradeHealth;

    /**
     * Show an image for a received item.
     *
     * @param imageFile The file name of the image to show.
     */
    void pickupItemEffects(std::string imageFile);

    /**
     * Show a hint if the count is lower than the objective.
     *
     * @param aCount The number to valid
     * @param aObjective The objective to obtained
     * @param aMessage The hint message.
     */
    void showHint(int aCount, int aObjective, const std::string& aMessage);

    /**
     * Launched when the game help screen has to be (un)spawn
     */
    void toggleHelpScreen();

    BitmapText *seedNumberText;

    /**
     * Setup a menu item and a label for an option of the transportation menu
     *
     * @param item The menu item
     * @param itemLabel The menu item label
     * @param icon The icon to show on the `aItem`
     * @param x The horizontal position of the menu item
     * @param y The vertical position of the menu item
     * @param text The text to put on the `aItemLabel`
     */
    void setupTransportationItem(AquariaMenuItem *item, BitmapText *itemLabel, const std::string& icon,
                                 float x, float y, const std::string& text);

    /**
     * Event for the Transportation menu to cancel the process.
     */
   	void onCancelTransportation();

    /**
     * Event for the Transportation menu to manage the Naija's home destination.
     */
   	void onNaijaHomeTransportation();

    /**
     * Event for the Transportation menu to manage the Naija's rock destination
     */
   	void onNaijaRockTransportation();

    /**
     * Event for the Transportation menu to manage the Veil left area destination
     */
   	void onVeil1Transportation();

    /**
     * Event for the Transportation menu to manage the Veil right area destination
     */
   	void onVeil2Transportation();

    /**
     * Event for the Transportation menu to manage the Arnassi Ruins destination
     */
   	void onArnassiTransportation();

    /**
     * Event for the Transportation menu to manage the Kelp Forest destination
     */
   	void onForestTransportation();

    /**
     * Event for the Transportation menu to manage the Simon says destination
     */
   	void onSimonTransportation();

    /**
     * Event for the Transportation menu to manage the Abyss destination
     */
   	void onAbyssTransportation();

    /**
     * Event for the Transportation menu to manage the Body destination
     */
   	void onBodyTransportation();

    /**
     * Event for the Transportation menu to manage the Open Waters destination
     */
   	void onOpenWaterTransportation();

    /**
     * Event for the Transportation menu to manage the Home Waters destination
     */
   	void onHomeWaterTransportation();

    /**
     * Temporarrly disable the transportation menu (re-enable with `enableTransportationMenu`)
     */
   	void disableTransportationMenu();

    /**
     * Re-enable the transportation menu after a `disableTransportationMenu`
     */
   	void enableTransportationMenu();

    /**
     * True if an item of the Transportation menu has been selected.
     */
    bool transportationDone;

    /**
     * The transportation flag selected, or 0 if no selected
     */
    int transportationSelected;

    /**
     * The cancel button for the transportation menu
     */
    AquariaMenuItem *menuCancel;

    /**
     * The home waters button for the transportation menu
     */
    AquariaMenuItem *homeWater;

    /**
     * The Open waters button for the transportation menu
     */
    AquariaMenuItem *openWater;

    /**
     * TheForest button for the transportation menu
     */
    AquariaMenuItem *forest;

    /**
     * The Veil left button for the transportation menu
     */
    AquariaMenuItem *veil1;

    /**
     * The Veil right button for the transportation menu
     */
    AquariaMenuItem *veil2;

    /**
     * The Arnassi Ruins button for the transportation menu
     */
    AquariaMenuItem *arnassi;

    /**
     * The Abyss button for the transportation menu
     */
    AquariaMenuItem *abyss;

    /**
     * The Body (final boss) button for the transportation menu
     */
    AquariaMenuItem *body;

    /**
     * The Simon says button for the transportation menu
     */
    AquariaMenuItem *simon;

    /**
     * The Naija's home/rock button for the transportation menu
     */
    AquariaMenuItem *returnBase;

};

const int locationsOrder[218] = {107, 108, 175, 200, 21, 22, 23, 58, 59, 60, 61, 62, 63, 64, 65, 194, 213, 119, 120,
                                  206, 71, 72, 73, 74, 75, 160, 178, 162, 205, 27, 170, 28, 163, 29, 169, 195, 1, 2, 3,
                                  4, 5, 6, 7, 8, 148, 149, 150, 9, 211, 11, 10, 12, 13, 177, 14, 15, 16, 179, 191, 164,
								                          217, 187, 156, 216, 30, 35, 31, 33, 34, 41, 37, 38, 39, 123, 124, 125, 126, 127, 32,
								                          40, 36, 174, 128, 173, 129, 42, 165, 130, 131, 132, 133, 134, 135, 208, 183, 136,
								                          137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147, 189, 198, 113, 114, 115, 116,
								                          117, 118, 202, 44, 45, 46, 185, 47, 158, 48, 49, 51, 52, 53, 167, 50, 54, 186, 212,
								                          168, 204, 55, 207, 56, 57, 176, 121, 197, 199, 78, 76, 209, 77, 184, 0, 193, 79, 180,
								                          80, 210, 82, 81, 157, 181, 196, 122, 94, 95, 96, 171, 91, 92, 93, 182, 17, 18, 19,
								                          20, 203, 24, 25, 166, 172, 26, 109, 110, 111, 112, 214, 83, 84, 85, 86, 87, 89, 90,
								                          161, 88, 188, 159, 154, 155, 151, 152, 153, 192, 43, 201, 97, 66, 69, 67, 68, 70,
								                          100, 98, 99, 101, 102, 190, 103, 104, 105, 215, 106};


const int GUILEVEL_TRANSPORT = 201;


const int FLAG_COLLECTIBLE_SONGCAVE        = 500;
const int FLAG_COLLECTIBLE_ENERGYTEMPLE    = 501;
const int FLAG_COLLECTIBLE_ENERGYSTATUE    = 502;
const int FLAG_COLLECTIBLE_ENERGYBOSS      = 503;
const int FLAG_COLLECTIBLE_NAIJACAVE       = 504;
const int FLAG_COLLECTIBLE_CRABCOSTUME     = 505;
const int FLAG_COLLECTIBLE_JELLYPLANT      = 506;
const int FLAG_COLLECTIBLE_MITHALASPOT     = 507;
const int FLAG_COLLECTIBLE_SEAHORSECOSTUME = 508;
const int FLAG_COLLECTIBLE_CHEST           = 509;
const int FLAG_COLLECTIBLE_BANNER          = 510;
const int FLAG_COLLECTIBLE_MITHALADOLL     = 511;
const int FLAG_COLLECTIBLE_WALKERBABY      = 512;
const int FLAG_COLLECTIBLE_SEEDBAG         = 513;
const int FLAG_COLLECTIBLE_ARNASSISTATUE   = 514;
const int FLAG_COLLECTIBLE_GEAR            = 515;
const int FLAG_COLLECTIBLE_SUNKEY          = 516;
const int FLAG_COLLECTIBLE_URCHINCOSTUME   = 517;
const int FLAG_COLLECTIBLE_TEENCOSTUME     = 518;
const int FLAG_COLLECTIBLE_MUTANTCOSTUME   = 519;
const int FLAG_COLLECTIBLE_JELLYCOSTUME    = 520;
const int FLAG_COLLECTIBLE_MITHALANCOSTUME = 521;
const int FLAG_COLLECTIBLE_ANEMONESEED     = 522;
const int FLAG_COLLECTIBLE_BIOSEED         = 523;
const int FLAG_COLLECTIBLE_TURTLEEGG       = 524;
const int FLAG_COLLECTIBLE_SKULL           = 525;
const int FLAG_COLLECTIBLE_TRIDENTHEAD     = 526;
const int FLAG_COLLECTIBLE_SPORESEED       = 527;
const int FLAG_COLLECTIBLE_UPSIDEDOWNSEED  = 528;
const int FLAG_COLLECTIBLE_STONEHEAD       = 529;
const int FLAG_COLLECTIBLE_STARFISH        = 530;
const int FLAG_COLLECTIBLE_BLACKPEARL      = 531;
const int FLAG_COLLECTIBLE_CRIB            = 532;
const int FLAG_COLLECTIBLE_BLASTER         = 533;
const int FLAG_COLLECTIBLE_NAUTILUS        = 534;
const int FLAG_COLLECTIBLE_DUMBO           = 535;
const int FLAG_COLLECTIBLE_PIRANHA         = 536;

// Bosses flags
const int FLAG_MINIBOSS_START              = 700;
const int FLAG_MINIBOSS_NAUTILUSPRIME      = 700;
const int FLAG_MINIBOSS_KINGJELLY          = 701;
const int FLAG_MINIBOSS_MERGOG             = 702;
const int FLAG_MINIBOSS_CRAB               = 703;
const int FLAG_MINIBOSS_OCTOMUN            = 704;
const int FLAG_MINIBOSS_MANTISSHRIMP       = 705;
const int FLAG_MINIBOSS_PRIESTS            = 706;
const int FLAG_MINIBOSS_BLASTER            = 707;
const int FLAG_MINIBOSS_END                = 707;
const int FLAG_ENERGYBOSSDEAD              = 109;
const int FLAG_SUNKENCITY_BOSS             = 114;
const int FLAG_BOSS_FOREST                 = 117;
const int FLAG_BOSS_MITHALA                = 116;
const int FLAG_BOSS_SUNWORM                = 128;

const int FLAG_TRANSTURTLE_VEIL01          = 130;
const int FLAG_TRANSTURTLE_FOREST04        = 132;
const int FLAG_TRANSTURTLE_OPENWATER03     = 133;
const int FLAG_TRANSTURTLE_FOREST05        = 134;
const int FLAG_TRANSTURTLE_MAINAREA        = 135;
const int FLAG_TRANSTURTLE_SEAHORSE        = 136;
const int FLAG_TRANSTURTLE_VEIL02          = 137;
const int FLAG_TRANSTURTLE_ABYSS03         = 138;
const int FLAG_TRANSTURTLE_FINALBOSS       = 139;
const int FLAG_TRANSTURTLE_NAIJAHOME       = 150;
const int FLAG_TRANSTURTLE_NAIJAROCK       = 151;

// Unconfine Home water
const int FLAG_MAINAREA_TRANSTURTLE_ROCK   = 245;
const int FLAG_ENERGYSLOT_MAINAREA         = 104;

// Other flags
const int FLAG_ENERGYSLOT_FIRST            = 106;
const int FLAG_VISION_ENERGYTEMPLE         = 300;
const int FLAG_ENTER_HOMECAVE              = 654;
const int FLAG_REMOVE_TONGUE               = 920;

// Randomizer FLAGS
const int FLAG_LOCATION_START              = 1100;
const int FLAG_LOCATION_END                = 1318;
const int FLAG_BLIND_GOAL                  = 1499;

const int FLAG_CHILDREN_RESERVED_START     = 1500;
const int FLAG_CHILDREN_RESERVED_END       = 1999;


#endif /* end of include guard RANDOMIZER_H */
