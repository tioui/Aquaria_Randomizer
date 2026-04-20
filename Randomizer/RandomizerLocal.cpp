/**
 * @author      : Louis M (prog@tioui.com)
 * @created     : Wed feb 15, 2024 21:30:04 EST
 * @license     : MIT
 * Class that encapsulate local randomization functionalities
*/

#include "RandomizerLocal.h"
#include <fstream>
#include "subprojects/json/include/nlohmann/json.hpp"

#define JSON_VERSION 2

/**
 * Constructor for using a local json file
 * @param aFilename The json filename
 */
RandomizerLocal::RandomizerLocal(const std::string& aFilename) : Randomizer() {
    itemsReplacement = new std::vector<itemReplacement*>();
    std::ifstream lFile((std::filesystem::path(aFilename)));
    bool lAquarianTranslated = false;
    bool lBlindGoal = false;
    bool lSaveHeal = true;
    killCreatorGoal = true;
    try {
        nlohmann::json lJsonData = nlohmann::json::parse(lFile);
        if (lJsonData.contains("version")) {
            version = lJsonData["version"];
            if (version > JSON_VERSION) {
                setError("The randomizer is too old for the generated json. Update the randomizer to play.");
            }
        } else {
            setError("Randomizer JSON file " + aFilename + " is not valid: 'version' field is required.");
        }
        if (lJsonData.contains("uid")) {
            setUid(lJsonData["uid"]);
        } else {
            setError("Randomizer JSON file " + aFilename + " is not valid: 'uid' field is required.");
        }
        if (lJsonData.contains("aquarianTranslate")) {
            lAquarianTranslated = lJsonData["aquarianTranslate"];
        } else {
            debugLog("Warning: The field 'aquarianTranslate' is not present in the json file.");
            lAquarianTranslated = false;
        }
        setIsAquarianTranslated(lAquarianTranslated);
        if (lJsonData.contains("skipFirstVision")) {
            skipFirstVision = lJsonData["skipFirstVision"];
        } else {
            debugLog("Warning: The field 'skipFirstVision' is not present in the json file.");
            skipFirstVision = false;
        }
        if (lJsonData.contains("blindGoal")) {
            lBlindGoal = lJsonData["blindGoal"];
        } else {
            debugLog("Warning: The field 'blindGoal' is not present in the json file.");
            lBlindGoal = false;
        }
        setBlindGoal(lBlindGoal);
        if (lJsonData.contains("secretsNeeded")) {
            secretsNeeded = lJsonData["secretsNeeded"];
            killFourGodsGoal = false;
        } else {
            secretsNeeded = false;
            if (lJsonData.contains("objective")) {
                int lObjective = lJsonData["objective"];
                if (lObjective == 1) {
                    secretsNeeded = true;
                    killFourGodsGoal = false;
                } else if (lObjective == 2) {
                    killFourGodsGoal = true;
                }
            } else {
                killFourGodsGoal = false;
                debugLog("Warning: The field 'objective' is not present in the json file.");
            }
        }
        if (lJsonData.contains("bigBossesToBeat")) {
            bigBossesToKill = lJsonData["bigBossesToBeat"];
        } else {
            debugLog("Warning: The field 'bigBossesToBeat' is not present in the json file.");
            bigBossesToKill = 0;
        }
        if (lJsonData.contains("miniBossesToBeat")) {
            miniBossesToKill = lJsonData["miniBossesToBeat"];
        } else {
            debugLog("Warning: The field 'miniBossesToBeat' is not present in the json file.");
            miniBossesToKill = 0;
        }
        if (lJsonData.contains("skipFirstVision")) {
            skipFirstVision = lJsonData["skipFirstVision"];
        } else {
            debugLog("Warning: The field 'skipFirstVision' is not present in the json file.");
            skipFirstVision = false;
        }
        if (lJsonData.contains("skipFinalBoss3rdForm")) {
            skipFinalBoss3rdForm = lJsonData["skipFinalBoss3rdForm"];
        } else {
            debugLog("Warning: The field 'skipFinalBoss3rdForm' is not present in the json file.");
            skipFinalBoss3rdForm = false;
        }
        if (lJsonData.contains("infiniteHotSoup")) {
            infiniteHotSoup = lJsonData["infiniteHotSoup"];
        } else {
            debugLog("Warning: The field 'infiniteHotSoup' is not present in the json file.");
            infiniteHotSoup = true;
        }
        if (lJsonData.contains("maximumIngredientAmount")) {
            maximumIngredientAmount = lJsonData["maximumIngredientAmount"];
        } else {
            debugLog("Warning: The field 'maximumIngredientAmount' is not present in the json file.");
            maximumIngredientAmount = 8;
        }
        if (lJsonData.contains("openBodyTongue")) {
            removeTongue = lJsonData.contains("openBodyTongue");
        }
        if (lJsonData.contains("saveHealing")) {
            lSaveHeal = lJsonData["saveHealing"];
        } else {
            debugLog("Warning: The field 'saveHealing' is not present in the json file.");
            lSaveHeal = false;
        }
        setSaveHeal(lSaveHeal);
        if (lJsonData.contains("unconfineHomeWaterEnergyDoor")) {
            unconfine_home_water_energy_door = lJsonData["unconfineHomeWaterEnergyDoor"];
        } else {
            debugLog("Warning: The field 'unconfineHomeWaterEnergyDoor' is not present in the json file.");
            unconfine_home_water_energy_door = false;
        }
        if (lJsonData.contains("unconfineHomeWaterTransturtle")) {
            unconfine_home_water_transturtle = lJsonData["unconfineHomeWaterTransturtle"];
        } else {
            debugLog("Warning: The field 'unconfineHomeWaterTransturtle' is not present in the json file.");
            unconfine_home_water_transturtle = false;
        }
        if (lJsonData.contains("ingredientReplacement")) {
            for (int lElement : lJsonData["ingredientReplacement"]) {
                ingredientReplacement->push_back(lElement);
            }
        } else {
            debugLog("Warning: The field 'ingredientReplacement' is not present in the json file.");
            for (int i = 0; i < 76; i = i + 1) {
                ingredientReplacement->push_back(i);
            }
        }
        if (lJsonData.contains("itemsReplacement")) {
            for (const nlohmann::json& lElement : lJsonData["itemsReplacement"]) {
                int lItem = lElement[0];
                int lCount = lElement[1];
                addItemReplacement(lItem, lCount);
            }
            for (int i = itemsReplacement->size(); i < locations->size(); i = i + 1) {
                addItemReplacement(0, 1);
            }
        } else {
            setError("Randomizer JSON file " + aFilename +
                " is not valid: 'itemsReplacement' field is required.");
        }
    } catch (nlohmann::json::parse_error& lException){
        setError("Randomizer JSON file " + aFilename + " is not valid: " + lException.what());
    } catch (nlohmann::json::type_error & lException){
        setError("Randomizer JSON file " + aFilename + " has invalid value type: " +  + lException.what());
    }

}

/**
 * Add a number of item in the `itemsRemplacement` list
 * @param aItem The item to add
 * @param aCount The number of item to add
 */
void RandomizerLocal::addItemReplacement(int aItem, int aCount) const {
    itemReplacement *lReplacement = new itemReplacement;
    lReplacement->id = aItem;
    lReplacement->count = aCount;
    itemsReplacement->push_back(lReplacement);
}


/**
 * Destructor of the object.
 */
RandomizerLocal::~RandomizerLocal() {
    for (std::vector<itemReplacement *>::iterator lIterator = itemsReplacement->begin(); lIterator != itemsReplacement->end();) {
        delete *lIterator;
    }
    delete(itemsReplacement);
}

/**
 * Activate a randomizer check
 * @param aCheck The check to activate
 */
void RandomizerLocal::activateLocation(std::string aCheck) {
    int lLocationIndex =getLocationIndex(aCheck);
    location_t *lLocation = getLocationByIndex(lLocationIndex);
    if (dsq->continuity.getFlag(lLocation->flag)) {
        dsq->screenMessage("Check already obtained.");
    } else {
        dsq->continuity.setFlag(lLocation->flag, 1);
        itemReplacement *lItemReplacement = itemsReplacement->at(lLocationIndex);
        item_t *lItem = getItemByIndex(lItemReplacement->id);
        receivingItem(lItem->name, lItemReplacement->count);
    }

}


