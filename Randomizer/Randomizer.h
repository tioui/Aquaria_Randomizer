/**
* @author      : Louis Marchand (prog@tioui.com)
* @created     : Thu, 25 Jan 2024 17:21:06 +0000
* @license     : MIT
* Class that encapsulate every randomization functionalities
*/

#ifndef RANDOMIZER_H

#define RANDOMIZER_H


#include "../Aquaria/DSQ.h"
#include <chrono>

typedef struct check {
int flag;
std::string id;
std::string item;
int count;
std::string message;
} check_t;


typedef struct ingredient {
std::string name;
IngredientType category;
} ingredient_t;

typedef struct collectible {
int flag;
std::string name;
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
class Randomizer
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
     * Lunched at each game loop iteration
     */
    virtual void update();

    /**
     * Get the file name (without path and extension) of the graphic file to show Aquarian text
     * @return The filename
     */
    std::string getAquarianGfx();

    /**
     * Is the Aquarian text in the game should be translated
     * @return True if the text should be translated
     */
    bool getIsAquarianTranslated();

    /**
     * Launched when the game is ending
     */
    virtual void endingGame() {};

    /**
     * Set the avatar (Naija) object
     * @param avatar Naija
     */
    void setAvatar(Avatar *avatar);

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
    bool accessFinalBoss();

    /**
     * Show what is missing to access the final boss.
     */
    void showHintFinalBoss();

protected:

    /**
     * A game is presently running. (not in title)
     */
    bool inGame;

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
     * Flags used to know what check has already been found
     */
    std::vector<int> *checkFlags;

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
     * Naija
     */
    Avatar *avatar;

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
     * All secret needed for goal achievement
     */
    bool secretNeeded;

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

    private:

    /**
     * Unique ID for the randomizer
     */
    std::string uid;

    /**
     * Initialize every Checks
     */
    void initialiseChecks();

    /**
     * Initialize ingredients
     */
    void initialiseIngredients();

    /**
     * Initialize `collectibles`
     */
    void initialiseCollectibles();


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
    void receivingCollectible(check_t *check);


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
     * Show a hint if the count is lower than the objective.
     *
     * @param aCount The number to valid
     * @param aObjective The objective to obtained
     * @param aMessage The hint message.
     */
    void showHint(int aCount, int aObjective, const std::string& aMessage);

};

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

// Bosses flags to open the way to the body
const int FLAG_MINIBOSS_START              = 700;
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

// Other flags
const int FLAG_VISION_ENERGYTEMPLE         = 300;
const int FLAG_ENTER_HOMECAVE              = 654;


#endif /* end of include guard RANDOMIZER_H */
