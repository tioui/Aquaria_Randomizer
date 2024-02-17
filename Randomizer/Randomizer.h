/**
 * @author      : Louis Marchand (prog@tioui.com)
 * @created     : Thu, 25 Jan 2024 17:21:06 +0000
 * @license     : MIT
 * Class that encapsulate every randomization functionalities
 */

#ifndef RANDOMIZER_H

#define RANDOMIZER_H


#include "../Aquaria/DSQ.h"

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
    ~Randomizer();

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
      * @return The (last) spawned ingredient;
      */
     Entity *spawnIngredient(const std::string &ingredient, const Vector &position, int times, int out);

    /**
     * Spawn a ingredient from an entity.
     * @param entity The entity that spawn the ingredient
     * @param ingredientData The ingredient to spawn
     */
    void spawnIngredientFromEntity(Entity *aEntity, IngredientData *ingredientData);

protected:

    /**
     * Replacement of every ingredients.
     */
    std::vector<int> *ingredientReplacement;

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

private:

    /**
     * Initialize every Checks
     */
    void initialiseChecks();

    /**
     * Initialize ingredients
     */
    void initialiseIngredients();

    /**
     * Every checks of the Randomizer
     */
    std::vector<check_t> *checks;

    /**
     * Initialize every checks of the randomizer
     */
    void initializeChecks();

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
     * @param aCollectible The collectible item to activate
     */
    void receivingCollectible(const std::string& aCollectible);

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

//		/**
//		 * The name of the multiworld randomizer user
//		 */
//		std::string name;
//
//		/**
//		 * The name of the multiworld randomizer server and port
//		 */
//		std::string server;
};

const int FLAG_COLLECTIBLE_INHOME_SONGCAVE = 2550;
const int FLAG_COLLECTIBLE_INHOME_ENERGYTEMPLE = 2551;
const int FLAG_COLLECTIBLE_INHOME_ENERGYSTATUE = 2552;
const int FLAG_COLLECTIBLE_INHOME_ENERGYBOSS = 2553;
const int FLAG_COLLECTIBLE_INHOME_NAIJACAVE = 2554;
const int FLAG_COLLECTIBLE_INHOME_CRABCOSTUME = 2555;
const int FLAG_COLLECTIBLE_INHOME_JELLYPLANT = 2556;
const int FLAG_COLLECTIBLE_INHOME_MITHALASPOT = 2557;
const int FLAG_COLLECTIBLE_INHOME_SEAHORSECOSTUME = 2558;
const int FLAG_COLLECTIBLE_INHOME_CHEST = 2559;
const int FLAG_COLLECTIBLE_INHOME_BANNER = 2560;
const int FLAG_COLLECTIBLE_INHOME_MITHALADOLL = 2561;
const int FLAG_COLLECTIBLE_INHOME_WALKERBABY = 2562;
const int FLAG_COLLECTIBLE_INHOME_SEEDBAG = 2563;
const int FLAG_COLLECTIBLE_INHOME_ARNASSISTATUE = 2564;
const int FLAG_COLLECTIBLE_INHOME_GEAR = 2565;
const int FLAG_COLLECTIBLE_INHOME_SUNKEY = 2566;
const int FLAG_COLLECTIBLE_INHOME_URCHINCOSTUME = 2567;
const int FLAG_COLLECTIBLE_INHOME_TEENCOSTUME = 2568;
const int FLAG_COLLECTIBLE_INHOME_MUTANTCOSTUME = 2569;
const int FLAG_COLLECTIBLE_INHOME_JELLYCOSTUME = 2570;
const int FLAG_COLLECTIBLE_INHOME_MITHALANCOSTUME = 2571;
const int FLAG_COLLECTIBLE_INHOME_ANEMONESEED = 2572;
const int FLAG_COLLECTIBLE_INHOME_BIOSEED = 2573;
const int FLAG_COLLECTIBLE_INHOME_TURTLEEGG = 2574;
const int FLAG_COLLECTIBLE_INHOME_SKULL = 2575;
const int FLAG_COLLECTIBLE_INHOME_TRIDENTHEAD = 2576;
const int FLAG_COLLECTIBLE_INHOME_SPORESEED = 2577;
const int FLAG_COLLECTIBLE_INHOME_UPSIDEDOWNSEED = 2578;
const int FLAG_COLLECTIBLE_INHOME_STONEHEAD = 2579;
const int FLAG_COLLECTIBLE_INHOME_STARFISH = 2580;
const int FLAG_COLLECTIBLE_INHOME_BLACKPEARL = 2581;
const int FLAG_COLLECTIBLE_INHOME_BLASTER = 2582;
const int FLAG_COLLECTIBLE_INHOME_NAUTILUS = 2583;
const int FLAG_COLLECTIBLE_INHOME_DUMBO = 2584;
const int FLAG_COLLECTIBLE_INHOME_PIRANHA = 2585;


#endif /* end of include guard RANDOMIZER_H */
