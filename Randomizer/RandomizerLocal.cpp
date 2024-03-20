/**
 * @author      : Louis Marchand (prog@tioui.com)
 * @created     : mercredi feb 15, 2024 21:30:04 EST
 * @license     : MIT
 * Class that encapsulate local randomization functionalities
 *
 * Todo:
jellyshock : attempt to call a nil value [???:0] songNoteDone
        nudi : attempt to call a nil value [???:0] songNoteDone
        pet_nautilus : attempt to call a nil value [???:0] songNoteDone
        luaScriptError: Path [naija_bindshell]: songNoteDone : attempt to call a nil value [???:0]

        anemone : attempt to call a nil value [???:0] songNoteDone
anemone3 : attempt to call a nil value [???:0] songNoteDone
anemone4 : attempt to call a nil value [???:0] songNoteDone
anemone : attempt to call a nil value [???:0] songNoteDone
anemone : attempt to call a nil value [???:0] songNote
anemone2 : attempt to call a nil value [???:0] songNote
anemone3 : attempt to call a nil value [???:0] songNote
anemone : attempt to call a nil value [???:0] songNote
anemone2 : attempt to call a nil value [???:0] songNote
luaScriptError: Path [big-anemone]: songNote : attempt to call a nil value [???:0]
anemone : attempt to call a nil value [???:0] songNoteDone
anemone2 : attempt to call a nil value [???:0] songNoteDone
anemone3 : attempt to call a nil value [???:0] songNoteDone
anemone : attempt to call a nil value [???:0] songNoteDone
anemone2 : attempt to call a nil value [???:0] songNoteDone
luaScriptError: Path [big-anemone]: songNoteDone : attempt to call a nil value [???:0]

luaScriptError: jellysmall : postInit : attempt to call a nil value [???:0]
 aggrohopper: canShotHit function failed
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
        lUid = lJsonData["uid"];
        setUid(std::to_string(lUid));
        lAquarianTranslated = lJsonData["aquarianTranslate"];
        setIsAquarianTranslated(lAquarianTranslated);
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
 * Todo: Put the location index in the continuity flags instead of the item index (after the first walkthrough
 */
void RandomizerLocal::activateCheck(std::string aCheck) {
    int lCheckIndex =getCheckIndex(aCheck);
    int lItemIndex = checksReplacement->at(lCheckIndex);

    check_t *lCheck = getCheckByIndex(lItemIndex);
    if (dsq->continuity.getFlag(lCheck->flag)) {
        dsq->screenMessage("Check already obtained.");
    } else {
        dsq->continuity.setFlag(lCheck->flag, 1);

        receivingItem(lCheck->item, lCheck->count);
    }

}

/**
 * Lunched at each game loop iteration
 */
void RandomizerLocal::update(){
}

