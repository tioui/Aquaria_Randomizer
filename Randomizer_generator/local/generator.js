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
        this.ingredientReplacement = [];
        for(let i = 0; i < 26; i = i + 1) {
            this.ingredientReplacement.push(i);
        }
        this.checksReplacement = [];
        for(let i = 0; i < 196; i = i + 1) {
            this.checksReplacement.push(i);
        }
    }

    /**
     * Randomize the ingredientReplacement array.
     */
    randomizeIngredientReplacement(aCommons){
        let lSkip = 0;
        if (aCommons){
            lSkip = 3;
        }
        this.randomizeArray(this.ingredientReplacement, lSkip);
    }

    /**
     * Randomize the checksReplacement array.
     */
    randomizeCheckReplacement(){
        this.randomizeArray(this.checksReplacement, 0);
    }

    /**
     * Randomize an array
     * @param aArray The array to randomize
     */
    randomizeArray(aArray, aSkip) {
        for (let i = aArray.length - 1 - aSkip; i > 0; i--) {
            const j = Math.floor(Math.random() * (i + 1));
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

    if ($('#ingredient').val() === "common") {
        lRandomizer.randomizeIngredientReplacement(true);
    } else if ($('#ingredient').val() === "all") {
        lRandomizer.randomizeIngredientReplacement(false);
    }
    var data = "text/json;charset=utf-8," + encodeURIComponent(JSON.stringify(lRandomizer));
    aPage.setAttribute("href", "data:"+data);
    aPage.setAttribute("download", "aquaria_randomized.json");
}