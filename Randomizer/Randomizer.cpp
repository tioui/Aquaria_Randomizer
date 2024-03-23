/**
 * @author      : Louis Marchand (prog@tioui.com)
 * @created     : mercredi jan 10, 2024 16:08:04 EST
 * @license     : MIT
 * Class that encapsulate every randomization functionalities
 *
 * Todo: Add the Urn in the first big room of the cathedral right part
 */

#include "../Aquaria/Game.h"
#include "Randomizer.h"
#include <cassert>
#include <utility>
#include <vector>
#include "apclient.hpp"
#include "../Aquaria/Avatar.h"

/**
 * Constructor for the Randomizer
 */
Randomizer::Randomizer() {
	ingredientReplacement = new std::vector<int>();
    error = false;
    inGame = false;
    errorMessage = "";
    checks = new std::vector<check_t>();
    ingredients = new std::vector<ingredient_t>();
    collectibles = new std::vector<collectible_t>();
    initialiseChecks();
    initialiseIngredients();
    initialiseCollectibles();
}

/**
 * Initialize the ingredients vector
 */
void Randomizer::initialiseIngredients() {
    ingredients->push_back({"PlantLeaf", IT_LEAF});
    ingredients->push_back({"TurtleMeat", IT_MEAT});
    ingredients->push_back({"SwordfishSteak", IT_MEAT});
    ingredients->push_back({"CrabMeat", IT_MEAT});
    ingredients->push_back({"FishMeat", IT_MEAT});
    ingredients->push_back({"RubberyMeat", IT_MEAT});
    ingredients->push_back({"SpicyMeat", IT_MEAT});
    ingredients->push_back({"RottenMeat", IT_MEAT});
    ingredients->push_back({"FishOil", IT_OIL});
    ingredients->push_back({"JellyOil", IT_OIL});
    ingredients->push_back({"EelOil", IT_OIL});
    ingredients->push_back({"SmallBone", IT_BONE});
    ingredients->push_back({"SmallEgg", IT_EGG});
    ingredients->push_back({"SmallEgg", IT_EGG});
    ingredients->push_back({"GlowingEgg", IT_EGG});
    ingredients->push_back({"SpiderEgg", IT_EGG});
    ingredients->push_back({"SmallEye", IT_PART});
    ingredients->push_back({"SharkFin", IT_PART});
    ingredients->push_back({"SmallTentacle", IT_TENTACLE});
    ingredients->push_back({"RedBerry", IT_BERRY});
    ingredients->push_back({"PlantBulb", IT_BULB});
    ingredients->push_back({"Mushroom", IT_MUSHROOM});
    ingredients->push_back({"RainbowMushroom", IT_MUSHROOM});
    ingredients->push_back({"IceChunk", IT_ICECHUNK});
    ingredients->push_back({"SpecialBulb", IT_BULB});
    ingredients->push_back({"RedBulb", IT_BULB});
    ingredients->push_back({"RukhEgg", IT_EGG});
    ingredients->push_back({"HotSoup", IT_SOUP});
    ingredients->push_back({"HeartySoup", IT_SOUP});
    ingredients->push_back({"DivineSoup", IT_SOUP});
    ingredients->push_back({"LongLifeSoup", IT_SOUP});
    ingredients->push_back({"SharkFinSoup", IT_SOUP});
    ingredients->push_back({"SpicySoup", IT_SOUP});
    ingredients->push_back({"ColdSoup", IT_SOUP});
    ingredients->push_back({"RainbowSoup", IT_SOUP});
    ingredients->push_back({"ColdBorscht", IT_SOUP});
    ingredients->push_back({"HotBorscht", IT_SOUP});
    ingredients->push_back({"TurtleSoup", IT_SOUP});
    ingredients->push_back({"PoisonSoup", IT_SOUP});
    ingredients->push_back({"HeartySoup", IT_SOUP});
    ingredients->push_back({"MagicSoup", IT_SOUP});
    ingredients->push_back({"RoyalSoup", IT_SOUP});
    ingredients->push_back({"VeggieSoup", IT_SOUP});
    ingredients->push_back({"SeaLoaf", IT_LOAF});
    ingredients->push_back({"ButterySeaLoaf", IT_LOAF});
    ingredients->push_back({"RottenLoaf", IT_LOAF});
    ingredients->push_back({"VedhaSeaCrisp", IT_LOAF});
    ingredients->push_back({"PoisonLoaf", IT_LOAF});
    ingredients->push_back({"LoafOfLife", IT_LOAF});
    ingredients->push_back({"SeaCake", IT_CAKE});
    ingredients->push_back({"TastyCake", IT_CAKE});
    ingredients->push_back({"VeggieCake", IT_CAKE});
    ingredients->push_back({"CrabCake", IT_CAKE});
    ingredients->push_back({"LegendaryCake", IT_CAKE});
    ingredients->push_back({"RottenCake", IT_CAKE});
    ingredients->push_back({"SwampCake", IT_CAKE});
    ingredients->push_back({"ToughCake", IT_CAKE});
    ingredients->push_back({"SpecialCake", IT_CAKE});
    ingredients->push_back({"HealingPoultice", IT_POULTICE});
    ingredients->push_back({"LeafPoultice", IT_POULTICE});
    ingredients->push_back({"ArcanePoultice", IT_POULTICE});
    ingredients->push_back({"SightPoultice", IT_POULTICE});
    ingredients->push_back({"LeechingPoultice", IT_POULTICE});
    ingredients->push_back({"Vedha'sCure-All", IT_POULTICE});
    ingredients->push_back({"DumboIceCream", IT_ICECREAM});
    ingredients->push_back({"IceCream", IT_ICECREAM});
    ingredients->push_back({"VeggieIceCream", IT_ICECREAM});
    ingredients->push_back({"BerryIceCream", IT_ICECREAM});
    ingredients->push_back({"HandRoll", IT_ROLL});
    ingredients->push_back({"TastyRoll", IT_ROLL});
    ingredients->push_back({"SpiderRoll", IT_ROLL});
    ingredients->push_back({"SpicyRoll", IT_ROLL});
    ingredients->push_back({"VolcanoRoll", IT_ROLL});
    ingredients->push_back({"LeadershipRoll", IT_ROLL});
    ingredients->push_back({"Perogi", IT_PEROGI});
    ingredients->push_back({"PlumpPerogi", IT_PEROGI});
    ingredients->push_back({"Zuuna'sPerogi", IT_PEROGI});
}

/**
 * Initialize every Checks
 */
void Randomizer::initialiseChecks(){
    checks->push_back({1101, "bulb_turtlecave","ingredient_leafpoultice",3, "Leaf poultice"});
    checks->push_back({1102, "bulb_openwater_tl_1","ingredient_handroll",1, "Hand roll"});
    checks->push_back({1103, "bulb_openwater_tl_2","ingredient_veggiesoup",1, "Veggie soup"});
    checks->push_back({1104, "bulb_openwater_tl_3","ingredient_butterysealoaf",1, "Buttery sea loaf"});
    checks->push_back({1105, "bulb_openwater_tr_1","ingredient_healingpoultice",1, "Healing poultice"});
    checks->push_back({1106, "bulb_openwater_tr_2","ingredient_sealoaf",2, "Sea loaf"});
    checks->push_back({1107, "bulb_openwater_tr_3","ingredient_spicyroll",1, "Spicy roll"});
    checks->push_back({1108, "bulb_openwater_tr_4","ingredient_spicymeat",2, "Spicy meat"});
    checks->push_back({1109, "bulb_openwater_tr_5","ingredient_crabcake",1, "Crab cake"});
    checks->push_back({1110, "bulb_openwater_tr_6","ingredient_spicyroll",1, "Spicy roll"});
    checks->push_back({1111, "bulb_openwater_bl_1","ingredient_leadershiproll",2, "Leadership roll"});
    checks->push_back({1112, "bulb_openwater_bl_2","ingredient_healingpoultice",2, "Healing poultice"});
    checks->push_back({1113, "bulb_skeleton_path_1","ingredient_tastycake",1, "Tasty cake"});
    checks->push_back({1114, "bulb_skeleton_path_2","ingredient_perogi",1, "Perogi"});
    checks->push_back({1115, "bulb_arnassi_1","ingredient_tastyroll",1, "Tasty roll"});
    checks->push_back({1116, "bulb_arnassi_2","ingredient_specialbulb",1, "Special bulb"});
    checks->push_back({1117, "bulb_arnassi_3","ingredient_specialcake",1, "Special cake"});
    checks->push_back({1118, "bulb_sunworm_1","ingredient_plantleaf",3, "Plant leaf"});
    checks->push_back({1119, "bulb_sunworm_2","ingredient_turtlesoup",1, "Turtle soup"});
    checks->push_back({1120, "bulb_sunworm_3","ingredient_specialcake",1, "Special cake"});
    checks->push_back({1121, "bulb_sunworm_4","ingredient_specialbulb",1, "Special bulb"});
    checks->push_back({1122, "bulb_tutorial_1","ingredient_handroll",1, "Hand roll"});
    checks->push_back({1123, "bulb_tutorial_2","ingredient_hotsoup",1, "Hot soup"});
    checks->push_back({1124, "bulb_tutorial_3","ingredient_heartysoup",1, "Hearty soup"});
    checks->push_back({1125, "bulb_abyss_l_1","ingredient_coldborscht",1, "Cold borscht"});
    checks->push_back({1126, "bulb_abyss_l_2","ingredient_healingpoultice",2, "Healing poultice"});
    checks->push_back({1127, "bulb_abyss_l_3","ingredient_sightpoultice",1, "Sight poultice"});
    checks->push_back({1128, "bulb_energy_temple_1_1","ingredient_leafpoultice",1, "Leaf poultice"});
    checks->push_back({1129, "bulb_energy_temple_2_1","ingredient_spicyroll",1, "Spicy roll"});
    checks->push_back({1130, "bulb_energy_temple_3_1","ingredient_plantleaf",2, "Plant leaf"});
    checks->push_back({1131, "bulb_mithalas_city_01","ingredient_spicyroll",1, "Spicy roll"});
    checks->push_back({1132, "bulb_mithalas_city_02","ingredient_spicymeat",2, "Spicy meat"});
    checks->push_back({1133, "bulb_mithalas_city_03","ingredient_vedhaseacrisp",1, "Vedha sea crisp"});
    checks->push_back({1134, "bulb_mithalas_city_04","ingredient_heartysoup",1, "Hearty soup"});
    checks->push_back({1135, "bulb_mithalas_city_05","ingredient_healingpoultice",1, "Healing poultice"});
    checks->push_back({1136, "bulb_mithalas_city_06","ingredient_vedhaseacrisp",1, "Vedha sea crisp"});
    checks->push_back({1137, "bulb_mithalas_city_07","ingredient_rottenloaf",8, "Rotten loaf"});
    checks->push_back({1138, "bulb_mithalas_city_08","ingredient_rottenmeat",8, "Rotten meat"});
    checks->push_back({1139, "bulb_mithalas_city_09","ingredient_smalltentacle",2, "Small tentacle"});
    checks->push_back({1140, "bulb_mithalas_city_10","ingredient_seacake",1, "Sea cake"});
    checks->push_back({1141, "bulb_mithalas_city_11","ingredient_smallbone",3, "Small bone"});
    checks->push_back({1142, "bulb_mithalas_city_12","ingredient_handroll",1, "Hand roll"});
    checks->push_back({1143, "bulb_cathedral_l_2","ingredient_heartysoup",1, "Hearty soup"});
    checks->push_back({1144, "bulb_boilerroom_1","ingredient_spicyroll",1, "Spicy roll"});
    checks->push_back({1145, "bulb_forest_tl_1","ingredient_seacake",1, "Sea cake"});
    checks->push_back({1146, "bulb_forest_tl_2","ingredient_spicyroll",1, "Spicy roll"});
    checks->push_back({1147, "bulb_forest_tl_3","ingredient_leechingpoultice",1, "Leeching poultice"});
    checks->push_back({1148, "bulb_forest_tl_4","ingredient_redbulb",2, "Red bulb"});
    checks->push_back({1149, "bulb_forest_tr_1","ingredient_spiderroll",1, "Spider roll"});
    checks->push_back({1150, "bulb_forest_tr_2","ingredient_veggiecake",1, "Veggie cake"});
    checks->push_back({1151, "bulb_forest_tr_3","ingredient_swampcake",1, "Swamp cake"});
    checks->push_back({1152, "bulb_forest_tr_4","ingredient_sharkfinsoup",1, "Shark fin soup"});
    checks->push_back({1153, "bulb_forest_tr_5","ingredient_healingpoultice",1, "Healing poultice"});
    checks->push_back({1154, "bulb_forest_tr_6","ingredient_redbulb",2, "Red bulb"});
    checks->push_back({1155, "bulb_forest_bl_1","ingredient_spiderroll",1, "Spider roll"});
    checks->push_back({1156, "bulb_forest_boss_room_1","ingredient_handroll",1, "Hand roll"});
    checks->push_back({1157, "bulb_forest_sprite_cave_1","ingredient_leechingpoultice",1, "Leeching poultice"});
    checks->push_back({1158, "bulb_forest_sprite_cave_2","ingredient_veggiesoup",1, "Veggie soup"});
    checks->push_back({1159, "bulb_home_water_1","ingredient_smallegg",2, "Small egg"});
    checks->push_back({1160, "bulb_home_water_2","ingredient_leafpoultice",1, "Leaf poultice"});
    checks->push_back({1161, "bulb_home_water_3","ingredient_leafpoultice",1, "Leaf poultice"});
    checks->push_back({1162, "bulb_home_water_4","ingredient_plantleaf",3, "Plant leaf"});
    checks->push_back({1163, "bulb_home_water_5","ingredient_redbulb",2, "Red bulb"});
    checks->push_back({1164, "bulb_home_water_6","ingredient_hotsoup",1, "Hot soup"});
    checks->push_back({1165, "bulb_home_water_7","ingredient_fishmeat",2, "Fish meat"});
    checks->push_back({1166, "bulb_home_water_8","ingredient_seacake",1, "Sea cake"});
    checks->push_back({1167, "bulb_final_l_1","ingredient_arcanepoultice",1, "Arcane poultice"});
    checks->push_back({1168, "bulb_final_l_2","ingredient_divinesoup",1, "Divine soup"});
    checks->push_back({1169, "bulb_final_l_3","ingredient_spicyroll",1, "Spicy roll"});
    checks->push_back({1170, "bulb_final_l_4","ingredient_volcanoroll",1, "Volcano roll"});
    checks->push_back({1171, "bulb_final_l_5","ingredient_arcanepoultice",1, "Arcane poultice"});
    checks->push_back({1172, "bulb_song_cave_1","ingredient_specialbulb",1, "Special bulb"});
    checks->push_back({1173, "bulb_song_cave_2","ingredient_handroll",1, "Hand roll"});
    checks->push_back({1174, "bulb_song_cave_3","ingredient_eeloil",2, "Eel oil"});
    checks->push_back({1175, "bulb_song_cave_4","ingredient_leafpoultice",1, "Leaf poultice"});
    checks->push_back({1176, "bulb_song_cave_5","ingredient_hotsoup",1, "Hot soup"});
    checks->push_back({1177, "bulb_veil_tl_1","ingredient_spicysoup",1, "Spicy soup"});
    checks->push_back({1178, "bulb_veil_tl_2","ingredient_longlifesoup",1, "Long life soup"});
    checks->push_back({1179, "bulb_veil_tl_3","ingredient_hotsoup",2, "Hot soup"});
    checks->push_back({1180, "bulb_veil_tr_1","ingredient_sharkfinsoup",1, "Shark fin soup"});
    checks->push_back({1181, "bulb_veil_tr_2","ingredient_legendarycake",1, "Legendary cake"});
    checks->push_back({1182, "bulb_veil_b_1","ingredient_swampcake",1, "Swamp cake"});
    checks->push_back({1183, "bulb_veil_b_2","ingredient_swampcake",1, "Swamp cake"});
    checks->push_back({1184, "bulb_ice_cave_1","ingredient_icecream",1, "Ice cream"});
    checks->push_back({1185, "bulb_ice_cave_2","ingredient_berryicecream",1, "Berry ice cream"});
    checks->push_back({1186, "bulb_ice_cave_3","ingredient_veggieicecream",1, "Veggie ice cream"});
    checks->push_back({1187, "bulb_ice_cave_4","ingredient_dumboicecream",1, "Dumbo ice cream"});
    checks->push_back({1188, "bulb_ice_cave_5","ingredient_icecream",1, "Ice cream"});
    checks->push_back({1189, "bulb_king_jellyfish_cave_1","ingredient_specialbulb",1, "Special bulb"});
    checks->push_back({1190, "bulb_bubble_cave_1","ingredient_coldsoup",1, "Cold soup"});
    checks->push_back({1191, "bulb_bubble_cave_2","ingredient_coldborscht",1, "Cold borscht"});
    checks->push_back({1192, "bulb_sun_temple_1","ingredient_glowingegg",2, "Glowing egg"});
    checks->push_back({1193, "bulb_sun_temple_2","ingredient_magicsoup",1, "Magic soup"});
    checks->push_back({1194, "bulb_sun_temple_3","ingredient_royalsoup",1, "Royal soup"});
    checks->push_back({1195, "bulb_sun_temple_4","ingredient_leadershiproll",1, "Leadership roll"});
    checks->push_back({1196, "bulb_sun_temple_5","ingredient_turtlesoup",1, "Turtle soup"});
    checks->push_back({1197, "bulb_sun_temple_6","ingredient_heartysoup",1, "Hearty soup"});
    checks->push_back({1198, "bulb_final_c_1","ingredient_Zuuna'sperogi",1, "Zuuna's perogi"});
    checks->push_back({1199, "bulb_final_r_1","ingredient_plumpperogi",1, "Plump perogi"});
    checks->push_back({1200, "bulb_final_r_2","ingredient_arcanepoultice",1, "Arcane poultice"});
    checks->push_back({1201, "bulb_final_r_3","ingredient_arcanepoultice",1, "Arcane poultice"});
    checks->push_back({1202, "bulb_final_b_1","ingredient_longlifesoup",1, "Long life soup"});
    checks->push_back({1203, "bulb_final_b_2","ingredient_spicyroll",1, "Spicy roll"});
    checks->push_back({1204, "bulb_final_boss_1","ingredient_Vedha'sCure-All",1, "Vedha's Cure-All"});
    checks->push_back({1205, "bulb_final_boss_2","ingredient_loafoflife",1, "Loaf of life"});
    checks->push_back({1206, "bulb_final_boss_3","ingredient_specialbulb",1, "Special bulb"});
    checks->push_back({1207, "bulb_final_boss_4","ingredient_dumboicecream",1, "Dumbo ice cream"});
    checks->push_back({1208, "bulb_starting_cave_1","ingredient_fishoil",1, "Fish oil"});
    checks->push_back({1209, "bulb_starting_cave_2","ingredient_smallegg",1, "Small egg"});
    checks->push_back({1210, "bulb_abyss_r_1","ingredient_dumboicecream",1, "Dumbo ice cream"});
    checks->push_back({1211, "bulb_abyss_r_2","ingredient_tastyroll",1, "Tasty roll"});
    checks->push_back({1212, "bulb_abyss_r_3","ingredient_healingpoultice",1, "Healing poultice"});
    checks->push_back({1213, "bulb_abyss_r_4","ingredient_hotborscht",1, "Hot borscht"});
    checks->push_back({1214, "bulb_cathedral_under_ground_1","ingredient_arcanepoultice",1, "Arcane poultice"});
    checks->push_back({1215, "bulb_cathedral_under_ground_2","ingredient_plantleaf",1, "Plant leaf"});
    checks->push_back({1216, "bulb_cathedral_under_ground_3","ingredient_arcanepoultice",1, "Arcane poultice"});
    checks->push_back({1217, "bulb_cathedral_under_ground_4","ingredient_redberry",1, "Red berry"});
    checks->push_back({1218, "bulb_cathedral_under_ground_5","ingredient_leafpoultice",1, "Leaf poultice"});
    checks->push_back({1219, "bulb_cathedral_under_ground_6","ingredient_arcanepoultice",1, "Arcane poultice"});
    checks->push_back({1220, "bulb_naija_home_1","ingredient_spicyroll",1, "Spicy roll"});
    checks->push_back({1221, "bulb_naija_home_2","ingredient_heartysoup",1, "Hearty soup"});
    checks->push_back({1222, "bulb_mermog_cave_1","ingredient_leechingpoultice",1, "Leeching poultice"});
    checks->push_back({1223, "bulb_octo_cave_1","ingredient_sightpoultice",1, "Sight poultice"});
    checks->push_back({1224, "urn_mithalas_city_1","ingredient_rottenmeat",2, "Rotten meat"});
    checks->push_back({1225, "urn_mithalas_city_2","ingredient_glowingegg",1, "Glowing egg"});
    checks->push_back({1226, "urn_mithalas_city_3","ingredient_rainbowmushroom",1, "Rainbow mushroom"});
    checks->push_back({1227, "urn_mithalas_city_4","ingredient_rainbowmushroom",1, "Rainbow mushroom"});
    checks->push_back({1228, "urn_mithalas_city_5","ingredient_rainbowmushroom",1, "Rainbow mushroom"});
    checks->push_back({1229, "urn_mithalas_city_6","ingredient_plantleaf",3, "Plant leaf"});
    checks->push_back({1230, "urn_mithalas_city_7","ingredient_spicyroll",1, "Spicy roll"});
    checks->push_back({1231, "urn_cathedral_l_1","ingredient_rainbowmushroom",1, "Rainbow mushroom"});
    checks->push_back({1232, "urn_cathedral_l_2","ingredient_smallbone",2, "Small bone"});
    checks->push_back({1233, "urn_cathedral_l_3","ingredient_rottenmeat",1, "Rotten meat"});
    checks->push_back({1234, "urn_cathedral_l_4","ingredient_fishoil",1, "Fish oil"});
    checks->push_back({1235, "urn_cathedral_l_5","ingredient_rottenmeat",1, "Rotten meat"});
    checks->push_back({1236, "urn_cathedral_l_6","ingredient_rainbowsoup",1, "Rainbow soup"});
    checks->push_back({1237, "urn_cathedral_r_01","ingredient_plantleaf",1, "Plant leaf"});
    checks->push_back({1238, "urn_cathedral_r_02","ingredient_rottencake",1, "Rotten cake"});
    checks->push_back({1239, "urn_cathedral_r_03","ingredient_toughcake",1, "Tough cake"});
    checks->push_back({1240, "urn_cathedral_r_04","ingredient_spicyroll",1, "Spicy roll"});
    checks->push_back({1241, "urn_cathedral_r_05","ingredient_rottenmeat",1, "Rotten meat"});
    checks->push_back({1242, "urn_cathedral_r_06","ingredient_plantleaf",1, "Plant leaf"});
    checks->push_back({1243, "urn_cathedral_r_07","ingredient_leechingpoultice",1, "Leeching poultice"});
    checks->push_back({1244, "urn_cathedral_r_08","ingredient_smallbone",3, "Small bone"});
    checks->push_back({1245, "urn_cathedral_r_09","ingredient_plantleaf",2, "Plant leaf"});
    checks->push_back({1246, "urn_cathedral_r_10","ingredient_rottenmeat",1, "Rotten meat"});
    checks->push_back({1247, "urn_cathedral_r_11","ingredient_poisonloaf",1, "Poison loaf"});
    checks->push_back({1248, "urn_cathedral_r_12","ingredient_poisonsoup",1, "Poison soup"});
    checks->push_back({1249, "urn_openwater_tr_1","ingredient_smallbone",3, "Small bone"});
    checks->push_back({1250, "urn_openwater_tr_2","ingredient_rottenmeat",1, "Rotten meat"});
    checks->push_back({1251, "urn_openwater_tr_3","ingredient_sealoaf",1, "Sea loaf"});
    checks->push_back({1252, "crate_sunkencity_2_1","ingredient_fishoil",3, "Fish oil"});
    checks->push_back({1253, "crate_sunkencity_2_2","ingredient_mushroom",2, "Mushroom"});
    checks->push_back({1254, "crate_sunkencity_2_3","ingredient_spicymeat",2, "Spicy meat"});
    checks->push_back({1255, "crate_sunkencity_1_1","ingredient_seacake",1, "Sea cake"});
    checks->push_back({1256, "crate_sunkencity_1_2","ingredient_plantleaf",3, "Plant leaf"});
    checks->push_back({1257, "beating_simon","upgrade_wok",1, "Wok"});
    checks->push_back({1258, "health_egg_1","upgrade_health_1",1, "Health"});
    checks->push_back({1259, "health_egg_2","upgrade_health_2",1, "Health"});
    checks->push_back({1260, "health_egg_3","upgrade_health_3",1, "Health"});
    checks->push_back({1261, "health_egg_4","upgrade_health_4",1, "Health"});
    checks->push_back({1262, "health_egg_5","upgrade_health_5",1, "Health"});
    checks->push_back({1263, "collect_anemone","collectible_anemone",1, "Anemone"});
    checks->push_back({1264, "collect_energy_temple","collectible_energy_temple",1, "Krotite armor"});
    checks->push_back({1265, "collect_arnassi_statue","collectible_arnassi_statue",1, "Arnassi statue"});
    checks->push_back({1266, "collect_mithalas_banner","collectible_mithalas_banner",1, "Mithalas banner"});
    checks->push_back({1267, "collect_bio_seed","collectible_bio_seed",1, "Glowing seed"});
    checks->push_back({1268, "collect_blackpearl","collectible_blackpearl",1, "Black pearl"});
    checks->push_back({1269, "collect_treasure_chest","collectible_treasure_chest",1, "Odd container"});
    checks->push_back({1270, "collect_energy_boss","collectible_energy_boss",1, "Tooth"});
    checks->push_back({1271, "collect_energy_statue","collectible_energy_statue",1, "Energy statue"});
    checks->push_back({1272, "collect_golden_gear","collectible_golden_gear",1, "Golden gear"});
    checks->push_back({1273, "collect_jelly_plant","collectible_jelly_plant",1, "Jelly plant"});
    checks->push_back({1274, "collect_mithala_doll","collectible_mithala_doll",1, "Mithalas doll"});
    checks->push_back({1275, "collect_mithalas_pot","collectible_mithalas_pot",1, "Mithalas pot"});
    checks->push_back({1276, "collect_big_seed","collectible_big_seed",1, "Big seed"});
    checks->push_back({1277, "collect_seed_bag","collectible_seed_bag",1, "Seed bag"});
    checks->push_back({1278, "collect_skull","collectible_skull",1, "King's Skull"});
    checks->push_back({1279, "collect_jelly_beacon","collectible_jelly_beacon",1, "Jelly beacon"});
    checks->push_back({1280, "collect_spore_seed","collectible_spore_seed",1, "Song plant spore"});
    checks->push_back({1281, "collect_gold_star","collectible_gold_star",1, "Golden starfish"});
    checks->push_back({1282, "collect_stone_head","collectible_stone_head",1, "Stone head"});
    checks->push_back({1283, "collect_sun_key","collectible_sun_key",1, "Sun key"});
    checks->push_back({1284, "collect_trident_head","collectible_trident_head",1, "Trident"});
    checks->push_back({1285, "collect_turtle_egg","collectible_turtle_egg",1, "Turtle egg"});
    checks->push_back({1286, "collect_upsidedown_seed","collectible_upsidedown_seed",1, "Jelly egg"});
    checks->push_back({1287, "collect_walker","collectible_walker",1, "Baby walker"});
    checks->push_back({1288, "collect_crab_costume","collectible_crab_costume",1, "Crab armor"});
    checks->push_back({1289, "collect_jelly_costume","collectible_jelly_costume",1, "Jelly costume"});
    checks->push_back({1290, "collect_mithalan_costume","collectible_mithalan_costume",1, "Mithalan dress"});
    checks->push_back({1291, "collect_mutant_costume","collectible_mutant_costume",1, "Mutant costume"});
    checks->push_back({1292, "collect_seahorse_costume","collectible_seahorse_costume",1, "Arnassi Armor"});
    checks->push_back({1293, "collect_teen_costume","collectible_teen_costume",1, "Girl costume"});
    checks->push_back({1294, "collect_urchin_costume","collectible_urchin_costume",1, "Urchin costume"});
    checks->push_back({1295, "collect_nautilus","collectible_nautilus",1, "Baby nautilus"});
    checks->push_back({1296, "collect_blaster","collectible_blaster",1, "Baby blaster"});
    checks->push_back({1297, "collect_dumbo","collectible_dumbo",1, "Baby dumbo"});
    checks->push_back({1298, "collect_piranha","collectible_piranha",1, "Baby piranha"});
    checks->push_back({1299, "urn_cathedral_r_13","ingredient_leafpoultice",3, "Leaf poultice"});
    checks->push_back({1300, "li_cave","song_li",1, "Li and Li song"});
    checks->push_back({1301, "song_shield_hint","song_shield",1, "Shield song"});
    checks->push_back({1302, "breaking_li_cage","song_dual",1, "Dual Form"});
    checks->push_back({1303, "beating_mithalas","song_beast",1, "Beast Form"});
    checks->push_back({1304, "beating_sun_god","song_sun",1, "Sun Form"});
    checks->push_back({1305, "beating_drunian_god","song_nature",1, "Nature Form"});
    checks->push_back({1306, "beating_energy_statue","song_energy",1, "Energy Form"});
    checks->push_back({1307, "erulian_spirit","song_bind",1, "Bind song"});
    checks->push_back({1308, "fish_cave_puzzle","song_fish",1, "Fish form"});
    checks->push_back({1309, "beating_priests","song_spirit",1, "Spirit form"});
    checks->push_back({1310, "transturtle_veil01","transport_veil01",1, "Transport to The Veil top left area"});
    checks->push_back({1311, "transturtle_veil02","transport_veil02",1, "Transport to The Veil top right area"});
    checks->push_back({1312, "transturtle_openwater03","transport_openwater03",1, "Transport to Open water top right area"});
    checks->push_back({1313, "transturtle_forest04","transport_forest04",1, "Transport to Kelp Forest bottom left area"});
    checks->push_back({1314, "transturtle_mainarea","transport_mainarea",1, "Transport to home water"});
    checks->push_back({1315, "transturtle_abyss03","transport_abyss03",1, "Transport to The Abyss right area"});
    checks->push_back({1316, "transturtle_finalboss","transport_finalboss",1, "Transport to The Creator"});
    checks->push_back({1317, "transturtle_forest05","transport_forest05",1, "Transport to Simon says"});
    checks->push_back({1318, "transturtle_seahorse","transport_seahorse",1, "Transport to Arnassi Ruins right area"});


}


/**
 * Initialize `collectibles`
 */
void Randomizer::initialiseCollectibles() {
    collectibles->push_back({
        FLAG_COLLECTIBLE_ANEMONESEED, "collectible_anemone"});
    collectibles->push_back({FLAG_COLLECTIBLE_ENERGYTEMPLE, "collectible_energy_temple"});
    collectibles->push_back({FLAG_COLLECTIBLE_ARNASSISTATUE, "collectible_arnassi_statue"});
    collectibles->push_back({FLAG_COLLECTIBLE_BANNER, "collectible_mithalas_banner"});
    collectibles->push_back({FLAG_COLLECTIBLE_BIOSEED, "collectible_bio_seed"});
    collectibles->push_back({FLAG_COLLECTIBLE_BLACKPEARL, "collectible_blackpearl"});
    collectibles->push_back({FLAG_COLLECTIBLE_CHEST, "collectible_treasure_chest"});
    collectibles->push_back({FLAG_COLLECTIBLE_ENERGYBOSS, "collectible_energy_boss"});
    collectibles->push_back({FLAG_COLLECTIBLE_ENERGYSTATUE, "collectible_energy_statue"});
    collectibles->push_back({FLAG_COLLECTIBLE_GEAR, "collectible_golden_gear"});
    collectibles->push_back({FLAG_COLLECTIBLE_JELLYPLANT, "collectible_jelly_plant"});
    collectibles->push_back({FLAG_COLLECTIBLE_MITHALADOLL, "collectible_mithala_doll"});
    collectibles->push_back({FLAG_COLLECTIBLE_MITHALASPOT, "collectible_mithalas_pot"});
    collectibles->push_back({FLAG_COLLECTIBLE_NAIJACAVE, "collectible_big_seed"});
    collectibles->push_back({FLAG_COLLECTIBLE_SEEDBAG, "collectible_seed_bag"});
    collectibles->push_back({FLAG_COLLECTIBLE_SKULL, "collectible_skull"});
    collectibles->push_back({FLAG_COLLECTIBLE_SONGCAVE, "collectible_jelly_beacon"});
    collectibles->push_back({FLAG_COLLECTIBLE_SPORESEED, "collectible_spore_seed"});
    collectibles->push_back({FLAG_COLLECTIBLE_STARFISH, "collectible_gold_star"});
    collectibles->push_back({FLAG_COLLECTIBLE_STONEHEAD, "collectible_stone_head"});
    collectibles->push_back({FLAG_COLLECTIBLE_SUNKEY, "collectible_sun_key"});
    collectibles->push_back({FLAG_COLLECTIBLE_TRIDENTHEAD, "collectible_trident_head"});
    collectibles->push_back({FLAG_COLLECTIBLE_TURTLEEGG, "collectible_turtle_egg"});
    collectibles->push_back({FLAG_COLLECTIBLE_UPSIDEDOWNSEED, "collectible_upsidedown_seed"});
    collectibles->push_back({FLAG_COLLECTIBLE_WALKERBABY, "collectible_walker"});
    collectibles->push_back({FLAG_COLLECTIBLE_CRABCOSTUME, "collectible_crab_costume"});
    collectibles->push_back({FLAG_COLLECTIBLE_JELLYCOSTUME, "collectible_jelly_costume"});
    collectibles->push_back({FLAG_COLLECTIBLE_MITHALANCOSTUME, "collectible_mithalan_costume"});
    collectibles->push_back({FLAG_COLLECTIBLE_MUTANTCOSTUME, "collectible_mutant_costume"});
    collectibles->push_back({FLAG_COLLECTIBLE_SEAHORSECOSTUME, "collectible_seahorse_costume"});
    collectibles->push_back({FLAG_COLLECTIBLE_TEENCOSTUME, "collectible_teen_costume"});
    collectibles->push_back({FLAG_COLLECTIBLE_URCHINCOSTUME, "collectible_urchin_costume"});
    collectibles->push_back({FLAG_PET_NAUTILUS, "collectible_nautilus"});
    collectibles->push_back({FLAG_PET_BLASTER, "collectible_blaster"});
    collectibles->push_back({FLAG_PET_DUMBO, "collectible_dumbo"});
    collectibles->push_back({FLAG_PET_PIRANHA, "collectible_piranha"});
}

/**
 * Get a new transport to location
 * @param aCheck The transport item to activate
 */
void Randomizer::receivingTransport(check_t *aCheck) {
    int lAreaStringIndex = 0;
    if (aCheck->flag == 1310) {
        dsq->continuity.setFlag(FLAG_TRANSTURTLE_VEIL01, 1);
        lAreaStringIndex = 1014;
    } else if (aCheck->flag == 1311) {
        dsq->continuity.setFlag(FLAG_TRANSTURTLE_VEIL02, 1);
        lAreaStringIndex = 1014;
    } else if (aCheck->flag == 1312) {
        dsq->continuity.setFlag(FLAG_TRANSTURTLE_OPENWATER03, 1);
        lAreaStringIndex = 1009;
    } else if (aCheck->flag == 1313) {
        dsq->continuity.setFlag(FLAG_TRANSTURTLE_FOREST04, 1);
        lAreaStringIndex = 1010;
    } else if (aCheck->flag == 1314) {
        dsq->continuity.setFlag(FLAG_TRANSTURTLE_MAINAREA, 1);
        lAreaStringIndex = 1008;
    } else if (aCheck->flag == 1315) {
        dsq->continuity.setFlag(FLAG_TRANSTURTLE_ABYSS03, 1);
        lAreaStringIndex = 1015;
    } else if (aCheck->flag == 1316) {
        dsq->continuity.setFlag(FLAG_TRANSTURTLE_FINALBOSS, 1);
        lAreaStringIndex = 1021;
    } else if (aCheck->flag == 1317) {
        dsq->continuity.setFlag(FLAG_TRANSTURTLE_FOREST05, 1);
        lAreaStringIndex = 1010;
    } else if (aCheck->flag == 1318) {
        dsq->continuity.setFlag(FLAG_TRANSTURTLE_SEAHORSE, 1);
        lAreaStringIndex = 1028;
    }
    dsq->game->setControlHint(
            dsq->continuity.stringBank.get(226) + " " + dsq->continuity.stringBank.get(lAreaStringIndex),
            false, false, false, 10
            );
}

/**
 * Get a new collectible item to activate in the local game
 * @param aCheck The collectible check item to activate
 */
void Randomizer::receivingCollectible(check_t *aCheck) {
    collectible_t *lCollectible = nullptr;
    for (int i = 0; i < collectibles->size() && !lCollectible; i = i + 1) {
        if (collectibles->at(i).name == aCheck->item) {
            lCollectible = &collectibles->at(i);
        }
    }
    assert(lCollectible && "The Collectible is not valid!");
    dsq->continuity.setFlag(lCollectible->flag, 1);
    if (lCollectible->flag == FLAG_PET_BLASTER) {
        dsq->continuity.setFlag(FLAG_COLLECTIBLE_BLASTER, 1);
        dsq->game->setControlHint(dsq->continuity.stringBank.get(30), false, false,
                                  false, 6, "collectibles/egg-blaster");
    } else if (lCollectible->flag == FLAG_PET_NAUTILUS) {
        dsq->continuity.setFlag(FLAG_COLLECTIBLE_NAUTILUS, 1);
        dsq->game->setControlHint(dsq->continuity.stringBank.get(33), false, false,
                                  false, 6, "collectibles/egg-nautilus");
    } else if (lCollectible->flag == FLAG_PET_DUMBO) {
        dsq->continuity.setFlag(FLAG_COLLECTIBLE_DUMBO, 1);
        dsq->game->setControlHint(dsq->continuity.stringBank.get(32), false, false,
                                  false, 6, "collectibles/egg-dumbo");
    } else if (lCollectible->flag == FLAG_PET_PIRANHA) {
        dsq->continuity.setFlag(FLAG_COLLECTIBLE_PIRANHA, 1);
        dsq->game->setControlHint(dsq->continuity.stringBank.get(31), false, false,
                                  false, 6, "collectibles/egg-piranha");
    }


}

/**
 * Get a new song item to activate in the local game
 * @param aCheck The song check item to activate
 */
void Randomizer::receivingSong(check_t *aCheck) {
    if (aCheck->flag == 1300) { // Li song
        dsq->continuity.setFlag(FLAG_LI, 100);
        dsq->continuity.learnSong(SONG_LI);
        dsq->game->setControlHint(dsq->continuity.stringBank.get(42), false, false,
                                  false, 8, "", false, SONG_LI);
        dsq->game->li = dsq->game->createEntity("li", 0, Vector (avatar->position.x, avatar->position.y), 0,
                                false, "Li", ET_ENEMY, true);
    } else if (aCheck->flag == 1301) { // Shield song
        dsq->continuity.learnSong(SONG_SHIELDAURA);
        dsq->game->setControlHint(dsq->continuity.stringBank.get(35), false, false,
                                  false, 8, "", false, SONG_SHIELDAURA);
    } else if (aCheck->flag == 1302) { // Dual song
        dsq->continuity.learnSong(SONG_DUALFORM);
        dsq->game->setControlHint(dsq->continuity.stringBank.get(43), false, false,
                                  false, 8, "", false, SONG_DUALFORM);
    } else if (aCheck->flag == 1303) { // Beast song
        dsq->continuity.learnSong(SONG_BEASTFORM);
        dsq->game->setControlHint(dsq->continuity.stringBank.get(38), false, false,
                                  false, 8, "", false, SONG_BEASTFORM);
    } else if (aCheck->flag == 1304) { // Sun song
        dsq->continuity.learnSong(SONG_SUNFORM);
        dsq->game->setControlHint(dsq->continuity.stringBank.get(41), false, false,
                                  false, 8, "", false, SONG_SUNFORM);
    } else if (aCheck->flag == 1305) { // Nature song
        dsq->continuity.learnSong(SONG_NATUREFORM);
        dsq->game->setControlHint(dsq->continuity.stringBank.get(40), false, false,
                                  false, 8, "", false, SONG_NATUREFORM);
    } else if (aCheck->flag == 1306) { // Energy song
        dsq->continuity.learnSong(SONG_ENERGYFORM);
        dsq->game->setControlHint(dsq->continuity.stringBank.get(37), false, false,
                                  false, 8, "", false, SONG_ENERGYFORM);
    } else if (aCheck->flag == 1307) { // Bind song
        dsq->continuity.learnSong(SONG_BIND);
        dsq->game->setControlHint(dsq->continuity.stringBank.get(36), false, false,
                                  false, 8, "", false, SONG_BIND);
    } else if (aCheck->flag == 1308) { // Fish song
        dsq->continuity.learnSong(SONG_FISHFORM);
        dsq->game->setControlHint(dsq->continuity.stringBank.get(39), false, false,
                                  false, 8, "", false, SONG_FISHFORM);
    } else if (aCheck->flag == 1309) { // Fish song
        dsq->continuity.learnSong(SONG_SPIRITFORM);
        dsq->game->setControlHint(dsq->continuity.stringBank.get(44), false, false,
                                  false, 8, "", false, SONG_SPIRITFORM);
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
        for (int i = 0; i < aCount; i = i + 1) {
            dsq->game->pickupIngredientEffects(lIngredient);
        }
	} else if (aItem.compare(0, 11, "upgrade_wok") == 0) {
		lMessageStream << "Upgrade: Wok";
		dsq->continuity.setFlag(FLAG_UPGRADE_WOK, 1);
	} else if (aItem.compare(0, 14, "upgrade_health") == 0) {
		lMessageStream << "Upgrade: Health";
		dsq->continuity.upgradeHealth();
	} else if (aItem.compare(0, 11, "collectible") == 0) {
        check_t *lCheck = getCheckByItem(aItem);
        lMessageStream << lCheck->message;
        receivingCollectible(lCheck);
    } else if (aItem.compare(0, 5, "song_") == 0) {
        check_t *lCheck = getCheckByItem(aItem);
        lMessageStream << lCheck->message;
        receivingSong(lCheck);
    } else if (aItem.compare(0, 10, "transport_") == 0) {
        check_t *lCheck = getCheckByItem(aItem);
        lMessageStream << lCheck->message;
        receivingTransport(lCheck);
	} else {
		assert(false && "The receving item is not valid!");
	}
    showQuickMessage(lMessageStream.str());
}

/**
 * Show a quick message on the screen.
 * @param aText The text to show
 */
void Randomizer::showQuickMessage(const std::string &aText){
    dsq->screenMessage(aText);
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
 * Retreive a random ingredient of a certain type (or of any type)
 * @param aType The Type of the ingredient (or any type if nothing)
 * @return the ingredient
 */
ingredient_t * Randomizer::getRandomIngredient(IngredientType aType = IT_ANYTHING) {
    std::vector<ingredient_t *> lIngredients;
    ingredient_t *lIngredient = nullptr;
    for (auto lIterator = ingredients->begin(); lIterator != ingredients->end(); ++lIterator) {
        if (aType == IT_ANYTHING || aType == lIterator->category) {
            lIngredients.push_back(lIterator.base());
        }
    }
    if (!lIngredients.empty()) {
        lIngredient = lIngredients.at(rand()%lIngredients.size());
    }
    assert(lIngredient && "getRandomIngredient: The ingredient is not valid");
    return lIngredient;
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
    if (aRecipe->result == "PoisonLoaf") {
        lResult = spawnIngredient("RottenMeat", aPosition,
                                             aTimes * 2, aOut, false);
    } else {
        for (int j = 0; j < aRecipe->names.size(); j = j + 1) {
            int lIndex = -1;
            for (int i = 0; lIndex < 0 && i < ingredients->size(); i = i + 1) {
                if (ingredients->at(i).name == aRecipe->names.at(j).name) {
                    lIndex = i;
                }
            }
            assert((lIndex != -1) && "spawnRecipe: The ingredient is not valid");
            lResult = spawnIngredient(aRecipe->names.at(j).name, aPosition,
                                      aTimes * aRecipe->names.at(j).amount, aOut, false);
        }
        for (int j = 0; j < aRecipe->types.size(); j = j + 1) {
            ingredient_t *lIngredient = getRandomIngredient(aRecipe->types.at(j).type);
            lResult = spawnIngredient(lIngredient->name, aPosition,
                                      aTimes * aRecipe->types.at(j).amount, aOut, false);
        }
    }
    return lResult;
}

/**
 * Spawn a number of ingredient at a position in space, at a certain time.
 * @param aIngredient The ingredient to spawn
 * @param aPosition At what position to spawn the ingredient
 * @param aTimes The number of ingredient to spawn
 * @param aOut Is the entity should spawn now.
 * @param aRandomized Is aIngredient randomized before spawn (default is true)
 * @return The (last) spawned ingredient;
 */
Entity *Randomizer::spawnIngredient(const std::string &aIngredient, const Vector &aPosition, int aTimes, int aOut, bool aRandomized) {
    Entity *lResult = nullptr;
    IngredientData *lIngredientData;
    std::string lIngredientName = aIngredient;
    if (nocasecmp(lIngredientName, "poultice")==0)
        lIngredientName = "LeafPoultice";
    IngredientData *lIngredientDataBeforeRandomize = dsq->continuity.getIngredientDataByName(lIngredientName);
    if (aRandomized) {
        lIngredientData = getRandomizedIngredientData(lIngredientDataBeforeRandomize);
    } else {
        lIngredientData = lIngredientDataBeforeRandomize;
    }

    if (nocasecmp(lIngredientData->name, "SeaLoaf")==0 || (lIngredientData->type > IT_NONE && lIngredientData->type < IT_INGREDIENTSEND)) {
        lResult = dsq->game->spawnIngredient(lIngredientData->name, aPosition, aTimes, aOut);
    } else {
        std::vector<Recipe> lRecipes = dsq->continuity.recipes;
        Recipe * lRecipe = nullptr;
        for (int i = 0; !lRecipe && i < lRecipes.size(); i = i + 1) {
            if (nocasecmp(lRecipes.at(i).result, lIngredientData->name)==0) {
                lRecipe = &lRecipes.at(i);
            }
        }
        if (lRecipe->isKnown()) {
            lResult = dsq->game->spawnIngredient(lIngredientData->name, aPosition, aTimes, aOut);
        } else {
            lResult = spawnRecipe(lRecipe, aPosition, aTimes, aOut);
        }
    }
    return lResult;
}

/**
 * Spawn a recipe desi from an entity.
 * @param entity The entity that spawn the recipe dish
 * @param recipe The recipe to spawn
 * @param aIngredientData The ingredient that represent the recipe
 */
void Randomizer::spawnRecipeFromEntity(Entity *aEntity, Recipe * aRecipe, IngredientData *aIngredientData) {
    if (aRecipe->result == "PoisonLoaf") {
        IngredientData *lIngredientData = dsq->continuity.getIngredientDataByName("RottenMeat");
        spawnIngredientFromEntity(aEntity, lIngredientData, false);
        spawnIngredientFromEntity(aEntity, lIngredientData, false);
    } else {
        for (int j = 0; j < aRecipe->names.size(); j = j + 1) {
            int lIndex = -1;
            for (int i = 0; lIndex < 0 && i < ingredients->size(); i = i + 1) {
                if (ingredients->at(i).name == aRecipe->names.at(j).name) {
                    lIndex = i;
                }
            }
            assert((lIndex != -1) && "spawnRecipeFromEntity: The ingredient is not valid");
            IngredientData *lIngredientData = dsq->continuity.getIngredientDataByName(aRecipe->names.at(j).name);
            for (int i = 0; i < aRecipe->names.at(j).amount; i = i + 1) {
                spawnIngredientFromEntity(aEntity, lIngredientData, false);
            }

        }
        for (int j = 0; j < aRecipe->types.size(); j = j + 1) {
            ingredient_t *lIngredient = getRandomIngredient(aRecipe->types.at(j).type);
            IngredientData *lIngredientData = dsq->continuity.getIngredientDataByName(lIngredient->name);
            for (int i = 0; i < aRecipe->types.at(j).amount; i = i + 1) {
                spawnIngredientFromEntity(aEntity, lIngredientData, false);
            }
        }
    }
}

/**
 * Spawn a ingredient from an entity.
 * @param aEntity The entity that spawn the ingredient
 * @param aIngredientData The ingredient to spawn
 * @param aRandomized Is aIngredientData should be randomized before spawning (default true)
 */
void Randomizer::spawnIngredientFromEntity(Entity *aEntity, IngredientData *aIngredientData, bool aRandomized)
{
    IngredientData *lIngredientData = aIngredientData;
    if (aRandomized) {
        lIngredientData = getRandomizedIngredientData(aIngredientData);
    }
    if (lIngredientData->type > IT_NONE && lIngredientData->type < IT_INGREDIENTSEND ) {
        dsq->game->spawnIngredientFromEntityRandomized(aEntity, lIngredientData);
    } else {
        std::vector<Recipe> lRecipes = dsq->continuity.recipes;
        Recipe * lRecipe = nullptr;
        for (int i = 0; !lRecipe && i < lRecipes.size(); i = i + 1) {
            if (nocasecmp(lRecipes.at(i).result, lIngredientData->name)==0) {
                lRecipe = &lRecipes.at(i);
            }
        }
        if (lRecipe->isKnown()) {
            dsq->game->spawnIngredientFromEntityRandomized(aEntity,lIngredientData);
        } else {
            spawnRecipeFromEntity(aEntity,lRecipe, lIngredientData);
        }
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

/**
 * Assign the unique ID for the Randomizer
 * @param aUid The ID of the Randomizer
 */
void Randomizer::setUid(std::string aUid) {
    uid = std::move(aUid);
}


/**
 * The unique ID for the Randomizer
 * @return The ID of the Randomizer
 */
std::string Randomizer::getUid() {
    return uid;
}

/**
 * Is the Aquarian text in the game should be translated
 * @param aValue The value to assign to `isAquarianTranslated`
 */
void Randomizer::setIsAquarianTranslated(bool aValue){
    isAquarianTranslated = aValue;
}

/**
 * Is the Aquarian text in the game should be translated
 * @return True if the text should be translated
 */
bool Randomizer::getIsAquarianTranslated(){
    return isAquarianTranslated;
}

/**
 * Get the file name (without path and extension) of the graphic file to show Aquarian text
 * @return The filename
 */
std::string Randomizer::getAquarianGfx(){
    std::string lResult = "aquarian";
    if (isAquarianTranslated) {
        lResult = "aquarian_alt";
    }
    return lResult;
}

/**
 * Set the avatar (Naija) object
 * @param aAvatar Naija
 */
void Randomizer::setAvatar(Avatar *aAvatar) {
    avatar = aAvatar;
}

/**
 * A now or saves game has been load
   @param aNewGame True if a new game is launched.
 */
void Randomizer::onLoad(bool aNewGame){
    if (!aNewGame) {
        dsq->toggleCursor(true);
        if (dsq->confirm("Restart at Naija's cave?","", false, 3.0)) {
            dsq->game->sceneToLoad = "naijacave";
            dsq->game->positionToAvatar = Vector(8880, 3881);
        }
        dsq->toggleCursor(false);
    }
    inGame = true;
}

/**
 * When a game is quitting.
 */
void Randomizer::onClose() {
    inGame = false;
}

