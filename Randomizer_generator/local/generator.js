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
        this.uid = Date.now();
        this.aquarianTranslate = false;
        this.ingredientReplacement = []; // 26 base ingredients and 50 dishs
        for(let i = 0; i < 76; i = i + 1) {
            this.ingredientReplacement.push(i);
        }
        this.checksReplacement = [];
        for(let i = 0; i < 206; i = i + 1) {
            this.checksReplacement.push(i);
        }
    }

    /**
     * Randomize the ingredient part of the ingredientReplacement array.
     */
    randomizeIngredientReplacement(aCommons){
        let lSkip = 49;
        if (aCommons){
            lSkip = lSkip + 3;
        }
        this.randomizeArray(this.ingredientReplacement, 0, lSkip);
    }

    /**
     * Randomize the dish part of the ingredientReplacement array.
     */
    randomizeDishReplacement(){
        this.randomizeArray(this.ingredientReplacement, 27, 0);
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

function show_tips() {
    let lFiles = document.getElementById('jsonfile').files;
    let lFileReader = new FileReader();
    lFileReader.onload = function(aEvent) {
        console.log(aEvent);
        var lRandomizer = JSON.parse(aEvent.target.result);
        let lCheckSpans = document.getElementsByName("check_tips");
        for (let lSpan of lCheckSpans) {
            lSpan.style.display = 'none';
        }
        let lTips = new Tips(0);
        let lChecks = lTips.getTips($('#tips_item').val(), lRandomizer);
        for (let lCheck of lChecks) {
            document.getElementById(lCheck).style.display = 'block';
        }
    }

    lFileReader.readAsText(lFiles.item(0));

}

class Tips {

    getTips(aItemId, aRandomizer) {
        let lChecks = [];
        for (let i = 0; i < this.checks.length; i = i + 1) {
            if (this.checks[i].item_id === aItemId) {
                for (let j = 0; j < aRandomizer.checksReplacement.length; j = j + 1) {
                    if (aRandomizer.checksReplacement[j] == i) {
                        lChecks.push(this.checks[j].check_id);
                    }
                }

            }
        }
        return lChecks
    }

    constructor(aVersion) {
        let version = aVersion;
        this.checks = [
            { "check_id":"bulb_turtlecave", "item_id":"ingredient_leafpoultice"},
            { "check_id":"bulb_openwater_tl_1", "item_id":"ingredient_handroll"},
            { "check_id":"bulb_openwater_tl_2", "item_id":"ingredient_veggiesoup"},
            { "check_id":"bulb_openwater_tl_3", "item_id":"ingredient_butterysealoaf"},
            { "check_id":"bulb_openwater_tr_1", "item_id":"ingredient_healingpoultice"},
            { "check_id":"bulb_openwater_tr_2", "item_id":"ingredient_sealoaf"},
            { "check_id":"bulb_openwater_tr_3", "item_id":"ingredient_spicyroll"},
            { "check_id":"bulb_openwater_tr_4", "item_id":"ingredient_spicymeat"},
            { "check_id":"bulb_openwater_tr_5", "item_id":"ingredient_crabcake"},
            { "check_id":"bulb_openwater_tr_6", "item_id":"ingredient_spicyroll"},
            { "check_id":"bulb_openwater_bl_1", "item_id":"ingredient_leadershiproll"},
            { "check_id":"bulb_openwater_bl_2", "item_id":"ingredient_healingpoultice"},
            { "check_id":"bulb_skeleton_path_1", "item_id":"ingredient_tastycake"},
            { "check_id":"bulb_skeleton_path_2", "item_id":"ingredient_perogi"},
            { "check_id":"bulb_arnassi_1", "item_id":"ingredient_tastyroll"},
            { "check_id":"bulb_arnassi_2", "item_id":"ingredient_specialbulb"},
            { "check_id":"bulb_arnassi_3", "item_id":"ingredient_specialcake"},
            { "check_id":"bulb_sunworm_1", "item_id":"ingredient_plantleaf"},
            { "check_id":"bulb_sunworm_2", "item_id":"ingredient_turtlesoup"},
            { "check_id":"bulb_sunworm_3", "item_id":"ingredient_specialcake"},
            { "check_id":"bulb_sunworm_4", "item_id":"ingredient_specialbulb"},
            { "check_id":"bulb_tutorial_1", "item_id":"ingredient_handroll"},
            { "check_id":"bulb_tutorial_2", "item_id":"ingredient_hotsoup"},
            { "check_id":"bulb_tutorial_3", "item_id":"ingredient_heartysoup"},
            { "check_id":"bulb_abyss_l_1", "item_id":"ingredient_coldborscht"},
            { "check_id":"bulb_abyss_l_2", "item_id":"ingredient_healingpoultice"},
            { "check_id":"bulb_abyss_l_3", "item_id":"ingredient_sightpoultice"},
            { "check_id":"bulb_energy_temple_1_1", "item_id":"ingredient_leafpoultice"},
            { "check_id":"bulb_energy_temple_2_1", "item_id":"ingredient_spicyroll"},
            { "check_id":"bulb_energy_temple_3_1", "item_id":"ingredient_plantleaf"},
            { "check_id":"bulb_mithalas_city_01", "item_id":"ingredient_spicyroll"},
            { "check_id":"bulb_mithalas_city_02", "item_id":"ingredient_spicymeat"},
            { "check_id":"bulb_mithalas_city_03", "item_id":"ingredient_vedhaseacrisp"},
            { "check_id":"bulb_mithalas_city_04", "item_id":"ingredient_heartysoup"},
            { "check_id":"bulb_mithalas_city_05", "item_id":"ingredient_healingpoultice"},
            { "check_id":"bulb_mithalas_city_06", "item_id":"ingredient_vedhaseacrisp"},
            { "check_id":"bulb_mithalas_city_07", "item_id":"ingredient_rottenloaf"},
            { "check_id":"bulb_mithalas_city_08", "item_id":"ingredient_rottenmeat"},
            { "check_id":"bulb_mithalas_city_09", "item_id":"ingredient_smalltentacle"},
            { "check_id":"bulb_mithalas_city_10", "item_id":"ingredient_seacake"},
            { "check_id":"bulb_mithalas_city_11", "item_id":"ingredient_smallbone"},
            { "check_id":"bulb_mithalas_city_12", "item_id":"ingredient_handroll"},
            { "check_id":"bulb_cathedral_l_2", "item_id":"ingredient_heartysoup"},
            { "check_id":"bulb_boilerroom_1", "item_id":"ingredient_spicyroll"},
            { "check_id":"bulb_forest_tl_1", "item_id":"ingredient_seacake"},
            { "check_id":"bulb_forest_tl_2", "item_id":"ingredient_spicyroll"},
            { "check_id":"bulb_forest_tl_3", "item_id":"ingredient_leechingpoultice"},
            { "check_id":"bulb_forest_tl_4", "item_id":"ingredient_redbulb"},
            { "check_id":"bulb_forest_tr_1", "item_id":"ingredient_spiderroll"},
            { "check_id":"bulb_forest_tr_2", "item_id":"ingredient_veggiecake"},
            { "check_id":"bulb_forest_tr_3", "item_id":"ingredient_swampcake"},
            { "check_id":"bulb_forest_tr_4", "item_id":"ingredient_sharkfinsoup"},
            { "check_id":"bulb_forest_tr_5", "item_id":"ingredient_healingpoultice"},
            { "check_id":"bulb_forest_tr_6", "item_id":"ingredient_redbulb"},
            { "check_id":"bulb_forest_bl_1", "item_id":"ingredient_spiderroll"},
            { "check_id":"bulb_forest_boss_room_1", "item_id":"ingredient_handroll"},
            { "check_id":"bulb_forest_sprite_cave_1", "item_id":"ingredient_leechingpoultice"},
            { "check_id":"bulb_forest_sprite_cave_2", "item_id":"ingredient_veggiesoup"},
            { "check_id":"bulb_home_water_1", "item_id":"ingredient_smallegg"},
            { "check_id":"bulb_home_water_2", "item_id":"ingredient_leafpoultice"},
            { "check_id":"bulb_home_water_3", "item_id":"ingredient_leafpoultice"},
            { "check_id":"bulb_home_water_4", "item_id":"ingredient_plantleaf"},
            { "check_id":"bulb_home_water_5", "item_id":"ingredient_redbulb"},
            { "check_id":"bulb_home_water_6", "item_id":"ingredient_hotsoup"},
            { "check_id":"bulb_home_water_7", "item_id":"ingredient_fishmeat"},
            { "check_id":"bulb_home_water_8", "item_id":"ingredient_seacake"},
            { "check_id":"bulb_final_l_1", "item_id":"ingredient_arcanepoultice"},
            { "check_id":"bulb_final_l_2", "item_id":"ingredient_divinesoup"},
            { "check_id":"bulb_final_l_3", "item_id":"ingredient_spicyroll"},
            { "check_id":"bulb_final_l_4", "item_id":"ingredient_volcanoroll"},
            { "check_id":"bulb_final_l_5", "item_id":"ingredient_arcanepoultice"},
            { "check_id":"bulb_song_cave_1", "item_id":"ingredient_specialbulb"},
            { "check_id":"bulb_song_cave_2", "item_id":"ingredient_handroll"},
            { "check_id":"bulb_song_cave_3", "item_id":"ingredient_eeloil"},
            { "check_id":"bulb_song_cave_4", "item_id":"ingredient_leafpoultice"},
            { "check_id":"bulb_song_cave_5", "item_id":"ingredient_hotsoup"},
            { "check_id":"bulb_veil_tl_1", "item_id":"ingredient_spicysoup"},
            { "check_id":"bulb_veil_tl_2", "item_id":"ingredient_longlifesoup"},
            { "check_id":"bulb_veil_tl_3", "item_id":"ingredient_hotsoup"},
            { "check_id":"bulb_veil_tr_1", "item_id":"ingredient_sharkfinsoup"},
            { "check_id":"bulb_veil_tr_2", "item_id":"ingredient_legendarycake"},
            { "check_id":"bulb_veil_b_1", "item_id":"ingredient_swampcake"},
            { "check_id":"bulb_veil_b_2", "item_id":"ingredient_swampcake"},
            { "check_id":"bulb_ice_cave_1", "item_id":"ingredient_icecream"},
            { "check_id":"bulb_ice_cave_2", "item_id":"ingredient_berryicecream"},
            { "check_id":"bulb_ice_cave_3", "item_id":"ingredient_veggieicecream"},
            { "check_id":"bulb_ice_cave_4", "item_id":"ingredient_dumboicecream"},
            { "check_id":"bulb_ice_cave_5", "item_id":"ingredient_icecream"},
            { "check_id":"bulb_king_jellyfish_cave_1", "item_id":"ingredient_specialbulb"},
            { "check_id":"bulb_bubble_cave_1", "item_id":"ingredient_coldsoup"},
            { "check_id":"bulb_bubble_cave_2", "item_id":"ingredient_coldborscht"},
            { "check_id":"bulb_sun_temple_1", "item_id":"ingredient_glowingegg"},
            { "check_id":"bulb_sun_temple_2", "item_id":"ingredient_magicsoup"},
            { "check_id":"bulb_sun_temple_3", "item_id":"ingredient_royalsoup"},
            { "check_id":"bulb_sun_temple_4", "item_id":"ingredient_leadershiproll"},
            { "check_id":"bulb_sun_temple_5", "item_id":"ingredient_turtlesoup"},
            { "check_id":"bulb_sun_temple_6", "item_id":"ingredient_heartysoup"},
            { "check_id":"bulb_final_c_1", "item_id":"ingredient_Zuuna'sperogi"},
            { "check_id":"bulb_final_r_1", "item_id":"ingredient_plumpperogi"},
            { "check_id":"bulb_final_r_2", "item_id":"ingredient_arcanepoultice"},
            { "check_id":"bulb_final_r_3", "item_id":"ingredient_arcanepoultice"},
            { "check_id":"bulb_final_b_1", "item_id":"ingredient_longlifesoup"},
            { "check_id":"bulb_final_b_2", "item_id":"ingredient_spicyroll"},
            { "check_id":"bulb_final_boss_1", "item_id":"ingredient_Vedha'sCure-All"},
            { "check_id":"bulb_final_boss_2", "item_id":"ingredient_loafoflife"},
            { "check_id":"bulb_final_boss_3", "item_id":"ingredient_specialbulb"},
            { "check_id":"bulb_final_boss_4", "item_id":"ingredient_dumboicecream"},
            { "check_id":"bulb_starting_cave_1", "item_id":"ingredient_fishoil"},
            { "check_id":"bulb_starting_cave_2", "item_id":"ingredient_smallegg"},
            { "check_id":"bulb_abyss_r_1", "item_id":"ingredient_dumboicecream"},
            { "check_id":"bulb_abyss_r_2", "item_id":"ingredient_tastyroll"},
            { "check_id":"bulb_abyss_r_3", "item_id":"ingredient_healingpoultice"},
            { "check_id":"bulb_abyss_r_4", "item_id":"ingredient_hotborscht"},
            { "check_id":"bulb_cathedral_under_ground_1", "item_id":"ingredient_arcanepoultice"},
            { "check_id":"bulb_cathedral_under_ground_2", "item_id":"ingredient_plantleaf"},
            { "check_id":"bulb_cathedral_under_ground_3", "item_id":"ingredient_arcanepoultice"},
            { "check_id":"bulb_cathedral_under_ground_4", "item_id":"ingredient_redberry"},
            { "check_id":"bulb_cathedral_under_ground_5", "item_id":"ingredient_leafpoultice"},
            { "check_id":"bulb_cathedral_under_ground_6", "item_id":"ingredient_arcanepoultice"},
            { "check_id":"bulb_naija_home_1", "item_id":"ingredient_spicyroll"},
            { "check_id":"bulb_naija_home_2", "item_id":"ingredient_heartysoup"},
            { "check_id":"bulb_mermog_cave_1", "item_id":"ingredient_leechingpoultice"},
            { "check_id":"bulb_octo_cave_1", "item_id":"ingredient_sightpoultice"},
            { "check_id":"urn_mithalas_city_1", "item_id":"ingredient_rottenmeat"},
            { "check_id":"urn_mithalas_city_2", "item_id":"ingredient_glowingegg"},
            { "check_id":"urn_mithalas_city_3", "item_id":"ingredient_rainbowmushroom"},
            { "check_id":"urn_mithalas_city_4", "item_id":"ingredient_rainbowmushroom"},
            { "check_id":"urn_mithalas_city_5", "item_id":"ingredient_rainbowmushroom"},
            { "check_id":"urn_mithalas_city_6", "item_id":"ingredient_plantleaf"},
            { "check_id":"urn_mithalas_city_7", "item_id":"ingredient_spicyroll"},
            { "check_id":"urn_cathedral_l_1", "item_id":"ingredient_rainbowmushroom"},
            { "check_id":"urn_cathedral_l_2", "item_id":"ingredient_smallbone"},
            { "check_id":"urn_cathedral_l_3", "item_id":"ingredient_rottenmeat"},
            { "check_id":"urn_cathedral_l_4", "item_id":"ingredient_fishoil"},
            { "check_id":"urn_cathedral_l_5", "item_id":"ingredient_rottenmeat"},
            { "check_id":"urn_cathedral_l_6", "item_id":"ingredient_rainbowsoup"},
            { "check_id":"urn_cathedral_r_01", "item_id":"ingredient_plantleaf"},
            { "check_id":"urn_cathedral_r_02", "item_id":"ingredient_rottencake"},
            { "check_id":"urn_cathedral_r_03", "item_id":"ingredient_toughcake"},
            { "check_id":"urn_cathedral_r_04", "item_id":"ingredient_spicyroll"},
            { "check_id":"urn_cathedral_r_05", "item_id":"ingredient_rottenmeat"},
            { "check_id":"urn_cathedral_r_06", "item_id":"ingredient_plantleaf"},
            { "check_id":"urn_cathedral_r_07", "item_id":"ingredient_leechingpoultice"},
            { "check_id":"urn_cathedral_r_08", "item_id":"ingredient_smallbone"},
            { "check_id":"urn_cathedral_r_09", "item_id":"ingredient_plantleaf"},
            { "check_id":"urn_cathedral_r_10", "item_id":"ingredient_rottenmeat"},
            { "check_id":"urn_cathedral_r_11", "item_id":"ingredient_poisonloaf"},
            { "check_id":"urn_cathedral_r_12", "item_id":"ingredient_poisonsoup"},
            { "check_id":"urn_openwater_tr_1", "item_id":"ingredient_smallbone"},
            { "check_id":"urn_openwater_tr_2", "item_id":"ingredient_rottenmeat"},
            { "check_id":"urn_openwater_tr_3", "item_id":"ingredient_sealoaf"},
            { "check_id":"crate_sunkencity_2_1", "item_id":"ingredient_fishoil"},
            { "check_id":"crate_sunkencity_2_2", "item_id":"ingredient_mushroom"},
            { "check_id":"crate_sunkencity_2_3", "item_id":"ingredient_spicymeat"},
            { "check_id":"crate_sunkencity_1_1", "item_id":"ingredient_seacake"},
            { "check_id":"crate_sunkencity_1_2", "item_id":"ingredient_plantleaf"},
            { "check_id":"beating_simon", "item_id":"upgrade_wok"},
            { "check_id":"health_egg_1", "item_id":"upgrade_health"},
            { "check_id":"health_egg_2", "item_id":"upgrade_health"},
            { "check_id":"health_egg_3", "item_id":"upgrade_health"},
            { "check_id":"health_egg_4", "item_id":"upgrade_health"},
            { "check_id":"health_egg_5", "item_id":"upgrade_health"},
            { "check_id":"collect_anemone", "item_id":"collectible_anemone"},
            { "check_id":"collect_energy_temple", "item_id":"collectible_energy_temple"},
            { "check_id":"collect_arnassi_statue", "item_id":"collectible_arnassi_statue"},
            { "check_id":"collect_mithalas_banner", "item_id":"collectible_mithalas_banner"},
            { "check_id":"collect_bio_seed", "item_id":"collectible_bio_seed"},
            { "check_id":"collect_blackpearl", "item_id":"collectible_blackpearl"},
            { "check_id":"collect_treasure_chest", "item_id":"collectible_treasure_chest"},
            { "check_id":"collect_energy_boss", "item_id":"collectible_energy_boss"},
            { "check_id":"collect_energy_statue", "item_id":"collectible_energy_statue"},
            { "check_id":"collect_golden_gear", "item_id":"collectible_golden_gear"},
            { "check_id":"collect_jelly_plant", "item_id":"collectible_jelly_plant"},
            { "check_id":"collect_mithala_doll", "item_id":"collectible_mithala_doll"},
            { "check_id":"collect_mithalas_pot", "item_id":"collectible_mithalas_pot"},
            { "check_id":"collect_big_seed", "item_id":"collectible_big_seed"},
            { "check_id":"collect_seed_bag", "item_id":"collectible_seed_bag"},
            { "check_id":"collect_skull", "item_id":"collectible_skull"},
            { "check_id":"collect_jelly_beacon", "item_id":"collectible_jelly_beacon"},
            { "check_id":"collect_spore_seed", "item_id":"collectible_spore_seed"},
            { "check_id":"collect_gold_star", "item_id":"collectible_gold_star"},
            { "check_id":"collect_stone_head", "item_id":"collectible_stone_head"},
            { "check_id":"collect_sun_key", "item_id":"collectible_sun_key"},
            { "check_id":"collect_trident_head", "item_id":"collectible_trident_head"},
            { "check_id":"collect_turtle_egg", "item_id":"collectible_turtle_egg"},
            { "check_id":"collect_upsidedown_seed", "item_id":"collectible_upsidedown_seed"},
            { "check_id":"collect_walker", "item_id":"collectible_walker"},
            { "check_id":"collect_crab_costume", "item_id":"collectible_crab_costume"},
            { "check_id":"collect_jelly_costume", "item_id":"collectible_jelly_costume"},
            { "check_id":"collect_mithalan_costume", "item_id":"collectible_mithalan_costume"},
            { "check_id":"collect_mutant_costume", "item_id":"collectible_mutant_costume"},
            { "check_id":"collect_seahorse_costume", "item_id":"collectible_seahorse_costume"},
            { "check_id":"collect_teen_costume", "item_id":"collectible_teen_costume"},
            { "check_id":"collect_urchin_costume", "item_id":"collectible_urchin_costume"},
            { "check_id":"collect_nautilus", "item_id":"collectible_nautilus"},
            { "check_id":"collect_blaster", "item_id":"collectible_blaster"},
            { "check_id":"collect_dumbo", "item_id":"collectible_dumbo"},
            { "check_id":"collect_piranha", "item_id":"collectible_piranha"},
            { "check_id":"urn_cathedral_r_13", "item_id":"ingredient_leafpoultice"}
        ];
    }
}
