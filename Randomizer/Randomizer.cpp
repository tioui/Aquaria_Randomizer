/**
 * @author      : Louis Marchand (prog@tioui.com)
 * @created     : mercredi jan 10, 2024 16:08:04 EST
 * @license     : MIT
 * Class that encapsulate every randomization functionalities
 */

#include "Randomizer.h"
#include <cassert>
#include <utility>
#include <vector>
#include "apclient.hpp"
#include "../Aquaria/Game.h"

// /**
//  * Constructor of the object
//  * \param aName The username
//  * \param aServer The server ip and port
//  */
// Randomizer::Randomizer(std::string aName, std::string aServer)
// {
// 	dsq = NULL;
// 	ingredientReplacement = {};
// 	for (int i = 0; i < 26; i = i + 1) {
// 		ingredientReplacement.push_back(i);
// 	}
// 	name = aName;
// 	server = aServer;
// }


/**
 * Constructor for the Randomizer
 */
Randomizer::Randomizer() {
	ingredientReplacement = new std::vector<int>();
    error = false;
    errorMessage = "";
    checks = new std::vector<check_t>();
    ingredients = new std::vector<ingredient_t>();
    initialiseChecks();
}

/**
 * Initialize the ingredients vector
 */
void Randomizer::initialiseIngredients() {
    ingredients->push_back({"plantleaf", IT_LEAF});
    ingredients->push_back({"crabmeat", IT_MEAT});
    ingredients->push_back({"fishmeat", IT_MEAT});
    ingredients->push_back({"spicymeat", IT_MEAT});
    ingredients->push_back({"rottenmeat", IT_MEAT});
    ingredients->push_back({"rubberymeat", IT_MEAT});
    ingredients->push_back({"turtlemeat", IT_MEAT});
    ingredients->push_back({"swordfishsteak", IT_MEAT});
    ingredients->push_back({"fishoil", IT_OIL});
    ingredients->push_back({"jellyoil", IT_OIL});
    ingredients->push_back({"eeloil", IT_OIL});
    ingredients->push_back({"smallbone", IT_BONE});
    ingredients->push_back({"smallegg", IT_EGG});
    ingredients->push_back({"glowingegg", IT_EGG});
    ingredients->push_back({"spideregg", IT_EGG});
    ingredients->push_back({"smalleye", IT_PART});
    ingredients->push_back({"sharkfin", IT_PART});
    ingredients->push_back({"smalltentacle", IT_TENTACLE});
    ingredients->push_back({"redberry", IT_BERRY});
    ingredients->push_back({"mushroom", IT_MUSHROOM});
    ingredients->push_back({"rainbowmushroom", IT_MUSHROOM});
    ingredients->push_back({"icechunk", IT_ICECHUNK});
    ingredients->push_back({"plantbulb", IT_BULB});
    ingredients->push_back({"specialbulb", IT_BULB});
    ingredients->push_back({"rukhegg", IT_EGG});
    ingredients->push_back({"redbulb", IT_BULB});
}


/**
 * Initialize every Checks
 */
void Randomizer::initialiseChecks(){
    checks->push_back({2001, "bulb_turtlecave","ingredient_poultice",3, "Leaf poultice"});
    checks->push_back({2002, "bulb_openwater_tl_1","ingredient_handroll",1, "Hand roll"});
    checks->push_back({2003, "bulb_openwater_tl_2","ingredient_veggiesoup",1, "Veggie soup"});
    checks->push_back({2004, "bulb_openwater_tl_3","ingredient_butterysealoaf",1, "Buttery sea loaf"});
    checks->push_back({2005, "bulb_openwater_tr_1","ingredient_healingpoultice",1, "Healing poultice"});
    checks->push_back({2006, "bulb_openwater_tr_2","ingredient_sealoaf",2, "Sea loaf"});
    checks->push_back({2007, "bulb_openwater_tr_3","ingredient_spicyroll",1, "Spicy roll"});
    checks->push_back({2008, "bulb_openwater_tr_4","ingredient_spicymeat",2, "Spicy meat"});
    checks->push_back({2009, "bulb_openwater_tr_5","ingredient_crabcake",1, "Crab cake"});
    checks->push_back({2010, "bulb_openwater_tr_6","ingredient_spicyroll",1, "Spicy roll"});
    checks->push_back({2011, "bulb_openwater_bl_1","ingredient_leadershiproll",2, "Leadership roll"});
    checks->push_back({2012, "bulb_openwater_bl_2","ingredient_healingpoultice",2, "Healing poultice"});
    checks->push_back({2013, "bulb_skeleton_path_1","ingredient_tastycake",1, "Tasty cake"});
    checks->push_back({2014, "bulb_skeleton_path_2","ingredient_perogi",1, "Perogi"});
    checks->push_back({2015, "bulb_arnassi_1","ingredient_tastyrool",1, "Tasty roll"});
    checks->push_back({2016, "bulb_arnassi_2","ingredient_specialbulb",1, "Special bulb"});
    checks->push_back({2017, "bulb_arnassi_3","ingredient_specialcake",1, "Special cake"});
    checks->push_back({2018, "bulb_sunworm_1","ingredient_plantleaf",3, "Plant leaf"});
    checks->push_back({2019, "bulb_sunworm_2","ingredient_turtlesoup",1, "Turtle soup"});
    checks->push_back({2020, "bulb_sunworm_3","ingredient_specialcake",1, "Special cake"});
    checks->push_back({2021, "bulb_sunworm_4","ingredient_specialbulb",1, "Special bulb"});
    checks->push_back({2022, "bulb_tutorial_1","ingredient_handroll",1, "Hand roll"});
    checks->push_back({2023, "bulb_tutorial_2","ingredient_hotsoup",1, "Hot soup"});
    checks->push_back({2024, "bulb_tutorial_3","ingredient_heartysoup",1, "Hearty soup"});
    checks->push_back({2025, "bulb_abyss_l_1","ingredient_coldborscht",1, "Cold borscht"});
    checks->push_back({2026, "bulb_abyss_l_2","ingredient_healingpoultice",2, "Healing poultice"});
    checks->push_back({2027, "bulb_abyss_l_3","ingredient_sightpoultice",1, "Sight poultice"});
    checks->push_back({2028, "bulb_energy_temple_1_1","ingredient_poultice",1, "Leaf poultice"});
    checks->push_back({2029, "bulb_energy_temple_2_1","ingredient_spicyroll",1, "Spicy roll"});
    checks->push_back({2030, "bulb_energy_temple_3_1","ingredient_plantleaf",2, "Plant leaf"});
    checks->push_back({2031, "bulb_mithalas_city_01","ingredient_spicyroll",1, "Spicy roll"});
    checks->push_back({2032, "bulb_mithalas_city_02","ingredient_spicymeat",2, "Spicy meat"});
    checks->push_back({2033, "bulb_mithalas_city_03","ingredient_vedhaseacrisp",1, "Vedha sea crisp"});
    checks->push_back({2034, "bulb_mithalas_city_04","ingredient_heartysoup",1, "Hearty soup"});
    checks->push_back({2035, "bulb_mithalas_city_05","ingredient_healingpoultice",1, "Healing poultice"});
    checks->push_back({2036, "bulb_mithalas_city_06","ingredient_vedhaseacrisp",1, "Vedha sea crisp"});
    checks->push_back({2037, "bulb_mithalas_city_07","ingredient_rottenloaf",8, "Rotten loaf"});
    checks->push_back({2038, "bulb_mithalas_city_08","ingredient_rottenmeat",8, "Rotten meat"});
    checks->push_back({2039, "bulb_mithalas_city_09","ingredient_smalltentacle",2, "Small tentacle"});
    checks->push_back({2040, "bulb_mithalas_city_10","ingredient_seacake",1, "Sea cake"});
    checks->push_back({2041, "bulb_mithalas_city_11","ingredient_smallbone",3, "Small bone"});
    checks->push_back({2042, "bulb_mithalas_city_12","ingredient_handroll",1, "Hand roll"});
    checks->push_back({2043, "bulb_cathedral_l_2","ingredient_heartysoup",1, "Hearty soup"});
    checks->push_back({2044, "bulb_boilerroom_1","ingredient_spicyroll",1, "Spicy rool"});
    checks->push_back({2045, "bulb_forest_tl_1","ingredient_seacake",1, "Sea cake"});
    checks->push_back({2046, "bulb_forest_tl_2","ingredient_spicyroll",1, "Spicy roll"});
    checks->push_back({2047, "bulb_forest_tl_3","ingredient_leechingpoultice",1, "Leeching poultice"});
    checks->push_back({2048, "bulb_forest_tl_4","ingredient_redbulb",2, "Red bulb"});
    checks->push_back({2049, "bulb_forest_tr_1","ingredient_spiderroll",1, "Spider roll"});
    checks->push_back({2050, "bulb_forest_tr_2","ingredient_veggiecake",1, "Veggie cake"});
    checks->push_back({2051, "bulb_forest_tr_3","ingredient_swampcake",1, "Swamp cake"});
    checks->push_back({2052, "bulb_forest_tr_4","ingredient_sharkfinsoup",1, "Shark fin soup"});
    checks->push_back({2053, "bulb_forest_tr_5","ingredient_healingpoultice",1, "Healing poultice"});
    checks->push_back({2054, "bulb_forest_tr_6","ingredient_redbulb",2, "Red bulb"});
    checks->push_back({2055, "bulb_forest_bl_1","ingredient_spiderroll",1, "Spider roll"});
    checks->push_back({2056, "bulb_forest_boss_room_1","ingredient_handroll",1, "Hand roll"});
    checks->push_back({2057, "bulb_forest_sprite_cave_1","ingredient_leechingpoultice",1, "Leeching poultice"});
    checks->push_back({2058, "bulb_forest_sprite_cave_2","ingredient_veggiesoup",1, "Veggie soup"});
    checks->push_back({2059, "bulb_home_water_1","ingredient_smallegg",2, "Small egg"});
    checks->push_back({2060, "bulb_home_water_2","ingredient_poultice",1, "Leaf poultice"});
    checks->push_back({2061, "bulb_home_water_3","ingredient_poultice",1, "Leaf poultice"});
    checks->push_back({2062, "bulb_home_water_4","ingredient_plantleaf",3, "Plant leaf"});
    checks->push_back({2063, "bulb_home_water_5","ingredient_redbulb",2, "Red bulb"});
    checks->push_back({2064, "bulb_home_water_6","ingredient_hotsoup",1, "Hot soup"});
    checks->push_back({2065, "bulb_home_water_7","ingredient_fishmeat",2, "Fish meat"});
    checks->push_back({2066, "bulb_home_water_8","ingredient_seacake",1, "Sea cake"});
    checks->push_back({2067, "bulb_final_l_1","ingredient_arcanepoultice",1, "Arcane poultice"});
    checks->push_back({2068, "bulb_final_l_2","ingredient_divinesoup",1, "Divine soup"});
    checks->push_back({2069, "bulb_final_l_3","ingredient_spicyroll",1, "Spicy roll"});
    checks->push_back({2070, "bulb_final_l_4","ingredient_volcanoroll",1, "Volcano roll"});
    checks->push_back({2071, "bulb_final_l_5","ingredient_arcanepoultice",1, "Arcane poultice"});
    checks->push_back({2072, "bulb_song_cave_1","ingredient_specialbulb",1, "Special bulb"});
    checks->push_back({2073, "bulb_song_cave_2","ingredient_handroll",1, "Hand roll"});
    checks->push_back({2074, "bulb_song_cave_3","ingredient_eeloil",2, "Eel oil"});
    checks->push_back({2075, "bulb_song_cave_4","ingredient_poultice",1, "Leaf poultice"});
    checks->push_back({2076, "bulb_song_cave_5","ingredient_hotsoup",1, "Hot soup"});
    checks->push_back({2077, "bulb_veil_tl_1","ingredient_spicysoup",1, "Spicy soup"});
    checks->push_back({2078, "bulb_veil_tl_2","ingredient_longlifesoup",1, "Long life soup"});
    checks->push_back({2079, "bulb_veil_tl_3","ingredient_hotsoup",2, "Hot soup"});
    checks->push_back({2080, "bulb_veil_tr_1","ingredient_sharkfinsoup",1, "Shark fin soup"});
    checks->push_back({2081, "bulb_veil_tr_2","ingredient_legendarycake",1, "Legendary cake"});
    checks->push_back({2082, "bulb_veil_b_1","ingredient_swampcake",1, "Swamp cake"});
    checks->push_back({2083, "bulb_veil_b_2","ingredient_swampcake",1, "Swamp cake"});
    checks->push_back({2084, "bulb_ice_cave_1","ingredient_icecream",1, "Ice cream"});
    checks->push_back({2085, "bulb_ice_cave_2","ingredient_berryicecream",1, "Berry ice cream"});
    checks->push_back({2086, "bulb_ice_cave_3","ingredient_veggieicecream",1, "Veggie ice cream"});
    checks->push_back({2087, "bulb_ice_cave_4","ingredient_dumboicecream",1, "Dumbo ice cream"});
    checks->push_back({2088, "bulb_ice_cave_5","ingredient_icecream",1, "Ice cream"});
    checks->push_back({2089, "bulb_king_jellyfish_cave_1","ingredient_specialbulb",1, "Special bulb"});
    checks->push_back({2090, "bulb_bubble_cave_1","ingredient_coldsoup",1, "Cold soup"});
    checks->push_back({2091, "bulb_bubble_cave_2","ingredient_coldborscht",1, "Cold borscht"});
    checks->push_back({2092, "bulb_sun_temple_1","ingredient_glowingegg",2, "Glowing egg"});
    checks->push_back({2093, "bulb_sun_temple_2","ingredient_magicsoup",1, "Magic soup"});
    checks->push_back({2094, "bulb_sun_temple_3","ingredient_royalsoup",1, "Royal soup"});
    checks->push_back({2095, "bulb_sun_temple_4","ingredient_leadershiproll",1, "Leadership roll"});
    checks->push_back({2096, "bulb_sun_temple_5","ingredient_turtlesoup",1, "Turtle soup"});
    checks->push_back({2097, "bulb_sun_temple_6","ingredient_heartysoup",1, "Hearty soup"});
    checks->push_back({2098, "bulb_final_c_1","ingredient_Zuuna'sperogi",1, "Zuuna's perogi"});
    checks->push_back({2099, "bulb_final_r_1","ingredient_plumpperogi",1, "Plump perogi"});
    checks->push_back({2100, "bulb_final_r_2","ingredient_arcanepoultice",1, "Arcane poultice"});
    checks->push_back({2101, "bulb_final_r_3","ingredient_arcanepoultice",1, "Arcane poultice"});
    checks->push_back({2102, "bulb_final_b_1","ingredient_longlifesoup",1, "Long life soup"});
    checks->push_back({2103, "bulb_final_b_2","ingredient_spicyroll",1, "Spicy roll"});
    checks->push_back({2104, "bulb_final_boss_1","ingredient_Vedha'sCure-All",1, "Vedha's Cure-All"});
    checks->push_back({2105, "bulb_final_boss_2","ingredient_loafoflife",1, "Loaf of life"});
    checks->push_back({2106, "bulb_final_boss_3","ingredient_specialbulb",1, "Special bulb"});
    checks->push_back({2107, "bulb_final_boss_4","ingredient_dumboicecream",1, "Dumbo ice cream"});
    checks->push_back({2108, "bulb_starting_cave_1","ingredient_fishoil",1, "Fish oil"});
    checks->push_back({2109, "bulb_starting_cave_2","ingredient_smallegg",1, "Small egg"});
    checks->push_back({2110, "bulb_abyss_r_1","ingredient_dumboicecream",1, "Dumbo ice cream"});
    checks->push_back({2111, "bulb_abyss_r_2","ingredient_tastyroll",1, "Tasty roll"});
    checks->push_back({2112, "bulb_abyss_r_3","ingredient_healingpoultice",1, "Healing poultice"});
    checks->push_back({2113, "bulb_abyss_r_4","ingredient_hotborscht",1, "Hot borscht"});
    checks->push_back({2114, "bulb_cathedral_under_ground_1","ingredient_arcanepoultice",1, "Arcane poultice"});
    checks->push_back({2115, "bulb_cathedral_under_ground_2","ingredient_plantleaf",1, "Plant leaf"});
    checks->push_back({2116, "bulb_cathedral_under_ground_3","ingredient_arcanepoultice",1, "Arcane poultice"});
    checks->push_back({2117, "bulb_cathedral_under_ground_4","ingredient_redberry",1, "Red berry"});
    checks->push_back({2118, "bulb_cathedral_under_ground_5","ingredient_poultice",1, "Leaf poultice"});
    checks->push_back({2119, "bulb_cathedral_under_ground_6","ingredient_arcanepoultice",1, "Arcane poultice"});
    checks->push_back({2120, "bulb_naija_home_1","ingredient_spicyroll",1, "Spicy roll"});
    checks->push_back({2121, "bulb_naija_home_2","ingredient_heartysoup",1, "Hearty soup"});
    checks->push_back({2122, "bulb_mermog_cave_1","ingredient_leechingpoultice",1, "Leeching poultice"});
    checks->push_back({2123, "bulb_octo_cave_1","ingredient_sightpoultice",1, "Sight poultice"});
    checks->push_back({2124, "urn_mithalas_city_1","ingredient_rottenmeat",2, "Rotten meat"});
    checks->push_back({2125, "urn_mithalas_city_2","ingredient_glowingegg",1, "Glowing egg"});
    checks->push_back({2126, "urn_mithalas_city_3","ingredient_rainbowmushroom",1, "Rainbow mushroom"});
    checks->push_back({2127, "urn_mithalas_city_4","ingredient_rainbowmushroom",1, "Rainbow mushroom"});
    checks->push_back({2128, "urn_mithalas_city_5","ingredient_rainbowmushroom",1, "Rainbow mushroom"});
    checks->push_back({2129, "urn_mithalas_city_6","ingredient_plantleaf",3, "Plant leaf"});
    checks->push_back({2130, "urn_mithalas_city_7","ingredient_spicyroll",1, "Spicy roll"});
    checks->push_back({2131, "urn_cathedral_l_1","ingredient_rainbowmushroom",1, "Rainbow mushroom"});
    checks->push_back({2132, "urn_cathedral_l_2","ingredient_smallbone",2, "Small bone"});
    checks->push_back({2133, "urn_cathedral_l_3","ingredient_rottenmeat",1, "Rotten meat"});
    checks->push_back({2134, "urn_cathedral_l_4","ingredient_fishoil",1, "Fish oil"});
    checks->push_back({2135, "urn_cathedral_l_5","ingredient_rottenmeat",1, "Rotten meat"});
    checks->push_back({2136, "urn_cathedral_l_6","ingredient_rainbowsoup",1, "Rainbow soup"});
    checks->push_back({2137, "urn_cathedral_r_01","ingredient_plantleaf",1, "Plant leaf"});
    checks->push_back({2138, "urn_cathedral_r_02","ingredient_rottencake",1, "Rotten cake"});
    checks->push_back({2139, "urn_cathedral_r_03","ingredient_toughcake",1, "Tough cake"});
    checks->push_back({2140, "urn_cathedral_r_04","ingredient_spicyroll",1, "Spicy roll"});
    checks->push_back({2141, "urn_cathedral_r_05","ingredient_rottenmeat",1, "Rottem meat"});
    checks->push_back({2142, "urn_cathedral_r_06","ingredient_plantleaf",1, "Plant leaf"});
    checks->push_back({2143, "urn_cathedral_r_07","ingredient_leechingpoultice",1, "Leeching poultice"});
    checks->push_back({2144, "urn_cathedral_r_08","ingredient_smallbone",3, "Small bone"});
    checks->push_back({2145, "urn_cathedral_r_09","ingredient_plantleaf",2, "Plant leaf"});
    checks->push_back({2146, "urn_cathedral_r_10","ingredient_rottenmeat",1, "Rotten meat"});
    checks->push_back({2147, "urn_cathedral_r_11","ingredient_poisonloaf",1, "Poison loaf"});
    checks->push_back({2148, "urn_cathedral_r_12","ingredient_poisonsoup",1, "Poison soup"});
    checks->push_back({2149, "urn_openwater_tr_1","ingredient_smallbone",3, "Small bone"});
    checks->push_back({2150, "urn_openwater_tr_2","ingredient_rottenmeat",1, "Rotten meat"});
    checks->push_back({2151, "urn_openwater_tr_3","ingredient_sealoaf",1, "Sea loaf"});
    checks->push_back({2152, "crate_sunkencity_2_1","ingredient_fishoil",3, "Fish oil"});
    checks->push_back({2153, "crate_sunkencity_2_2","ingredient_mushroom",2, "Mushroom"});
    checks->push_back({2154, "crate_sunkencity_2_3","ingredient_spicymeat",2, "Spicy meat"});
    checks->push_back({2155, "crate_sunkencity_1_1","ingredient_seacake",1, "Sea cake"});
    checks->push_back({2156, "crate_sunkencity_1_2","ingredient_plantleaf",3, "Plant leaf"});
    checks->push_back({2157, "beating_simon","upgrade_wok",1, "Wok"});
    checks->push_back({2158, "health_egg_1","upgrade_health_1",1, "Health"});
    checks->push_back({2159, "health_egg_2","upgrade_health_2",1, "Health"});
    checks->push_back({2160, "health_egg_3","upgrade_health_3",1, "Health"});
    checks->push_back({2161, "health_egg_4","upgrade_health_4",1, "Health"});
    checks->push_back({2162, "health_egg_5","upgrade_health_5",1, "Health"});
    checks->push_back({FLAG_COLLECTIBLE_INHOME_ANEMONESEED, "collect_anemone","collectible_anemone",1, "Anemone"});
    checks->push_back({FLAG_COLLECTIBLE_INHOME_ARNASSISTATUE, "collect_arnassi_statue","collectible_arnassi_statue",1, "Arnassi statue"});
    checks->push_back({FLAG_COLLECTIBLE_INHOME_BIOSEED, "collect_mithalas_banner","collectible_mithalas_banner",1, "Mithalas banner"});
    checks->push_back({FLAG_COLLECTIBLE_INHOME_BIOSEED, "collect_bio_seed","collectible_bio_seed",1, "Bio sead"});
    checks->push_back({FLAG_COLLECTIBLE_INHOME_BLACKPEARL, "collect_blackpearl","collectible_blackpearl",1, "Black pearl"});
    checks->push_back({FLAG_COLLECTIBLE_INHOME_CHEST, "collect_treasure_chest","collectible_treasure_chest",1, "Treasure chest"});
    checks->push_back({FLAG_COLLECTIBLE_INHOME_ENERGYBOSS, "collect_energy_boss","collectible_energy_boss",1, "Energy boss"});
    checks->push_back({FLAG_COLLECTIBLE_INHOME_ENERGYSTATUE, "collect_energy_statue","collectible_energy_statue",1, "Energy statue"});
    checks->push_back({FLAG_COLLECTIBLE_INHOME_GEAR, "collect_golden_gear","collectible_golden_gear",1, "Golden gear"});
    checks->push_back({FLAG_COLLECTIBLE_INHOME_JELLYPLANT, "collect_jelly_plant","collectible_jelly_plant",1, "Jelly plant"});
    checks->push_back({FLAG_COLLECTIBLE_INHOME_MITHALADOLL, "collect_mithala_doll","collectible_mithala_doll",1, "Mithalas doll"});
    checks->push_back({FLAG_COLLECTIBLE_INHOME_MITHALASPOT, "collect_mithala_spot","collectible_mithala_spot",1, "Mithalas spot"});
    checks->push_back({FLAG_COLLECTIBLE_INHOME_NAIJACAVE, "collect_big_seed","collectible_big_seed",1, "Big seed"});
    checks->push_back({FLAG_COLLECTIBLE_INHOME_SEEDBAG, "collect_seed_bag","collectible_seed_bag",1, "Seed bag"});
    checks->push_back({FLAG_COLLECTIBLE_INHOME_SKULL, "collect_skull","collectible_skull",1, "Skull"});
    checks->push_back({FLAG_COLLECTIBLE_INHOME_SONGCAVE, "collect_jelly_beacon","collectible_jelly_beacon",1, "Jelly beacon"});
    checks->push_back({FLAG_COLLECTIBLE_INHOME_SPORESEED, "collect_spore_seed","collectible_spore_seed",1, "Spore seed"});
    checks->push_back({FLAG_COLLECTIBLE_INHOME_STARFISH, "collect_gold_star","collectible_gold_star",1, "Golden star"});
    checks->push_back({FLAG_COLLECTIBLE_INHOME_STONEHEAD, "collect_stone_head","collectible_stone_head",1, "Stone head"});
    checks->push_back({FLAG_COLLECTIBLE_INHOME_SUNKEY, "collect_sun_key","collectible_sun_key",1, "Sun key"});
    checks->push_back({FLAG_COLLECTIBLE_INHOME_TRIDENTHEAD, "collect_trident_head","collectible_trident_head",1, "Trident"});
    checks->push_back({FLAG_COLLECTIBLE_INHOME_TURTLEEGG, "collect_turtle_egg","collectible_turtle_egg",1, "Turtle egg"});
    checks->push_back({FLAG_COLLECTIBLE_INHOME_UPSIDEDOWNSEED, "collect_upsidedown_seed","collectible_upsidedown_seed",1, "Upside down seed"});
    checks->push_back({FLAG_COLLECTIBLE_INHOME_WALKERBABY, "collect_walker","collectible_walker",1, "Baby walker"});
    checks->push_back({FLAG_COLLECTIBLE_INHOME_CRABCOSTUME, "collect_crab_costume","collectible_crab_costume",1, "Crab costume"});
    checks->push_back({FLAG_COLLECTIBLE_INHOME_JELLYCOSTUME, "collect_jelly_costume","collectible_jelly_costume",1, "Jelly costume"});
    checks->push_back({FLAG_COLLECTIBLE_INHOME_MITHALANCOSTUME, "collect_mithalan_costume","collectible_mithalan_costume",1, "Mithalan costume"});
    checks->push_back({FLAG_COLLECTIBLE_INHOME_MUTANTCOSTUME, "collect_mutant_costume","collectible_mutant_costume",1, "Mutan costume"});
    checks->push_back({FLAG_COLLECTIBLE_INHOME_SEAHORSECOSTUME, "collect_seahorse_costume","collectible_seahorse_costume",1, "Seahorse costume"});
    checks->push_back({FLAG_COLLECTIBLE_INHOME_TEENCOSTUME, "collect_teen_costume","collectible_teen_costume",1, "Teen costume"});
    checks->push_back({FLAG_COLLECTIBLE_INHOME_URCHINCOSTUME, "collect_urchin_costume","collectible_urchin_costume",1, "Urchin costume"});
    checks->push_back({FLAG_COLLECTIBLE_INHOME_BLASTER, "collect_blaster","collectible_blaster",1, "Baby blaster"});
    checks->push_back({FLAG_COLLECTIBLE_INHOME_NAUTILUS, "collect_nautilus","collectible_nautilus",1, "Baby nautilus"});
    checks->push_back({FLAG_COLLECTIBLE_INHOME_PIRANHA, "collect_piranha","collectible_piranha",1, "Baby piranha"});
}


/**
 * Get a new collectible item to activate in the local game
 * @param aCollectible The collectible item to activate
 */
void Randomizer::receivingCollectible(const std::string& aCollectible) {
	if (aCollectible == "anemone"){
		dsq->continuity.setFlag(FLAG_COLLECTIBLE_INHOME_ANEMONESEED, 1);
	} else if (aCollectible == "arnassi_statue") {
		dsq->continuity.setFlag(FLAG_COLLECTIBLE_INHOME_ARNASSISTATUE, 1);
	} else if (aCollectible == "mithalas_banner") {
		dsq->continuity.setFlag(FLAG_COLLECTIBLE_INHOME_BANNER, 1);
	} else if (aCollectible == "bio_seed") {
		dsq->continuity.setFlag(FLAG_COLLECTIBLE_INHOME_BIOSEED, 1);
	} else if (aCollectible == "blackpearl") {
		dsq->continuity.setFlag(FLAG_COLLECTIBLE_INHOME_BLACKPEARL, 1);
	} else if (aCollectible == "treasure_chest") {
		dsq->continuity.setFlag(FLAG_COLLECTIBLE_INHOME_CHEST, 1);
	} else if (aCollectible == "energy_boss") {
		dsq->continuity.setFlag(FLAG_COLLECTIBLE_INHOME_ENERGYBOSS, 1);
	} else if (aCollectible == "energy_statue") {
		dsq->continuity.setFlag(FLAG_COLLECTIBLE_INHOME_ENERGYSTATUE, 1);
	} else if (aCollectible == "golden_gear") {
		dsq->continuity.setFlag(FLAG_COLLECTIBLE_INHOME_GEAR, 1);
	} else if (aCollectible == "jelly_plant") {
		dsq->continuity.setFlag(FLAG_COLLECTIBLE_INHOME_JELLYPLANT, 1);
	} else if (aCollectible == "mithala_doll") {
		dsq->continuity.setFlag(FLAG_COLLECTIBLE_INHOME_MITHALADOLL, 1);
	} else if (aCollectible == "mithala_spot") {
		dsq->continuity.setFlag(FLAG_COLLECTIBLE_INHOME_MITHALASPOT, 1);
	} else if (aCollectible == "big_seed") {
		dsq->continuity.setFlag(FLAG_COLLECTIBLE_INHOME_NAIJACAVE, 1);
	} else if (aCollectible == "seed_bag") {
		dsq->continuity.setFlag(FLAG_COLLECTIBLE_INHOME_SEEDBAG, 1);
	} else if (aCollectible == "skull") {
		dsq->continuity.setFlag(FLAG_COLLECTIBLE_INHOME_SKULL, 1);
	} else if (aCollectible == "jelly_beacon") {
		dsq->continuity.setFlag(FLAG_COLLECTIBLE_INHOME_SONGCAVE, 1);
	} else if (aCollectible == "spore_seed") {
		dsq->continuity.setFlag(FLAG_COLLECTIBLE_INHOME_SPORESEED, 1);
	} else if (aCollectible == "gold_star") {
		dsq->continuity.setFlag(FLAG_COLLECTIBLE_INHOME_STARFISH, 1);
	} else if (aCollectible == "stone_head") {
		dsq->continuity.setFlag(FLAG_COLLECTIBLE_INHOME_STONEHEAD, 1);
	} else if (aCollectible == "sun_key") {
		dsq->continuity.setFlag(FLAG_COLLECTIBLE_INHOME_SUNKEY, 1);
	} else if (aCollectible == "trident_head") {
		dsq->continuity.setFlag(FLAG_COLLECTIBLE_INHOME_TRIDENTHEAD, 1);
	} else if (aCollectible == "turtle_egg") {
		dsq->continuity.setFlag(FLAG_COLLECTIBLE_INHOME_TURTLEEGG, 1);
	} else if (aCollectible == "upsidedown_seed") {
		dsq->continuity.setFlag(FLAG_COLLECTIBLE_INHOME_UPSIDEDOWNSEED, 1);
	} else if (aCollectible == "walker") {
		dsq->continuity.setFlag(FLAG_COLLECTIBLE_INHOME_WALKERBABY, 1);
	} else if (aCollectible == "crab_costume") {
		dsq->continuity.setFlag(FLAG_COLLECTIBLE_INHOME_CRABCOSTUME, 1);
	} else if (aCollectible == "jelly_costume") {
		dsq->continuity.setFlag(FLAG_COLLECTIBLE_INHOME_JELLYCOSTUME, 1);
	} else if (aCollectible == "mithalan_costume") {
		dsq->continuity.setFlag(FLAG_COLLECTIBLE_INHOME_MITHALANCOSTUME, 1);
	} else if (aCollectible == "mutant_costume") {
		dsq->continuity.setFlag(FLAG_COLLECTIBLE_INHOME_MUTANTCOSTUME, 1);
	} else if (aCollectible == "seahorse_costume") {
		dsq->continuity.setFlag(FLAG_COLLECTIBLE_INHOME_SEAHORSECOSTUME, 1);
	} else if (aCollectible == "teen_costume") {
		dsq->continuity.setFlag(FLAG_COLLECTIBLE_INHOME_TEENCOSTUME, 1);
	} else if (aCollectible == "urchin_costume") {
		dsq->continuity.setFlag(FLAG_COLLECTIBLE_INHOME_URCHINCOSTUME, 1);
	} else if (aCollectible == "blaster") {
		dsq->continuity.setFlag(FLAG_COLLECTIBLE_INHOME_BLASTER, 1);
	} else if (aCollectible == "nautilus") {
		dsq->continuity.setFlag(FLAG_COLLECTIBLE_INHOME_NAUTILUS, 1);
	} else if (aCollectible == "dumbo") {
		dsq->continuity.setFlag(FLAG_COLLECTIBLE_INHOME_DUMBO, 1);
	} else if (aCollectible == "piranha") {
		dsq->continuity.setFlag(FLAG_COLLECTIBLE_INHOME_PIRANHA, 1);
	} else {
		assert(false && "The collectible is not valid!");
	}
}

/**
 * Get a new item to activate in the local game
 * @param aItem The item to activate
 * @param aCount The number of element to receive
 */
void Randomizer::receivingItem(const std::string& aItem, int aCount) {
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
 * @param aCheckId The Id of the check to retreive
 * @return A pointer to the check_t object
 */
check_t *Randomizer::getCheck(const std::string& aCheckId)
{
	check_t *result = nullptr;
    int lCheckIndex = getCheckIndex(aCheckId);
    if (lCheckIndex != -1) {
        result = getCheckByIndex(lCheckIndex);
    }
	return result;
}

/**
 * Retreive the index of a check
 * @param aCheckId The Id of the check to retreive
 * @return The index of the check in the CHECKS vector
 */
int Randomizer::getCheckIndex(const std::string& aCheckId)
{
    int result = -1;
    for (int i = 0; i < checks->size() && result == -1; i = i + 1) {
        if (getCheckByIndex(i)->id == aCheckId) {
            result = i;
        }
    }
    return result;
}

/**
 * Retreive a check structure from an item Id
 * @param aItem The item Id of the check to retreive
 * @return A pointer to the check_t object
 */
check_t *Randomizer::getCheckByItem(const std::string& aItem)
{
	check_t *result = nullptr;
	for (int i = 0; i < checks->size() && !result; i = i + 1) {
        check_t * lCheck = getCheckByIndex(i);
		if (lCheck->item == aItem) {
			result = lCheck;
		}
	}
	return result;
}

/**
 * Spawn a number of recipe dish at a position in space, at a certain time.
 * @param aRecipe The recipe to spawn
 * @param aPosition At what position to spawn the ingredients
 * @param aTimes The number of ingredients to spawn
 * @param aOut Is the entity should spawn now.
 * @return The (last) spawned ingredient;
 */
Entity *Randomizer::spawnRecipe(Recipe * aRecipe, const Vector &aPosition, int aTimes, int aOut) {
    Entity *lResult = nullptr;
    if (aRecipe && aRecipe->isKnown()) {
        lResult = dsq->game->spawnIngredient(aRecipe->result, aPosition, aTimes, aOut);
    } else {
        if (aRecipe->result == "PoisonLoaf") {
            lResult = dsq->game->spawnIngredient("rottenmeat", aPosition,
                                                 aTimes * 2, aOut);
        } else {
            for (int j = 0; j < aRecipe->names.size(); j = j + 1) {
                std::string lName = aRecipe->names.at(j).name;
                transform(lName.begin(), lName.end(), lName.begin(), ::tolower);
                int lIndex = -1;
                for (int i = 0; lIndex < 0 && i < ingredients->size(); i = i + 1) {
                    if (ingredients->at(i).name == lName) {
                        lIndex = i;
                    }
                }
                if (lIndex >= 0) {
                    int lRandomizedIndex = -1;
                    lRandomizedIndex = ingredientReplacement->at(lIndex);
                    lResult = spawnIngredient(ingredients->at(lRandomizedIndex).name,
                                              aPosition, aTimes * aRecipe->names.at(j).amount, aOut);
                } else {
                    lResult = spawnIngredient(lName, aPosition,
                                              aTimes * aRecipe->names.at(j).amount, aOut);
                }
            }
            for (int j = 0; j < aRecipe->types.size(); j = j + 1) {
                std::string lName;
                if (aRecipe->types.at(j).type == IT_MEAT) { lName = "fishmeat"; }
                else if (aRecipe->types.at(j).type == IT_EGG) { lName = "smallegg"; }
                else if (aRecipe->types.at(j).type == IT_OIL) { lName = "fishoil"; }
                else if (aRecipe->types.at(j).type == IT_EGG) { lName = "smallegg"; }
                else if (aRecipe->types.at(j).type == IT_BERRY) { lName = "redberry"; }
                else if (aRecipe->types.at(j).type == IT_MUSHROOM) { lName = "mushroom"; }
                else if (aRecipe->types.at(j).type == IT_BULB) { lName = "plantbulb"; }
                else if (aRecipe->types.at(j).type == IT_TENTACLE) { lName = "smalltentacle"; }
                else if (aRecipe->types.at(j).type == IT_ICECHUNK) { lName = "icechunk"; }
                else if (aRecipe->types.at(j).type == IT_PART) { lName = "smalleye"; }
                else if (aRecipe->types.at(j).type == IT_SOUP) { lName = "hotsoup"; }
                else if (aRecipe->types.at(j).type == IT_CAKE) { lName = "seacake"; }
                else if (aRecipe->types.at(j).type == IT_ICECREAM) { lName = "icecream"; }
                else if (aRecipe->types.at(j).type == IT_LOAF) { lName = "sealoaf"; }
                else if (aRecipe->types.at(j).type == IT_PEROGI) { lName = "perogi"; }
                else if (aRecipe->types.at(j).type == IT_POULTICE) { lName = "leafpoultice"; }
                else if (aRecipe->types.at(j).type == IT_ROLL) { lName = "handroll"; }
                else { lName = "plantleaf"; }
                lResult = spawnIngredient(lName, aPosition,
                                          aTimes * aRecipe->names.at(j).amount, aOut);
            }
        }
    }
}

/**
 * Spawn a number of ingredient at a position in space, at a certain time.
 * @param aIngredient The ingredient to spawn
 * @param aPosition At what position to spawn the ingredient
 * @param aTimes The number of ingredient to spawn
 * @param aOut Is the entity should spawn now.
 * @return The (last) spawned ingredient;
 */
Entity *Randomizer::spawnIngredient(const std::string &aIngredient, const Vector &aPosition, int aTimes, int aOut) {
    Entity *lResult = nullptr;
    std::string lIngredientName = aIngredient;
    if (nocasecmp(lIngredientName, "poultice")==0)
        lIngredientName = "leafpoultice";
    transform(lIngredientName.begin(), lIngredientName.end(), lIngredientName.begin(), ::tolower);
    int lIndex = -1;
    for (int i = 0; lIndex < 0 && i < ingredients->size(); i = i + 1) {
        if (ingredients->at(i).name == lIngredientName) {
            lIndex = i;
        }
    }
    if (lIndex == -1) {
        std::vector<Recipe> lRecipes = dsq->continuity.recipes;
        Recipe * lRecipe = nullptr;
        int lIndexRecipe = -1;
        for (int i = 0; lIndexRecipe < 0 && i < lRecipes.size(); i = i + 1) {
            std::string lRecipeName = lRecipes.at(i).result;
            transform(lRecipeName.begin(), lRecipeName.end(), lRecipeName.begin(), ::tolower);
            if (lRecipeName == lIngredientName) {
                lRecipe = &lRecipes.at(i);
            }
        }
        lResult = spawnRecipe(lRecipe, aPosition, aTimes, aOut);
    } else {
        int lRandomizedIndex = -1;
        lRandomizedIndex = ingredientReplacement->at(lIndex);
        lResult = dsq->game->spawnIngredient(ingredients->at(lRandomizedIndex).name,
                                             aPosition, aTimes, aOut);
    }
    return lResult;
}

/**
 * Spawn a recipe desi from an entity.
 * @param entity The entity that spawn the recipe dish
 * @param recipe The recipe to spawn
 */
void Randomizer::spawnRecipeFromEntity(Entity *aEntity, Recipe * aRecipe) {
    IngredientData * lData = dsq->continuity.getIngredientDataByName(aRecipe->result);
    if (aRecipe && aRecipe->isKnown()) {
        dsq->game->spawnIngredientFromEntity(aEntity, lData);
    } else {
        if (aRecipe->result == "PoisonLoaf") {
            lData = dsq->continuity.getIngredientDataByName("rottenmeat");
            dsq->game->spawnIngredientFromEntity(aEntity, lData);
        } else {
            for (int j = 0; j < aRecipe->names.size(); j = j + 1) {
                std::string lName = aRecipe->names.at(j).name;
                transform(lName.begin(), lName.end(), lName.begin(), ::tolower);
                int lIndex = -1;
                for (int i = 0; lIndex < 0 && i < ingredients->size(); i = i + 1) {
                    if (ingredients->at(i).name == lName) {
                        lIndex = i;
                    }
                }
                if (lIndex >= 0) {
                    int lRandomizedIndex = -1;
                    lRandomizedIndex = ingredientReplacement->at(lIndex);
                    lData = dsq->continuity.getIngredientDataByName(ingredients->at(lRandomizedIndex).name);
                    spawnIngredientFromEntity(aEntity, lData);
                } else {
                    lData = dsq->continuity.getIngredientDataByName(lName);
                    spawnIngredientFromEntity(aEntity, lData);
                }
            }
            for (int j = 0; j < aRecipe->types.size(); j = j + 1) {
                std::string lName;
                if (aRecipe->types.at(j).type == IT_MEAT) { lName = "fishmeat"; }
                else if (aRecipe->types.at(j).type == IT_EGG) { lName = "smallegg"; }
                else if (aRecipe->types.at(j).type == IT_OIL) { lName = "fishoil"; }
                else if (aRecipe->types.at(j).type == IT_EGG) { lName = "smallegg"; }
                else if (aRecipe->types.at(j).type == IT_BERRY) { lName = "redberry"; }
                else if (aRecipe->types.at(j).type == IT_MUSHROOM) { lName = "mushroom"; }
                else if (aRecipe->types.at(j).type == IT_BULB) { lName = "plantbulb"; }
                else if (aRecipe->types.at(j).type == IT_TENTACLE) { lName = "smalltentacle"; }
                else if (aRecipe->types.at(j).type == IT_ICECHUNK) { lName = "icechunk"; }
                else if (aRecipe->types.at(j).type == IT_PART) { lName = "smalleye"; }
                else if (aRecipe->types.at(j).type == IT_SOUP) { lName = "hotsoup"; }
                else if (aRecipe->types.at(j).type == IT_CAKE) { lName = "seacake"; }
                else if (aRecipe->types.at(j).type == IT_ICECREAM) { lName = "icecream"; }
                else if (aRecipe->types.at(j).type == IT_LOAF) { lName = "sealoaf"; }
                else if (aRecipe->types.at(j).type == IT_PEROGI) { lName = "perogi"; }
                else if (aRecipe->types.at(j).type == IT_POULTICE) { lName = "leafpoultice"; }
                else if (aRecipe->types.at(j).type == IT_ROLL) { lName = "handroll"; }
                else { lName = "plantleaf"; }
                lData = dsq->continuity.getIngredientDataByName(lName);
                spawnIngredientFromEntity(aEntity, lData);
            }
        }
    }
}

/**
 * Spawn a ingredient from an entity.
 * @param aEntity The entity that spawn the ingredient
 * @param aIngredientData The ingredient to spawn
 */
void Randomizer::spawnIngredientFromEntity(Entity *aEntity, IngredientData *aIngredientData)
{
    std::string lIngredientName = aIngredientData->name;
    transform(lIngredientName.begin(), lIngredientName.end(), lIngredientName.begin(), ::tolower);
    int lIndex = -1;
    for (int i = 0; lIndex < 0 && i < ingredients->size(); i = i + 1) {
        if (ingredients->at(i).name == lIngredientName) {
            lIndex = i;
        }
    }
    if (lIndex == -1) {
        std::vector<Recipe> lRecipes = dsq->continuity.recipes;
        Recipe * lRecipe = nullptr;
        int lIndexRecipe = -1;
        for (int i = 0; lIndexRecipe < 0 && i < lRecipes.size(); i = i + 1) {
            std::string lRecipeName = lRecipes.at(i).result;
            transform(lRecipeName.begin(), lRecipeName.end(), lRecipeName.begin(), ::tolower);
            if (lRecipeName == lIngredientName) {
                lRecipe = &lRecipes.at(i);
            }
        }
        spawnRecipeFromEntity(aEntity, lRecipe);
    } else {
        dsq->game->spawnIngredientFromEntity(aEntity, getRandomizedIngredientData(aIngredientData));
    }

}

/**
 * Randomize the IngredientData using ingredient in continuity.
 * @param aData The IngredientData to randomize
 * @return The randomized IngredientData.
 */
IngredientData *Randomizer::getRandomizedIngredientData(IngredientData* aData)
{
	IngredientData* lRandomizedData = aData;
	if (dsq) {
        int lIndex = -1;
        int lRandomizedIndex = -1;
        for (int i = 0; lIndex < 0 && i < ingredients->size(); i = i + 1) {
            if (ingredients->at(i).name == aData->name) {
                lIndex = i;
            }
        }
		assert((lIndex != -1) && "The ingredient is not valid");
		lRandomizedIndex = ingredientReplacement->at(lIndex);
		lRandomizedData = dsq->continuity.getIngredientDataByName(ingredients->at(lRandomizedIndex).name);
		assert(lRandomizedData && "The ingredient is not valid");
	}
	return lRandomizedData;
}

/**
 * Destructor of the object
 */
Randomizer::~Randomizer() {
    delete(ingredientReplacement);
}

/**
 * True if an error occured at initialization. False means every thing is fine
 *
 * @return True if an error occured at initialization. False if not.
 */
bool Randomizer::hasError() const{
    return error;
}

/**
 * The the error message when hasError is True
 * @return The error message
 */
std::string Randomizer::getErrorMessage(){
    return errorMessage;
}
/**
 * Put hasError to True and assign a message to getErrorMessage.
 * @param message The message to assign to getErrorMessage
 */
void Randomizer::setError(std::string message) {
    errorMessage = std::move(message);
    error = true;
}


/**
 * Retreive the check at a certain index
 * @param index The index of the check to retreive
 * @return The check
 */
check_t *Randomizer::getCheckByIndex(int aIndex) {
    check_t * lResult = nullptr;
    if (aIndex >= 0 && aIndex < checks->size()) {
        lResult = &(checks->at(aIndex));
    }
    return lResult;
}


