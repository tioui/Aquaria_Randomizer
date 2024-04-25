/**
 * @author      : Louis Marchand (prog@tioui.com)
 * @created     : mercredi feb 15, 2024 21:30:04 EST
 * @license     : MIT
 * Class that encapsulate local randomization functionalities
*/

#include "RandomizerLocal.h"
#include <fstream>
#include "subprojects/json/include/nlohmann/json.hpp"


/**
 * Constructor for using a local json file
 * @param aFilename The json filename
 */
RandomizerLocal::RandomizerLocal(const std::string& aFilename) : Randomizer() {
    checksReplacement = new std::vector<int>();
    long long int lUid = 0;
    std::ifstream lFile(aFilename);
    bool lAquarianTranslated = false;
    try {
        nlohmann::json lJsonData = nlohmann::json::parse(lFile);
        version = lJsonData["version"];
        setUid(lJsonData["uid"]);
        lAquarianTranslated = lJsonData["aquarianTranslate"];
        skipFirstVision = lJsonData["skipFirstVision"];
        setIsAquarianTranslated(lAquarianTranslated);
        secretsNeeded = lJsonData["secretsNeeded"];
        bigBossesToKill = lJsonData["bigBossesToBeat"];
        miniBossesToKill = lJsonData["miniBossesToBeat"];
        skipFirstVision = lJsonData["skipFirstVision"];
        for (int lElement : lJsonData["ingredientReplacement"]) {
            ingredientReplacement->push_back(lElement);
        }
        for (int lElement : lJsonData["checksReplacement"]) {
            checksReplacement->push_back(lElement);
        }
    } catch (nlohmann::json::parse_error& lException){
        setError("Randomizer JSON file " + aFilename + " is not valid.");
    }

}


/**
 * Destructor of the object.
 */
RandomizerLocal::~RandomizerLocal() {
    delete(checksReplacement);
}

/**
 * Activate a randomizer check
 * @param aCheck The check to activate
 */
void RandomizerLocal::activateCheck(std::string aCheck) {
    int lCheckIndex =getCheckIndex(aCheck);
    int lItemIndex = checksReplacement->at(lCheckIndex);

    check_t *lLocationCheck = getCheckByIndex(lCheckIndex);
    check_t *lItemCheck = getCheckByIndex(lItemIndex);
    if (dsq->continuity.getFlag(lLocationCheck->flag)) {
        dsq->screenMessage("Check already obtained.");
    } else {
        dsq->continuity.setFlag(lLocationCheck->flag, 1);

        receivingItem(lItemCheck->item, lItemCheck->count);
    }

}

/**
 * Lunched at each game loop iteration
 */
void RandomizerLocal::update(){
}

