/**
 * @author      : Louis Marchand (prog@tioui.com)
 * @created     : mercredi jan 10, 2024 16:08:04 EST
 * @license     : MIT
 * Class that encapsulate every randomization functionalities
 */

#include "Randomizer.h"
#include <assert.h>
#include <vector>
#include "apclient.hpp"

/**
 * Constructor of the object
 * \param aName The user name
 * \param aServer The server ip and port
 */
Randomizer::Randomizer(std::string aName, std::string aServer)
{
	dsq = NULL;
	ingredientReplacement = {};
	for (int i = 0; i < 26; i = i + 1) {
		ingredientReplacement.push_back(i);
	}
	name = aName;
	server = aServer;
}


/**
 * Constructor for using a local json file
 * \param filename The json filename
 */
Randomizer::Randomizer(std::string filename) {
	
}

/**
 * Activate a randomizer check in the multiworld
 * \param aCheck The check to activate
 * \todo The method
 */
void Randomizer::activateCheck(const std::string aCheck)
{
	check_t * lCheck = getCheck(aCheck);
	receivingItem(lCheck->item, lCheck->count);
}

/**
 * Get a new collectible item to activate in the local game
 * \param aCollectible The collectible item to activate
 */
void Randomizer::receivingCollectible(const std::string aCollectible) {
	if (aCollectible.compare("anemone")){
		dsq->continuity.setFlag(FLAG_COLLECTIBLE_INHOME_ANEMONESEED, 1);
	} else if (aCollectible.compare("arnassi_statue")) {
		dsq->continuity.setFlag(FLAG_COLLECTIBLE_INHOME_ARNASSISTATUE, 1);
	} else if (aCollectible.compare("mithalas_banner")) {
		dsq->continuity.setFlag(FLAG_COLLECTIBLE_INHOME_BANNER, 1);
	} else if (aCollectible.compare("bio_seed")) {
		dsq->continuity.setFlag(FLAG_COLLECTIBLE_INHOME_BIOSEED, 1);
	} else if (aCollectible.compare("blackpearl")) {
		dsq->continuity.setFlag(FLAG_COLLECTIBLE_INHOME_BLACKPEARL, 1);
	} else if (aCollectible.compare("treasure_chest")) {
		dsq->continuity.setFlag(FLAG_COLLECTIBLE_INHOME_CHEST, 1);
	} else if (aCollectible.compare("energy_boss")) {
		dsq->continuity.setFlag(FLAG_COLLECTIBLE_INHOME_ENERGYBOSS, 1);
	} else if (aCollectible.compare("energy_statue")) {
		dsq->continuity.setFlag(FLAG_COLLECTIBLE_INHOME_ENERGYSTATUE, 1);
	} else if (aCollectible.compare("golden_gear")) {
		dsq->continuity.setFlag(FLAG_COLLECTIBLE_INHOME_GEAR, 1);
	} else if (aCollectible.compare("jelly_plant")) {
		dsq->continuity.setFlag(FLAG_COLLECTIBLE_INHOME_JELLYPLANT, 1);
	} else if (aCollectible.compare("mithala_doll")) {
		dsq->continuity.setFlag(FLAG_COLLECTIBLE_INHOME_MITHALADOLL, 1);
	} else if (aCollectible.compare("mithala_spot")) {
		dsq->continuity.setFlag(FLAG_COLLECTIBLE_INHOME_MITHALASPOT, 1);
	} else if (aCollectible.compare("big_seed")) {
		dsq->continuity.setFlag(FLAG_COLLECTIBLE_INHOME_NAIJACAVE, 1);
	} else if (aCollectible.compare("seed_bag")) {
		dsq->continuity.setFlag(FLAG_COLLECTIBLE_INHOME_SEEDBAG, 1);
	} else if (aCollectible.compare("skull")) {
		dsq->continuity.setFlag(FLAG_COLLECTIBLE_INHOME_SKULL, 1);
	} else if (aCollectible.compare("jelly_beacon")) {
		dsq->continuity.setFlag(FLAG_COLLECTIBLE_INHOME_SONGCAVE, 1);
	} else if (aCollectible.compare("spore_seed")) {
		dsq->continuity.setFlag(FLAG_COLLECTIBLE_INHOME_SPORESEED, 1);
	} else if (aCollectible.compare("gold_star")) {
		dsq->continuity.setFlag(FLAG_COLLECTIBLE_INHOME_STARFISH, 1);
	} else if (aCollectible.compare("stone_head")) {
		dsq->continuity.setFlag(FLAG_COLLECTIBLE_INHOME_STONEHEAD, 1);
	} else if (aCollectible.compare("sun_key")) {
		dsq->continuity.setFlag(FLAG_COLLECTIBLE_INHOME_SUNKEY, 1);
	} else if (aCollectible.compare("trident_head")) {
		dsq->continuity.setFlag(FLAG_COLLECTIBLE_INHOME_TRIDENTHEAD, 1);
	} else if (aCollectible.compare("turtle_egg")) {
		dsq->continuity.setFlag(FLAG_COLLECTIBLE_INHOME_TURTLEEGG, 1);
	} else if (aCollectible.compare("upsidedown_seed")) {
		dsq->continuity.setFlag(FLAG_COLLECTIBLE_INHOME_UPSIDEDOWNSEED, 1);
	} else if (aCollectible.compare("walker")) {
		dsq->continuity.setFlag(FLAG_COLLECTIBLE_INHOME_WALKERBABY, 1);
	} else if (aCollectible.compare("crab_costume")) {
		dsq->continuity.setFlag(FLAG_COLLECTIBLE_INHOME_CRABCOSTUME, 1);
	} else if (aCollectible.compare("jelly_costume")) {
		dsq->continuity.setFlag(FLAG_COLLECTIBLE_INHOME_JELLYCOSTUME, 1);
	} else if (aCollectible.compare("mithalan_costume")) {
		dsq->continuity.setFlag(FLAG_COLLECTIBLE_INHOME_MITHALANCOSTUME, 1);
	} else if (aCollectible.compare("mutant_costume")) {
		dsq->continuity.setFlag(FLAG_COLLECTIBLE_INHOME_MUTANTCOSTUME, 1);
	} else if (aCollectible.compare("seahorse_costume")) {
		dsq->continuity.setFlag(FLAG_COLLECTIBLE_INHOME_SEAHORSECOSTUME, 1);
	} else if (aCollectible.compare("teen_costume")) {
		dsq->continuity.setFlag(FLAG_COLLECTIBLE_INHOME_TEENCOSTUME, 1);
	} else if (aCollectible.compare("urchin_costume")) {
		dsq->continuity.setFlag(FLAG_COLLECTIBLE_INHOME_URCHINCOSTUME, 1);
	} else if (aCollectible.compare("blaster")) {
		dsq->continuity.setFlag(FLAG_COLLECTIBLE_INHOME_BLASTER, 1);
	} else if (aCollectible.compare("nautilus")) {
		dsq->continuity.setFlag(FLAG_COLLECTIBLE_INHOME_NAUTILUS, 1);
	} else if (aCollectible.compare("dumbo")) {
		dsq->continuity.setFlag(FLAG_COLLECTIBLE_INHOME_DUMBO, 1);
	} else if (aCollectible.compare("piranha")) {
		dsq->continuity.setFlag(FLAG_COLLECTIBLE_INHOME_PIRANHA, 1);
	} else {
		assert(false && "The collectible is not valid!");
	}
}

/**
 * Get a new item to activate in the local game
 * \param aItem The item to activate
 * \param aCount The number of element to receive
 */
void Randomizer::receivingItem(const std::string aItem, int aCount)
{
	std::stringstream lMessageStream;
	if (aItem.compare(0, 10, "ingredient") == 0) {
		check_t * lCheck = getCheckByItem(aItem);
		lMessageStream << lCheck->message;
		if (aCount > 1) {
			lMessageStream << " x " << aCount;
		}
		std::string lIngredientName = aItem.substr(11);
		IngredientData *lIngredient = dsq->continuity.getIngredientDataByName(lIngredientName);
		dsq->continuity.pickupIngredient(lIngredient, aCount);
	} else if (aItem.compare(0, 11, "upgrade_wok") == 0) {
		lMessageStream << "Upgrade: Wok";
		dsq->continuity.setFlag(FLAG_UPGRADE_WOK, 1);
	} else if (aItem.compare(0, 10, "upgrade_health") == 0) {
		lMessageStream << "Upgrade: Health";
		dsq->continuity.upgradeHealth();
	} else if (aItem.compare(0, 11, "collectible") == 0) {
		check_t * lCheck = getCheckByItem(aItem);
		lMessageStream << lCheck->message;
		std::string lCollectible = aItem.substr(12);
		receivingCollectible(lCollectible);
	} else {
		assert(false && "The receving item is not valid!");
	}
	dsq->screenMessage(lMessageStream.str());
}

/**
 * Retreive a check structure from a check Id
 * \param aCheckId The Id of the check to retreive
 * \return A pointer to the check_t object
 */
check_t *Randomizer::getCheck(const std::string aCheckId)
{
	check_t *result = NULL;
	for (int i = 0; i < CHECKS.size() && !result; i = i + 1) {
		if (CHECKS[i].id.compare(aCheckId) == 0) {
			result = &(CHECKS[i]);
		}
	}
	return result;
}

/**
 * Retreive a check structure from an item Id
 * \param aItem The item Id of the check to retreive
 * \return A pointer to the check_t object
 */
check_t *Randomizer::getCheckByItem(const std::string aItem)
{
	check_t *result = NULL;
	for (int i = 0; i < CHECKS.size() && !result; i = i + 1) {
		if (CHECKS[i].item.compare(aItem) == 0) {
			result = &(CHECKS[i]);
		}
	}
	return result;
}

/**
 * Initialise the ingredientReplacement values.
 * \param filename The YAML file containing the remplacement values.
 * \todo The method
 */
void Randomizer::initialiseIngredientReplacements(const std::string &filename)
{

}
/**
 * Randomize the IngredientData using ingredient in continuity.
 * \param aData The IngredientData to randomize
 * \return The randomized IngredientData.
 */
IngredientData *Randomizer::getRandomizedIngredientData(IngredientData* aData)
{
	IngredientData* lRandomizedData = aData;
	if (dsq) {
		int lRandomizedIndex;
		int ingredientIndex = dsq->continuity.indexOfIngredientData(aData);
		assert((ingredientIndex != -1) && "The ingredient is not valid");
		lRandomizedIndex = ingredientReplacement[ingredientIndex];
		lRandomizedData = dsq->continuity.getIngredientDataByIndex(lRandomizedIndex);
		assert(lRandomizedData && "The ingredient is not valid");
	}
	
	return lRandomizedData;
}

