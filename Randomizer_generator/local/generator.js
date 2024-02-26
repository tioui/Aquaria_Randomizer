/**
 * Class used to generate Aquaria randomizer JSON file
 */
class Randomizer {

    /**
     * Initialization of the current object
     * @param aVersion The version number of the randomizer generator
     */
    constructor(aVersion) {
        this.version = aVersion;
        this.ingredientReplacement = []; // 26 base ingredients and 50 dishs
        for(let i = 0; i < 76; i = i + 1) {
            this.ingredientReplacement.push(i);
        }
        this.checksReplacement = [];
        for(let i = 0; i < 198; i = i + 1) {
            this.checksReplacement.push(i);
        }
    }

    /**
     * Randomize the ingredient part of the ingredientReplacement array.
     */
    randomizeIngredientReplacement(aCommons){
        let lSkip = 50;
        if (aCommons){
            lSkip = lSkip + 3;
        }
        this.randomizeArray(this.ingredientReplacement, 0, lSkip);
    }

    /**
     * Randomize the dish part of the ingredientReplacement array.
     */
    randomizeDishReplacement(){
        this.randomizeArray(this.ingredientReplacement, 26, 0);
    }

    /**
     * Randomize the checksReplacement array.
     */
    randomizeCheckReplacement(){
        this.randomizeArray(this.checksReplacement, 0, 0);
    }

    /**
     * Randomize an array
     * @param aArray The array to randomize
     */
    randomizeArray(aArray, aSkipBefore, aSkipAfter) {
        for (let i = aArray.length - 1 - aSkipAfter; i > aSkipBefore; i--) {
            const j = Math.floor(Math.random() * ((i + 1) - aSkipBefore)) + aSkipBefore;
            [aArray[i], aArray[j]] = [aArray[j], aArray[i]];
        }
    }

}

/**
 * Generate a Randomizer JSON to download
 * @param aPage The web page used to start the download
 */
function generateRandomizer(aPage) {
    let lRandomizer = new Randomizer(0);
    lRandomizer.randomizeCheckReplacement();
    let lIngredientOption = $('#ingredient');
    if (lIngredientOption.val() === "common") {
        lRandomizer.randomizeIngredientReplacement(true);
    } else if (lIngredientOption.val() === "all") {
        lRandomizer.randomizeIngredientReplacement(false);
    }
    if ($('#dish').val() === "all") {
        lRandomizer.randomizeDishReplacement();
    }
    var data = "text/json;charset=utf-8," + encodeURIComponent(JSON.stringify(lRandomizer));
    aPage.setAttribute("href", "data:"+data);
    aPage.setAttribute("download", "aquaria_randomized.json");
}
