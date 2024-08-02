/**
 * @author      : Louis M (prog@tioui.com)
 * @created     : Wed, jan 10, 2024 16:08:04 EST
 * @license     : MIT
 * Class that encapsulate every randomization functionalities
 */

#include "../Aquaria/Game.h"
#include "Randomizer.h"
#include <cassert>
#include <utility>
#include <vector>
#include "apclient.hpp"
#include "../Aquaria/Avatar.h"
#include "../BBGE/Event.h"

/**
 * Constructor for the Randomizer
 */
Randomizer::Randomizer() : ActionMapper() {
	ingredientReplacement = new std::vector<int>();
    error = false;
    inGame = false;
    errorMessage = "";
    blindGoal = 0;
    maximumIngredientAmount = 8;
    skipFirstVision = false;
    skipFinalBoss3rdForm = false;
    infiniteHotSoup = false;
    unconfine_home_water_transturtle = false;
    unconfine_home_water_energy_door = false;
    isAquarianTranslated = false;
    secretsNeeded = false;
    checks = new std::vector<check_t>();
    ingredients = new std::vector<ingredient_t>();
    collectibles = new std::vector<collectible_t>();
    nextMessages = new std::queue<randomessage_t>();
    currentMessageTime = 0;
    miniBossesToKill = 0;
    bigBossesToKill = 0;
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
    checks->push_back({1101, "bulb_turtlecave","ingredient_leafpoultice",3, "Leaf poultice",
                       "Turtle cave, bulb in Bubble Cliff"});
    checks->push_back({1102, "bulb_openwater_tl_1","ingredient_handroll",1, "Hand roll",
                       "Open Waters top left area, bulb under the rock in the right path"});
    checks->push_back({1103, "bulb_openwater_tl_2","ingredient_veggiesoup",1, "Veggie soup",
                       "Open Waters top left area, bulb under the rock in the left path"});
    checks->push_back({1104, "bulb_openwater_tl_3","ingredient_butterysealoaf",1, "Buttery sea loaf",
                       "Open Waters top left area, bulb to the right of the save crystal"});
    checks->push_back({1105, "bulb_openwater_tr_1","ingredient_healingpoultice",1, "Healing poultice",
                       "Open Waters top right area, bulb in the small path before Mithalas"});
    checks->push_back({1106, "bulb_openwater_tr_2","ingredient_sealoaf",2, "Sea loaf",
                       "Open Waters top right area, bulb in the path from the left entrance"});
    checks->push_back({1107, "bulb_openwater_tr_3","ingredient_spicyroll",1, "Spicy roll",
                       "Open Waters top right area, bulb in the clearing close to the bottom exit"});
    checks->push_back({1108, "bulb_openwater_tr_4","ingredient_spicymeat",2, "Spicy meat",
                       "Open Waters top right area, bulb in the big clearing close to the save crystal"});
    checks->push_back({1109, "bulb_openwater_tr_5","ingredient_crabcake",1, "Crab cake",
                       "Open Waters top right area, bulb in the big clearing to the top exit"});
    checks->push_back({1110, "bulb_openwater_tr_6","ingredient_spicyroll",1, "Spicy roll",
                       "Open Waters top right area, bulb in the turtle room"});
    checks->push_back({1111, "bulb_openwater_bl_1","ingredient_leadershiproll",2, "Leadership roll",
                       "Open Waters bottom left area, bulb inside the lowest fish pass"});
    checks->push_back({1112, "bulb_openwater_bl_2","ingredient_healingpoultice",2, "Healing poultice",
                       "Open Waters bottom left area, bulb behind the chomper fish"});
    checks->push_back({1113, "bulb_skeleton_path_1","ingredient_tastycake",1, "Tasty cake",
                       "Open Waters skeleton path, bulb close to the right exit"});
    checks->push_back({1114, "bulb_skeleton_path_2","ingredient_perogi",1, "Perogi",
                       "Open Waters skeleton path, bulb behind the chomper fish"});
    checks->push_back({1115, "bulb_arnassi_1","ingredient_tastyroll",1, "Tasty roll",
                       "Arnassi Ruins, bulb in the right part"});
    checks->push_back({1116, "bulb_arnassi_2","ingredient_specialbulb",1, "Special bulb",
                       "Arnassi Ruins, bulb in the left part"});
    checks->push_back({1117, "bulb_arnassi_3","ingredient_specialcake",1, "Special cake",
                       "Arnassi Ruins, bulb in the center part"});
    checks->push_back({1118, "bulb_sunworm_1","ingredient_plantleaf",3, "Plant leaf",
                       "Sun Worm path, first path bulb"});
    checks->push_back({1119, "bulb_sunworm_2","ingredient_turtlesoup",1, "Turtle soup",
                       "Sun Worm path, second path bulb"});
    checks->push_back({1120, "bulb_sunworm_3","ingredient_specialcake",1, "Special cake",
                       "Sun Worm path, first cliff bulb"});
    checks->push_back({1121, "bulb_sunworm_4","ingredient_specialbulb",1, "Special bulb",
                       "Sun Worm path, second cliff bulb"});
    checks->push_back({1122, "bulb_tutorial_1","ingredient_handroll",1, "Hand roll",
                       "Verse Cave left area, bulb in the center part"});
    checks->push_back({1123, "bulb_tutorial_2","ingredient_hotsoup",1, "Hot soup",
                       "Verse Cave left area, bulb in the right part"});
    checks->push_back({1124, "bulb_tutorial_3","ingredient_heartysoup",1, "Hearty soup",
                       "Verse Cave left area, bulb under the rock at the end of the path"});
    checks->push_back({1125, "bulb_abyss_l_1","ingredient_coldborscht",1, "Cold borscht",
                       "Abyss left area, bulb in hidden path room"});
    checks->push_back({1126, "bulb_abyss_l_2","ingredient_healingpoultice",2, "Healing poultice",
                       "Abyss left area, bulb in the right part"});
    checks->push_back({1127, "bulb_abyss_l_3","ingredient_sightpoultice",1, "Sight poultice",
                       "Abyss left area, bulb in the bottom fish pass"});
    checks->push_back({1128, "bulb_energy_temple_1_1","ingredient_leafpoultice",1, "Leaf poultice",
                       "Energy Temple first area, bulb in the bottom room blocked by a rock"});
    checks->push_back({1129, "bulb_energy_temple_2_1","ingredient_spicyroll",1, "Spicy roll",
                       "Energy Temple second area, bulb under the rock"});
    checks->push_back({1130, "bulb_energy_temple_3_1","ingredient_plantleaf",2, "Plant leaf",
                       "Energy Temple third area, bulb in the bottom path"});
    checks->push_back({1131, "bulb_mithalas_city_01","ingredient_spicyroll",1, "Spicy roll",
                       "Mithalas City, first bulb in the left city part"});
    checks->push_back({1132, "bulb_mithalas_city_02","ingredient_spicymeat",2, "Spicy meat",
                       "Mithalas City, bulb in the right part"});
    checks->push_back({1133, "bulb_mithalas_city_03","ingredient_vedhaseacrisp",1, "Vedha sea crisp",
                       "Mithalas City, first bulb at the end of the top path"});
    checks->push_back({1134, "bulb_mithalas_city_04","ingredient_heartysoup",1, "Hearty soup",
                       "Mithalas City, bulb at the top of the city"});
    checks->push_back({1135, "bulb_mithalas_city_05","ingredient_healingpoultice",1, "Healing poultice",
                       "Mithalas City, first bulb in a broken home"});
    checks->push_back({1136, "bulb_mithalas_city_06","ingredient_vedhaseacrisp",1, "Vedha sea crisp",
                       "Mithalas City, second bulb in the left city part"});
    checks->push_back({1137, "bulb_mithalas_city_07","ingredient_rottenloaf",8, "Rotten loaf",
                       "Mithalas City, bulb in the top path"});
    checks->push_back({1138, "bulb_mithalas_city_08","ingredient_rottenmeat",8, "Rotten meat",
                       "Mithalas City, bulb in the bottom left part"});
    checks->push_back({1139, "bulb_mithalas_city_09","ingredient_smalltentacle",2, "Small tentacle",
                       "Mithalas City, first bulb in one of the homes"});
    checks->push_back({1140, "bulb_mithalas_city_10","ingredient_seacake",1, "Sea cake",
                       "Mithalas City, second bulb in one of the homes"});
    checks->push_back({1141, "bulb_mithalas_city_11","ingredient_smallbone",3, "Small bone",
                       "Mithalas City, second bulb at the end of the top path"});
    checks->push_back({1142, "bulb_mithalas_city_12","ingredient_handroll",1, "Hand roll",
                       "Mithalas City, second bulb in a broken home"});
    checks->push_back({1143, "bulb_cathedral_l_2","ingredient_heartysoup",1, "Hearty soup",
                       "Mithalas City Castle, bulb in the flesh hole"});
    checks->push_back({1144, "bulb_boilerroom_1","ingredient_spicyroll",1, "Spicy roll",
                       "Sunken City, bulb on top of the boss area"});
    checks->push_back({1145, "bulb_forest_tl_1","ingredient_seacake",1, "Sea cake",
                       "Kelp Forest top left area, bulb in the bottom left clearing"});
    checks->push_back({1146, "bulb_forest_tl_2","ingredient_spicyroll",1, "Spicy roll",
                       "Kelp Forest top left area, bulb in the path down from the top left clearing"});
    checks->push_back({1147, "bulb_forest_tl_3","ingredient_leechingpoultice",1, "Leeching poultice",
                       "Kelp Forest top left area, bulb in the top left clearing"});
    checks->push_back({1148, "bulb_forest_tl_4","ingredient_redbulb",2, "Red bulb",
                       "Kelp Forest top left area, bulb close to the Verse Egg"});
    checks->push_back({1149, "bulb_forest_tr_1","ingredient_spiderroll",1, "Spider roll",
                       "Kelp Forest top right area, bulb under the rock in the right path"});
    checks->push_back({1150, "bulb_forest_tr_2","ingredient_veggiecake",1, "Veggie cake",
                       "Kelp Forest top right area, bulb at the left of the center clearing"});
    checks->push_back({1151, "bulb_forest_tr_3","ingredient_swampcake",1, "Swamp cake",
                       "Kelp Forest top right area, bulb in the top fish pass"});
    checks->push_back({1152, "bulb_forest_tr_4","ingredient_sharkfinsoup",1, "Shark fin soup",
                       "Kelp Forest top right area, bulb in the left path's big room"});
    checks->push_back({1153, "bulb_forest_tr_5","ingredient_healingpoultice",1, "Healing poultice",
                       "Kelp Forest top right area, bulb in the left path's small room"});
    checks->push_back({1154, "bulb_forest_tr_6","ingredient_redbulb",2, "Red bulb",
                       "Kelp Forest top right area, bulb at the top of the center clearing"});
    checks->push_back({1155, "bulb_forest_bl_1","ingredient_spiderroll",1, "Spider roll",
                       "Kelp Forest bottom left area, bulb close to the spirit crystals"});
    checks->push_back({1156, "bulb_forest_boss_room_1","ingredient_handroll",1, "Hand roll",
                       "Kelp Forest boss room, bulb at the bottom of the area"});
    checks->push_back({1157, "bulb_forest_sprite_cave_1","ingredient_leechingpoultice",1, "Leeching poultice",
                       "Kelp Forest sprite cave, bulb inside the fish pass"});
    checks->push_back({1158, "bulb_forest_sprite_cave_2","ingredient_veggiesoup",1, "Veggie soup",
                       "Kelp Forest sprite cave, bulb in the second room"});
    checks->push_back({1159, "bulb_home_water_1","ingredient_smallegg",2, "Small egg",
                       "Home Waters, bulb below the grouper fish"});
    checks->push_back({1160, "bulb_home_water_2","ingredient_leafpoultice",1, "Leaf poultice",
                       "Home Waters, bulb in the path below Nautilus Prime"});
    checks->push_back({1161, "bulb_home_water_3","ingredient_leafpoultice",1, "Leaf poultice",
                       "Home Waters, bulb in the little room above the grouper fish"});
    checks->push_back({1162, "bulb_home_water_4","ingredient_plantleaf",3, "Plant leaf",
                       "Home Waters, bulb in the end of the path close to the Verse Cave"});
    checks->push_back({1163, "bulb_home_water_5","ingredient_redbulb",2, "Red bulb",
                       "Home Waters, bulb in the top left path"});
    checks->push_back({1164, "bulb_home_water_6","ingredient_hotsoup",1, "Hot soup",
                       "Home Waters, bulb in the bottom left room"});
    checks->push_back({1165, "bulb_home_water_7","ingredient_fishmeat",2, "Fish meat",
                       "Home Waters, bulb close to Naija's Home"});
    checks->push_back({1166, "bulb_home_water_8","ingredient_seacake",1, "Sea cake",
                       "Home Waters, bulb under the rock in the left path from the Verse Cave"});
    checks->push_back({1167, "bulb_final_l_1","ingredient_arcanepoultice",1, "Arcane poultice",
                       "The Body left area, first bulb in the top face room"});
    checks->push_back({1168, "bulb_final_l_2","ingredient_divinesoup",1, "Divine soup",
                       "The Body left area, bulb below the water stream"});
    checks->push_back({1169, "bulb_final_l_3","ingredient_spicyroll",1, "Spicy roll",
                       "The Body left area, bulb in the top path to the top face room"});
    checks->push_back({1170, "bulb_final_l_4","ingredient_volcanoroll",1, "Volcano roll",
                       "The Body left area, second bulb in the top face room"});
    checks->push_back({1171, "bulb_final_l_5","ingredient_arcanepoultice",1, "Arcane poultice",
                       "The Body left area, bulb in the bottom face room"});
    checks->push_back({1172, "bulb_song_cave_1","ingredient_specialbulb",1, "Special bulb",
                       "Song Cave, bulb in the top right part"});
    checks->push_back({1173, "bulb_song_cave_2","ingredient_handroll",1, "Hand roll",
                       "Song Cave, bulb in the big anemone room"});
    checks->push_back({1174, "bulb_song_cave_3","ingredient_eeloil",2, "Eel oil",
                       "Song Cave, bulb in the path to the singing statues"});
    checks->push_back({1175, "bulb_song_cave_4","ingredient_leafpoultice",1, "Leaf poultice",
                       "Song Cave, bulb under the rock in the path to the singing statues"});
    checks->push_back({1176, "bulb_song_cave_5","ingredient_hotsoup",1, "Hot soup",
                       "Song Cave, bulb under the rock close to the song door"});
    checks->push_back({1177, "bulb_veil_tl_1","ingredient_spicysoup",1, "Spicy soup",
                       "The Veil top left area, bulb hidden behind the blocking rock"});
    checks->push_back({1178, "bulb_veil_tl_2","ingredient_longlifesoup",1, "Long life soup",
                       "The Veil top left area, bulb inside the fish pass"});
    checks->push_back({1179, "bulb_veil_tl_3","ingredient_hotsoup",2, "Hot soup",
                       "The Veil top left area, bulb under the rock in the top right path"});
    checks->push_back({1180, "bulb_veil_tr_1","ingredient_sharkfinsoup",1, "Shark fin soup",
                       "The Veil top right area, bulb in the middle of the wall jump cliff"});
    checks->push_back({1181, "bulb_veil_tr_2","ingredient_legendarycake",1, "Legendary cake",
                       "The Veil top right area, bulb at the top of the waterfall"});
    checks->push_back({1182, "bulb_veil_b_1","ingredient_swampcake",1, "Swamp cake",
                       "The Veil bottom area, bulb in the spirit path"});
    checks->push_back({1183, "bulb_veil_b_2","ingredient_swampcake",1, "Swamp cake",
                       "The Veil bottom area, bulb in the left path"});
    checks->push_back({1184, "bulb_ice_cave_1","ingredient_icecream",1, "Ice cream",
                       "Ice Cavern, bulb in the room to the right"});
    checks->push_back({1185, "bulb_ice_cave_2","ingredient_berryicecream",1, "Berry ice cream",
                       "Ice Cavern, first bulb in the top exit room"});
    checks->push_back({1186, "bulb_ice_cave_3","ingredient_veggieicecream",1, "Veggie ice cream",
                       "Ice Cavern, second bulb in the top exit room"});
    checks->push_back({1187, "bulb_ice_cave_4","ingredient_dumboicecream",1, "Dumbo ice cream",
                       "Ice Cavern, third bulb in the top exit room"});
    checks->push_back({1188, "bulb_ice_cave_5","ingredient_icecream",1, "Ice cream",
                       "Ice Cavern, bulb in the left room"});
    checks->push_back({1189, "bulb_king_jellyfish_cave_1","ingredient_specialbulb",1, "Special bulb",
                       "King Jellyfish Cave, bulb in the right path from King Jelly"});
    checks->push_back({1190, "bulb_bubble_cave_1","ingredient_coldsoup",1, "Cold soup",
                       "Bubble Cave, bulb in the left cave wall"});
    checks->push_back({1191, "bulb_bubble_cave_2","ingredient_coldborscht",1, "Cold borscht",
                       "Bubble Cave, bulb in the right cave wall (behind the ice crystal)"});
    checks->push_back({1192, "bulb_sun_temple_1","ingredient_glowingegg",2, "Glowing egg",
                       "Sun Temple, first bulb of the temple"});
    checks->push_back({1193, "bulb_sun_temple_2","ingredient_magicsoup",1, "Magic soup",
                       "Sun Temple, bulb on the right part"});
    checks->push_back({1194, "bulb_sun_temple_3","ingredient_royalsoup",1, "Royal soup",
                       "Sun Temple, bulb in the hidden room of the right part"});
    checks->push_back({1195, "bulb_sun_temple_4","ingredient_leadershiproll",1, "Leadership roll",
                       "Sun Temple, bulb in the top left part"});
    checks->push_back({1196, "bulb_sun_temple_5","ingredient_turtlesoup",1, "Turtle soup",
                       "Sun Temple, bulb in the top right part"});
    checks->push_back({1197, "bulb_sun_temple_6","ingredient_heartysoup",1, "Hearty soup",
                       "Sun Temple, bulb at the top of the high dark room"});
    checks->push_back({1198, "bulb_final_c_1","ingredient_Zuuna'sperogi",1, "Zuuna's perogi",
                       "The Body center area, bulb on the main path blocking tube"});
    checks->push_back({1199, "bulb_final_r_1","ingredient_plumpperogi",1, "Plump perogi",
                       "The Body right area, bulb in the top path to the bottom face room"});
    checks->push_back({1200, "bulb_final_r_2","ingredient_arcanepoultice",1, "Arcane poultice",
                       "The Body right area, bulb in the bottom face room"});
    checks->push_back({1201, "bulb_final_r_3","ingredient_arcanepoultice",1, "Arcane poultice",
                       "The Body right area, bulb in the top face room"});
    checks->push_back({1202, "bulb_final_b_1","ingredient_longlifesoup",1, "Long life soup",
                       "The Body bottom area, bulb in the Jelly Zap room"});
    checks->push_back({1203, "bulb_final_b_2","ingredient_spicyroll",1, "Spicy roll",
                       "The Body bottom area, bulb in the nautilus room"});
    checks->push_back({1204, "bulb_final_boss_1","ingredient_Vedha'sCure-All",1, "Vedha's Cure-All",
                       "Final Boss area, first bulb in the turtle room"});
    checks->push_back({1205, "bulb_final_boss_2","ingredient_loafoflife",1, "Loaf of life",
                       "Final Boss area, second bulb in the turtle room"});
    checks->push_back({1206, "bulb_final_boss_3","ingredient_specialbulb",1, "Special bulb",
                       "Final Boss area, third bulb in the turtle room"});
    checks->push_back({1207, "bulb_final_boss_4","ingredient_dumboicecream",1, "Dumbo ice cream",
                       "Final Boss area, bulb in the boss third form room"});
    checks->push_back({1208, "bulb_starting_cave_1","ingredient_fishoil",1, "Fish oil",
                       "Verse Cave right area, bulb in the skeleton room"});
    checks->push_back({1209, "bulb_starting_cave_2","ingredient_smallegg",1, "Small egg",
                       "Verse Cave right area, bulb in the path right of the skeleton room"});
    checks->push_back({1210, "bulb_abyss_r_1","ingredient_dumboicecream",1, "Dumbo ice cream",
                       "Abyss right area, bulb behind the rock in the whale room"});
    checks->push_back({1211, "bulb_abyss_r_2","ingredient_tastyroll",1, "Tasty roll",
                       "Abyss right area, bulb in the middle path"});
    checks->push_back({1212, "bulb_abyss_r_3","ingredient_healingpoultice",1, "Healing poultice",
                       "Abyss right area, bulb behind the rock in the middle path"});
    checks->push_back({1213, "bulb_abyss_r_4","ingredient_hotborscht",1, "Hot borscht",
                       "Abyss right area, bulb in the left green room"});
    checks->push_back({1214, "bulb_cathedral_under_ground_1","ingredient_arcanepoultice",1, "Arcane poultice",
                       "Mithalas Cathedral Underground, bulb in the center part"});
    checks->push_back({1215, "bulb_cathedral_under_ground_2","ingredient_plantleaf",1, "Plant leaf",
                       "Mithalas Cathedral Underground, first bulb in the top left part"});
    checks->push_back({1216, "bulb_cathedral_under_ground_3","ingredient_arcanepoultice",1, "Arcane poultice",
                       "Mithalas Cathedral Underground, second bulb in the top left part"});
    checks->push_back({1217, "bulb_cathedral_under_ground_4","ingredient_redberry",1, "Red berry",
                       "Mithalas Cathedral Underground, third bulb in the top left part"});
    checks->push_back({1218, "bulb_cathedral_under_ground_5","ingredient_leafpoultice",1, "Leaf poultice",
                       "Mithalas Cathedral Underground, bulb close to the save crystal"});
    checks->push_back({1219, "bulb_cathedral_under_ground_6","ingredient_arcanepoultice",1, "Arcane poultice",
                       "Mithalas Cathedral Underground, bulb in the bottom right path"});
    checks->push_back({1220, "bulb_naija_home_1","ingredient_spicyroll",1, "Spicy roll",
                       "Naija's Home, bulb after the energy door"});
    checks->push_back({1221, "bulb_naija_home_2","ingredient_heartysoup",1, "Hearty soup",
                       "Naija's Home, bulb under the rock at the right of the main path"});
    checks->push_back({1222, "bulb_mermog_cave_1","ingredient_leechingpoultice",1, "Leeching poultice",
                       "Mermog cave, bulb in the left part of the cave"});
    checks->push_back({1223, "bulb_octo_cave_1","ingredient_sightpoultice",1, "Sight poultice",
                       "Octopus Cave, bulb in the path below the Octopus Cave path"});
    checks->push_back({1224, "urn_mithalas_city_1","ingredient_rottenmeat",2, "Rotten meat",
                       "Mithalas City, first urn in one of the homes"});
    checks->push_back({1225, "urn_mithalas_city_2","ingredient_glowingegg",1, "Glowing egg",
                       "Mithalas City, second urn in one of the homes"});
    checks->push_back({1226, "urn_mithalas_city_3","ingredient_rainbowmushroom",1, "Rainbow mushroom",
                       "Mithalas City, first urn in the city reserve"});
    checks->push_back({1227, "urn_mithalas_city_4","ingredient_rainbowmushroom",1, "Rainbow mushroom",
                       "Mithalas City, second urn in the city reserve"});
    checks->push_back({1228, "urn_mithalas_city_5","ingredient_rainbowmushroom",1, "Rainbow mushroom",
                       "Mithalas City, third urn in the city reserve"});
    checks->push_back({1229, "urn_mithalas_city_6","ingredient_plantleaf",3, "Plant leaf",
                       "Mithalas City, urn in the Castle flower tube entrance"});
    checks->push_back({1230, "urn_mithalas_city_7","ingredient_spicyroll",1, "Spicy roll",
                       "Mithalas City, urn inside a home fish pass"});
    checks->push_back({1231, "urn_cathedral_l_1","ingredient_rainbowmushroom",1, "Rainbow mushroom",
                       "Mithalas City Castle, urn in the bedroom"});
    checks->push_back({1232, "urn_cathedral_l_2","ingredient_smallbone",2, "Small bone",
                       "Mithalas City Castle, first urn of the single lamp path"});
    checks->push_back({1233, "urn_cathedral_l_3","ingredient_rottenmeat",1, "Rotten meat",
                       "Mithalas City Castle, second urn of the single lamp path"});
    checks->push_back({1234, "urn_cathedral_l_4","ingredient_fishoil",1, "Fish oil",
                       "Mithalas City Castle, urn in the bottom room"});
    checks->push_back({1235, "urn_cathedral_l_5","ingredient_rottenmeat",1, "Rotten meat",
                       "Mithalas City Castle, first urn on the entrance path"});
    checks->push_back({1236, "urn_cathedral_l_6","ingredient_rainbowsoup",1, "Rainbow soup",
                       "Mithalas City Castle, second urn on the entrance path"});
    checks->push_back({1237, "urn_cathedral_r_01","ingredient_plantleaf",1, "Plant leaf",
                       "Mithalas Cathedral, first urn in the top right room"});
    checks->push_back({1238, "urn_cathedral_r_02","ingredient_rottencake",1, "Rotten cake",
                       "Mithalas Cathedral, second urn in the top right room"});
    checks->push_back({1239, "urn_cathedral_r_03","ingredient_toughcake",1, "Tough cake",
                       "Mithalas Cathedral, third urn in the top right room"});
    checks->push_back({1240, "urn_cathedral_r_04","ingredient_spicyroll",1, "Spicy roll",
                       "Mithalas Cathedral, bulb in the flesh room with fleas"});
    checks->push_back({1241, "urn_cathedral_r_05","ingredient_rottenmeat",1, "Rotten meat",
                       "Mithalas Cathedral, first urn in the bottom right path"});
    checks->push_back({1242, "urn_cathedral_r_06","ingredient_plantleaf",1, "Plant leaf",
                       "Mithalas Cathedral, second urn in the bottom right path"});
    checks->push_back({1243, "urn_cathedral_r_07","ingredient_leechingpoultice",1, "Leeching poultice",
                       "Mithalas Cathedral, urn behind the flesh vein"});
    checks->push_back({1244, "urn_cathedral_r_08","ingredient_smallbone",3, "Small bone",
                       "Mithalas Cathedral, urn in the top left eyes boss room"});
    checks->push_back({1245, "urn_cathedral_r_09","ingredient_plantleaf",2, "Plant leaf",
                       "Mithalas Cathedral, first urn in the path behind the flesh vein"});
    checks->push_back({1246, "urn_cathedral_r_10","ingredient_rottenmeat",1, "Rotten meat",
                       "Mithalas Cathedral, second urn in the path behind the flesh vein"});
    checks->push_back({1247, "urn_cathedral_r_11","ingredient_poisonloaf",1, "Poison loaf",
                       "Mithalas Cathedral, third urn in the path behind the flesh vein"});
    checks->push_back({1248, "urn_cathedral_r_12","ingredient_poisonsoup",1, "Poison soup",
                       "Mithalas Cathedral, fourth urn in the top right room"});
    checks->push_back({1249, "urn_openwater_tr_1","ingredient_smallbone",3, "Small bone",
                       "Open Waters top right area, first urn in the Mithalas exit"});
    checks->push_back({1250, "urn_openwater_tr_2","ingredient_rottenmeat",1, "Rotten meat",
                       "Open Waters top right area, second urn in the Mithalas exit"});
    checks->push_back({1251, "urn_openwater_tr_3","ingredient_sealoaf",1, "Sea loaf",
                       "Open Waters top right area, third urn in the Mithalas exit"});
    checks->push_back({1252, "crate_sunkencity_2_1","ingredient_fishoil",3, "Fish oil",
                       "Sunken City left area, crate in the little pipe room"});
    checks->push_back({1253, "crate_sunkencity_2_2","ingredient_mushroom",2, "Mushroom",
                       "Sunken City left area, crate close to the save crystal"});
    checks->push_back({1254, "crate_sunkencity_2_3","ingredient_spicymeat",2, "Spicy meat",
                       "Sunken City left area, crate before the bedroom"});
    checks->push_back({1255, "crate_sunkencity_1_1","ingredient_seacake",1, "Sea cake",
                       "Sunken City right area, crate close to the save crystal"});
    checks->push_back({1256, "crate_sunkencity_1_2","ingredient_plantleaf",3, "Plant leaf",
                       "Sunken City right area, crate in the left bottom room"});
    checks->push_back({1257, "beating_simon","upgrade_wok",1, "Wok",
                       "Simon Says area, beating Simon Says"});
    checks->push_back({1258, "health_egg_1","upgrade_health_1",1, "Health",
                       "The Veil bottom area, Verse Egg"});
    checks->push_back({1259, "health_egg_2","upgrade_health_2",1, "Health",
                       "Kelp Forest top left area, Verse Egg"});
    checks->push_back({1260, "health_egg_3","upgrade_health_3",1, "Health",
                       "The Whale, Verse Egg"});
    checks->push_back({1261, "health_egg_4","upgrade_health_4",1, "Health",
                       "Song Cave, Verse Egg"});
    checks->push_back({1262, "health_egg_5","upgrade_health_5",1, "Health",
                       "Bubble Cave, Verse Egg"});
    checks->push_back({1263, "collect_anemone","collectible_anemone",1, "Anemone",
                       "Song Cave, Anemone Seed"});
    checks->push_back({1264, "collect_energy_temple","collectible_energy_temple",1, "Krotite armor",
                       "Energy Temple bottom entrance, Krotite Armor"});
    checks->push_back({1265, "collect_arnassi_statue","collectible_arnassi_statue",1, "Arnassi statue",
                       "Arnassi Ruins, Arnassi Statue"});
    checks->push_back({1266, "collect_mithalas_banner","collectible_mithalas_banner",1, "Mithalas banner",
                       "Mithalas City Castle, Blue Banner"});
    checks->push_back({1267, "collect_bio_seed","collectible_bio_seed",1, "Glowing seed",
                       "Abyss left area, Glowing Seed"});
    checks->push_back({1268, "collect_blackpearl","collectible_blackpearl",1, "Black pearl",
                       "Kelp Forest top right area, Black Pearl"});
    checks->push_back({1269, "collect_treasure_chest","collectible_treasure_chest",1, "Odd container",
                       "Kelp Forest bottom right area, Odd Container"});
    checks->push_back({1270, "collect_energy_boss","collectible_energy_boss",1, "Tooth",
                       "Energy Temple boss area, Fallen God Tooth"});
    checks->push_back({1271, "collect_energy_statue","collectible_energy_statue",1, "Energy statue",
                       "Energy Temple first area, Energy Idol"});
    checks->push_back({1272, "collect_golden_gear","collectible_golden_gear",1, "Golden gear",
                       "Sun Temple, Golden Gear"});
    checks->push_back({1273, "collect_jelly_plant","collectible_jelly_plant",1, "Jelly plant",
                       "Abyss left area, Glowing Plant"});
    checks->push_back({1274, "collect_mithala_doll","collectible_mithala_doll",1, "Mithalas doll",
                       "Mithalas City, Doll"});
    checks->push_back({1275, "collect_mithalas_pot","collectible_mithalas_pot",1, "Mithalas pot",
                       "Mithalas City, Mithalas Pot"});
    checks->push_back({1276, "collect_big_seed","collectible_big_seed",1, "Big seed",
                       "Verse Cave right area, Big Seed"});
    checks->push_back({1277, "collect_seed_bag","collectible_seed_bag",1, "Seed bag",
                       "Kelp Forest sprite cave, Seed Bag"});
    checks->push_back({1278, "collect_skull","collectible_skull",1, "King's Skull",
                       "Open Waters skeleton path, King Skull"});
    checks->push_back({1279, "collect_jelly_beacon","collectible_jelly_beacon",1, "Jelly beacon",
                       "Song Cave, Jelly Beacon"});
    checks->push_back({1280, "collect_spore_seed","collectible_spore_seed",1, "Song plant spore",
                       "Arnassi Ruins, Song Plant Spore"});
    checks->push_back({1281, "collect_gold_star","collectible_gold_star",1, "Golden starfish",
                       "The Veil top right area, Golden Starfish"});
    checks->push_back({1282, "collect_stone_head","collectible_stone_head",1, "Stone head",
                       "The Veil bottom area, Stone Head"});
    checks->push_back({1283, "collect_sun_key","collectible_sun_key",1, "Sun key",
                       "Sun Temple, Sun Key"});
    checks->push_back({1284, "collect_trident_head","collectible_trident_head",1, "Trident",
                       "Mithalas City Castle, Trident Head"});
    checks->push_back({1285, "collect_turtle_egg","collectible_turtle_egg",1, "Turtle egg",
                       "Turtle cave, Turtle Egg"});
    checks->push_back({1286, "collect_upsidedown_seed","collectible_upsidedown_seed",1, "Jelly egg",
                       "Kelp Forest top left area, Jelly Egg"});
    checks->push_back({1287, "collect_walker","collectible_walker",1, "Baby walker",
                       "Kelp Forest bottom left area, Walker Baby"});
    checks->push_back({1288, "collect_crab_costume","collectible_crab_costume",1, "Crab armor",
                       "Arnassi Ruins, Crab Armor"});
    checks->push_back({1289, "collect_jelly_costume","collectible_jelly_costume",1, "Jelly costume",
                       "King Jellyfish Cave, Jellyfish Costume"});
    checks->push_back({1290, "collect_mithalan_costume","collectible_mithalan_costume",1, "Mithalan dress",
                       "Mithalas Cathedral, Mithalan Dress"});
    checks->push_back({1291, "collect_mutant_costume","collectible_mutant_costume",1, "Mutant costume",
                       "The Body bottom area, Mutant Costume"});
    checks->push_back({1292, "collect_seahorse_costume","collectible_seahorse_costume",1, "Arnassi Armor",
                       "Arnassi Ruins, Arnassi Armor"});
    checks->push_back({1293, "collect_teen_costume","collectible_teen_costume",1, "Girl costume",
                       "Sunken City left area, Girl Costume"});
    checks->push_back({1294, "collect_urchin_costume","collectible_urchin_costume",1, "Urchin costume",
                       "Turtle cave, Urchin Costume"});
    checks->push_back({1295, "collect_nautilus","collectible_nautilus",1, "Baby nautilus",
                       "Home Waters, Nautilus Egg"});
    checks->push_back({1296, "collect_blaster","collectible_blaster",1, "Baby blaster",
                       "Energy Temple blaster room, Blaster Egg"});
    checks->push_back({1297, "collect_dumbo","collectible_dumbo",1, "Baby dumbo",
                       "Octopus Cave, Dumbo Egg"});
    checks->push_back({1298, "collect_piranha","collectible_piranha",1, "Baby piranha",
                       "Mermog cave, Piranha Egg"});
    checks->push_back({1299, "urn_cathedral_r_13","ingredient_leafpoultice",3, "Leaf poultice",
                       "Mithalas Cathedral, urn below the left entrance"});
    checks->push_back({1300, "li_cave","song_li",1, "Li and Li song",
                       "The Veil top left area, In Li's cave"});
    checks->push_back({1301, "song_shield_hint","song_shield",1, "Shield song",
                       "Verse Cave left area, the Naija hint about the shield ability"});
    checks->push_back({1302, "breaking_li_cage","song_dual",1, "Dual Form",
                       "The Body center area, breaking Li's cage"});
    checks->push_back({1303, "beating_mithalas","song_beast",1, "Beast Form",
                       "Mithalas boss area, beating Mithalan God"});
    checks->push_back({1304, "beating_sun_god","song_sun",1, "Sun Form",
                       "Sun Temple boss area, beating Sun God"});
    checks->push_back({1305, "beating_drunian_god","song_nature",1, "Nature Form",
                       "Kelp Forest boss area, beating Drunian God"});
    checks->push_back({1306, "beating_energy_statue","song_energy",1, "Energy Form",
                       "Energy Temple first area, beating the Energy Statue"});
    checks->push_back({1307, "erulian_spirit","song_bind",1, "Bind song",
                       "Song Cave, Erulian spirit"});
    checks->push_back({1308, "fish_cave_puzzle","song_fish",1, "Fish form",
                       "Kelp Forest bottom left area, Fish Cave puzzle"});
    checks->push_back({1309, "beating_priests","song_spirit",1, "Spirit form",
                       "Mithalas City Castle, beating the Priests"});
    checks->push_back({1310, "transturtle_veil01","transport_veil01",1, "Transport to The Veil top left area",
                       "The Veil top left area, Transturtle"});
    checks->push_back({1311, "transturtle_veil02","transport_veil02",1, "Transport to The Veil top right area",
                       "The Veil top right area, Transturtle"});
    checks->push_back({1312, "transturtle_openwater03","transport_openwater03",1, "Transport to Open waters top right area",
                       "Open Waters top right area, Transturtle"});
    checks->push_back({1313, "transturtle_forest04","transport_forest04",1, "Transport to Kelp Forest bottom left area",
                       "Kelp Forest bottom left area, Transturtle"});
    checks->push_back({1314, "transturtle_mainarea","transport_mainarea",1, "Transport to home waters",
                       "Home Waters, Transturtle"});
    checks->push_back({1315, "transturtle_abyss03","transport_abyss03",1, "Transport to The Abyss right area",
                       "Abyss right area, Transturtle"});
    checks->push_back({1316, "transturtle_finalboss","transport_finalboss",1, "Transport to The Creator",
                       "Final Boss area, Transturtle"});
    checks->push_back({1317, "transturtle_forest05","transport_forest05",1, "Transport to Simon says",
                       "Simon Says area, Transturtle"});
    checks->push_back({1318, "transturtle_seahorse","transport_seahorse",1, "Transport to Arnassi Ruins right area",
                       "Arnassi Ruins, Transturtle"});



}


/**
 * Initialize `collectibles`
 */
void Randomizer::initialiseCollectibles() {
    collectibles->push_back({ FLAG_COLLECTIBLE_ANEMONESEED, "collectible_anemone", "anemone-seed"});
    collectibles->push_back({FLAG_COLLECTIBLE_ENERGYTEMPLE, "collectible_energy_temple", "energytemple"});
    collectibles->push_back({FLAG_COLLECTIBLE_ARNASSISTATUE, "collectible_arnassi_statue", "arnassi-statue"});
    collectibles->push_back({FLAG_COLLECTIBLE_BANNER, "collectible_mithalas_banner", "mithalas-banner"});
    collectibles->push_back({FLAG_COLLECTIBLE_BIOSEED, "collectible_bio_seed", "bio-seed"});
    collectibles->push_back({FLAG_COLLECTIBLE_BLACKPEARL, "collectible_blackpearl", "blackpearl"});
    collectibles->push_back({FLAG_COLLECTIBLE_CHEST, "collectible_treasure_chest", "treasure-chest"});
    collectibles->push_back({FLAG_COLLECTIBLE_ENERGYBOSS, "collectible_energy_boss", "energyboss"});
    collectibles->push_back({FLAG_COLLECTIBLE_ENERGYSTATUE, "collectible_energy_statue", "energystatue"});
    collectibles->push_back({FLAG_COLLECTIBLE_GEAR, "collectible_golden_gear", "golden-gear"});
    collectibles->push_back({FLAG_COLLECTIBLE_JELLYPLANT, "collectible_jelly_plant", "jellyplant"});
    collectibles->push_back({FLAG_COLLECTIBLE_MITHALADOLL, "collectible_mithala_doll", "mithala-doll"});
    collectibles->push_back({FLAG_COLLECTIBLE_MITHALASPOT, "collectible_mithalas_pot", "mithalaspot"});
    collectibles->push_back({FLAG_COLLECTIBLE_NAIJACAVE, "collectible_big_seed", "naijacave"});
    collectibles->push_back({FLAG_COLLECTIBLE_SEEDBAG, "collectible_seed_bag", "seed-bag"});
    collectibles->push_back({FLAG_COLLECTIBLE_SKULL, "collectible_skull", "skull"});
    collectibles->push_back({FLAG_COLLECTIBLE_SONGCAVE, "collectible_jelly_beacon", "songcave"});
    collectibles->push_back({FLAG_COLLECTIBLE_SPORESEED, "collectible_spore_seed", "sporeseed"});
    collectibles->push_back({FLAG_COLLECTIBLE_STARFISH, "collectible_gold_star", "goldstar"});
    collectibles->push_back({FLAG_COLLECTIBLE_STONEHEAD, "collectible_stone_head", "stonehead"});
    collectibles->push_back({FLAG_COLLECTIBLE_SUNKEY, "collectible_sun_key", "sun-key"});
    collectibles->push_back({FLAG_COLLECTIBLE_TRIDENTHEAD, "collectible_trident_head", "trident-head"});
    collectibles->push_back({FLAG_COLLECTIBLE_TURTLEEGG, "collectible_turtle_egg", "turtle-egg"});
    collectibles->push_back({FLAG_COLLECTIBLE_UPSIDEDOWNSEED, "collectible_upsidedown_seed", "upsidedownseed"});
    collectibles->push_back({FLAG_COLLECTIBLE_WALKERBABY, "collectible_walker", "walker-baby"});
    collectibles->push_back({FLAG_COLLECTIBLE_CRABCOSTUME, "collectible_crab_costume", "crabcostume"});
    collectibles->push_back({FLAG_COLLECTIBLE_JELLYCOSTUME, "collectible_jelly_costume", "jelly-costume"});
    collectibles->push_back({FLAG_COLLECTIBLE_MITHALANCOSTUME, "collectible_mithalan_costume", "mithalan-costume"});
    collectibles->push_back({FLAG_COLLECTIBLE_MUTANTCOSTUME, "collectible_mutant_costume", "mutant-costume"});
    collectibles->push_back({FLAG_COLLECTIBLE_SEAHORSECOSTUME, "collectible_seahorse_costume", "seahorse-costume"});
    collectibles->push_back({FLAG_COLLECTIBLE_TEENCOSTUME, "collectible_teen_costume", "teen-costume"});
    collectibles->push_back({FLAG_COLLECTIBLE_URCHINCOSTUME, "collectible_urchin_costume", "urchin-costume"});
    collectibles->push_back({FLAG_PET_NAUTILUS, "collectible_nautilus", "egg-nautilus"});
    collectibles->push_back({FLAG_PET_BLASTER, "collectible_blaster", "egg-blaster"});
    collectibles->push_back({FLAG_PET_DUMBO, "collectible_dumbo", "egg-dumbo"});
    collectibles->push_back({FLAG_PET_PIRANHA, "collectible_piranha", "egg-piranha"});
}

/**
 * Destructor of the object
 */
Randomizer::~Randomizer() {
    delete(ingredientReplacement);
    delete(checks);
    delete(ingredients);
    delete(collectibles);
    delete(nextMessages);
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
    std::ostringstream lFileNameStream;
    lFileNameStream << "collectibles/" << lCollectible->imageFile;
    dsq->game->pickupItemEffects(lFileNameStream.str());
    dsq->continuity.setFlag(lCollectible->flag, 1);
    if (lCollectible->flag == FLAG_PET_BLASTER) {
        if (dsq->continuity.getFlag(FLAG_COLLECTIBLE_BLASTER) != 1) {
            dsq->continuity.setFlag(FLAG_COLLECTIBLE_BLASTER, 1);
            dsq->game->setControlHint(dsq->continuity.stringBank.get(30), false, false,
                                      false, 6, "collectibles/egg-blaster");
        }
    } else if (lCollectible->flag == FLAG_PET_NAUTILUS) {
        if (dsq->continuity.getFlag(FLAG_COLLECTIBLE_NAUTILUS) != 1) {
            dsq->continuity.setFlag(FLAG_COLLECTIBLE_NAUTILUS, 1);
            dsq->game->setControlHint(dsq->continuity.stringBank.get(33), false, false,
                                      false, 6, "collectibles/egg-nautilus");
        }
    } else if (lCollectible->flag == FLAG_PET_DUMBO) {
        if (dsq->continuity.getFlag(FLAG_COLLECTIBLE_DUMBO) != 1) {
            dsq->continuity.setFlag(FLAG_COLLECTIBLE_DUMBO, 1);
            dsq->game->setControlHint(dsq->continuity.stringBank.get(32), false, false,
                                      false, 6, "collectibles/egg-dumbo");
        }
    } else if (lCollectible->flag == FLAG_PET_PIRANHA) {
        if (dsq->continuity.getFlag(FLAG_COLLECTIBLE_PIRANHA) != 1) {
            dsq->continuity.setFlag(FLAG_COLLECTIBLE_PIRANHA, 1);
            dsq->game->setControlHint(dsq->continuity.stringBank.get(31), false, false,
                                      false, 6, "collectibles/egg-piranha");
        }
    }
}

/**
 * Get a new song item to activate in the local game
 * @param aCheck The song check item to activate
 */
void Randomizer::receivingSong(check_t *aCheck) {
    int lSongType = 0;
    int lStrId = 0;
    if (aCheck->flag == 1300) { // Li song
        if (dsq->continuity.getFlag(FLAG_LI) == 0) {
            dsq->continuity.setFlag(FLAG_LI, 100);
            lSongType = SONG_LI;
            lStrId = 42;
            if (dsq->game->avatar) {
                dsq->game->li = dsq->game->createEntity("li", 0, Vector (dsq->game->avatar->position.x, dsq->game->avatar->position.y), 0,
                                                        false, "Li", ET_ENEMY, true);
            }
        }
    } else if (aCheck->flag == 1301) { // Shield song
        if (!dsq->continuity.hasSong(SONG_SHIELDAURA)) {
            lSongType = SONG_SHIELDAURA;
            lStrId = 35;
        }
    } else if (aCheck->flag == 1302) { // Dual song
        if (!dsq->continuity.hasSong(SONG_DUALFORM)) {
            lSongType = SONG_DUALFORM;
            lStrId = 43;
        }
    } else if (aCheck->flag == 1303) { // Beast song
        if (!dsq->continuity.hasSong(SONG_BEASTFORM)) {
            lSongType = SONG_BEASTFORM;
            lStrId = 38;
        }
    } else if (aCheck->flag == 1304) { // Sun song
        if (!dsq->continuity.hasSong(SONG_SUNFORM)) {
            lSongType = SONG_SUNFORM;
            lStrId = 41;
        }
    } else if (aCheck->flag == 1305) { // Nature song
        if (!dsq->continuity.hasSong(SONG_NATUREFORM)) {
            lSongType = SONG_NATUREFORM;
            lStrId = 40;
        }
    } else if (aCheck->flag == 1306) { // Energy song
        if (!dsq->continuity.hasSong(SONG_ENERGYFORM)) {
            lSongType = SONG_ENERGYFORM;
            lStrId = 37;
        }
    } else if (aCheck->flag == 1307) { // Bind song
        if (!dsq->continuity.hasSong(SONG_BIND)) {
            lSongType = SONG_BIND;
            lStrId = 36;
        }
    } else if (aCheck->flag == 1308) { // Fish song
        if (!dsq->continuity.hasSong(SONG_FISHFORM)) {
            lSongType = SONG_FISHFORM;
            lStrId = 39;
        }
    } else if (aCheck->flag == 1309) { // Fish song
        if (!dsq->continuity.hasSong(SONG_SPIRITFORM)) {
            lSongType = SONG_SPIRITFORM;
            lStrId = 44;
        }
    }
    if (lSongType != 0) {
        dsq->continuity.learnSong(lSongType);
        dsq->game->setControlHint(dsq->continuity.stringBank.get(lStrId), false, false,
                                  false, 8, "", false, lSongType);
        std::ostringstream lFileNameStream;
        lFileNameStream << "song/songslot-" << dsq->continuity.getSongSlotByType(lSongType);
        dsq->game->pickupItemEffects(lFileNameStream.str());
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
	    dsq->game->pickupItemEffects("gui/wok");
	} else if (aItem.compare(0, 14, "upgrade_health") == 0) {
		lMessageStream << "Upgrade: Health";
        if (dsq->game->avatar && dsq->game->avatar->health < 10) {
            dsq->continuity.upgradeHealth();
        }
	    dsq->game->pickupItemEffects("healthupgrade/whole");
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
        dsq->game->pickupItemEffects("gems/turtle");
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
 * Retreive the maximum number of the same ingredients that can be stacked on the ingredient inventory
 * @return The maximum number
 */
int Randomizer::getMaximumIngredientAmount() {
    return maximumIngredientAmount;
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
                std::string lRecipeName = aRecipe->names.at(j).name;
                std::string lIngredientName = ingredients->at(i).name;
                if (lRecipeName == lIngredientName) {
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
 * Get the recipe with a certain name.
 *
 * @param aName The name of the recipe to find
 * @return The recipe found.
 */
Recipe * Randomizer::getRecipe(const std::string &aName) {
    Recipe * lRecipe = nullptr;
    for (int i = 0; !lRecipe && i < dsq->continuity.recipes.size(); i = i + 1) {
        if (nocasecmp(dsq->continuity.recipes.at(i).result, aName)==0) {
            lRecipe = &(dsq->continuity.recipes.at(i));
        }
    }
    return lRecipe;
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
        Recipe * lRecipe = getRecipe(lIngredientData->name);
        if (lRecipe) {
            if (lRecipe->isKnown()) {
                lResult = dsq->game->spawnIngredient(lIngredientData->name, aPosition, aTimes, aOut);
            } else {
                lResult = spawnRecipe(lRecipe, aPosition, aTimes, aOut);
            }
        } else {
            debugLog("The recipe " + lIngredientData->name + " does not exists\n");
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
        Recipe * lRecipe = getRecipe(lIngredientData->name);
        if (lRecipe) {
            if (lRecipe->isKnown()) {
                dsq->game->spawnIngredientFromEntityRandomized(aEntity,lIngredientData);
            } else {
                spawnRecipeFromEntity(aEntity,lRecipe, lIngredientData);
            }
        } else {
            debugLog("The recipe " + lIngredientData->name + " does not exists\n");
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
 * Remove pending error
 */
void Randomizer::clearError() {
    error = false;
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
 * Is the Goal's requirement be hidden from the player?
 * @param value The value to assign to `blindGoal`
 */
void Randomizer::setBlindGoal(bool value) {
    blindGoal = value;
}

/**
 * Is the Goal's requirement be hidden from the player?
 * @return The value to assign to `blindGoal`
 */
bool Randomizer::getBlindGoal() {
    return blindGoal;
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
     * Write the `text` to `messageStream` and put a check if `flag` is true
     *
     * @param aMessageStream The stream to write the text
     * @param aText the text to write
     * @param aFlag write a check if true
     */
void Randomizer::writeHelpData(std::stringstream *aMessageStream, std::string aText, int aFlag){
    if (aFlag) {
        *aMessageStream << "[X] ";
    } else {
        *aMessageStream << "[ ] ";
    }
    *aMessageStream << aText;
    *aMessageStream << "\n";
}

/**
 * Add information about receiving important item in `data`.
 *
 * @param aData Where the information about item should be put.
 */
void Randomizer::appendItemHelpData(std::string &aData) {
    std::stringstream lMessageStream;
    lMessageStream << "[Progression item obtained]\n";
    writeHelpData(&lMessageStream, "Bind song", dsq->continuity.hasSong(SONG_BIND));
    writeHelpData(&lMessageStream, "Shield song", dsq->continuity.hasSong(SONG_SHIELDAURA));
    writeHelpData(&lMessageStream, "Energy form", dsq->continuity.hasSong(SONG_ENERGYFORM));
    writeHelpData(&lMessageStream, "Nature form", dsq->continuity.hasSong(SONG_NATUREFORM));
    writeHelpData(&lMessageStream, "Beast form", dsq->continuity.hasSong(SONG_BEASTFORM));
    writeHelpData(&lMessageStream, "Sun form", dsq->continuity.hasSong(SONG_SUNFORM));
    writeHelpData(&lMessageStream, "Fish form", dsq->continuity.hasSong(SONG_FISHFORM));
    writeHelpData(&lMessageStream, "Spirit form", dsq->continuity.hasSong(SONG_SPIRITFORM));
    writeHelpData(&lMessageStream, "Dual form", dsq->continuity.hasSong(SONG_DUALFORM));
    writeHelpData(&lMessageStream, "Li and Li song", dsq->continuity.hasSong(SONG_LI));
    Recipe *lRecipe = getRecipe("hotsoup");
    writeHelpData(&lMessageStream, "Hot soup", lRecipe && lRecipe->isKnown());
    writeHelpData(&lMessageStream, "Arnassi Armor", dsq->continuity.getFlag(FLAG_COLLECTIBLE_SEAHORSECOSTUME));
    writeHelpData(&lMessageStream, "Transport to The Veil top left area", dsq->continuity.getFlag(FLAG_TRANSTURTLE_VEIL01));
    writeHelpData(&lMessageStream, "Transport to The Veil top right area", dsq->continuity.getFlag(FLAG_TRANSTURTLE_VEIL02));
    writeHelpData(&lMessageStream, "Transport to Open waters top right area", dsq->continuity.getFlag(FLAG_TRANSTURTLE_OPENWATER03));
    writeHelpData(&lMessageStream, "Transport to Kelp Forest bottom left area", dsq->continuity.getFlag(FLAG_TRANSTURTLE_FOREST04));
    writeHelpData(&lMessageStream, "Transport to home waters", dsq->continuity.getFlag(FLAG_TRANSTURTLE_MAINAREA));
    writeHelpData(&lMessageStream, "Transport to The Abyss right area", dsq->continuity.getFlag(FLAG_TRANSTURTLE_ABYSS03));
    writeHelpData(&lMessageStream, "Transport to The Creator", dsq->continuity.getFlag(FLAG_TRANSTURTLE_FINALBOSS));
    writeHelpData(&lMessageStream, "Transport to Simon says", dsq->continuity.getFlag(FLAG_TRANSTURTLE_FOREST05));
    writeHelpData(&lMessageStream, "Transport to Arnassi Ruins right area", dsq->continuity.getFlag(FLAG_TRANSTURTLE_SEAHORSE));

    lMessageStream << "\n";
    aData += lMessageStream.str();
}

/**
 * Add information about mini bosses beaten in `data`.
 *
 * @param aData Where the information about item should be put.
 */
void Randomizer::appendMiniBossHelpData(std::string &aData) {
    std::stringstream lMessageStream;
    lMessageStream << "[Mini bosses beaten]\n";
    writeHelpData(&lMessageStream, "Nautilus Prime", dsq->continuity.getFlag(FLAG_MINIBOSS_NAUTILUSPRIME));
    writeHelpData(&lMessageStream, "King Jelly Prime", dsq->continuity.getFlag(FLAG_MINIBOSS_KINGJELLY));
    writeHelpData(&lMessageStream, "Mergog", dsq->continuity.getFlag(FLAG_MINIBOSS_MERGOG));
    writeHelpData(&lMessageStream, "Crabbius Maximus", dsq->continuity.getFlag(FLAG_MINIBOSS_CRAB));
    writeHelpData(&lMessageStream, "Octopus Prime", dsq->continuity.getFlag(FLAG_MINIBOSS_OCTOMUN));
    writeHelpData(&lMessageStream, "Mantis Shrimp", dsq->continuity.getFlag(FLAG_MINIBOSS_MANTISSHRIMP));
    writeHelpData(&lMessageStream, "Mithalan Priests", dsq->continuity.getFlag(FLAG_MINIBOSS_PRIESTS));
    writeHelpData(&lMessageStream, "Blaster Peg Prime", dsq->continuity.getFlag(FLAG_MINIBOSS_BLASTER));

    lMessageStream << "\n";
    if (dsq->continuity.getFlag(FLAG_BLIND_GOAL) == 0) {
        if (miniBossesToKill > 1) {
            lMessageStream << miniBossesToKill << " mini bosses beaten are needed to access final boss.\n\n\n";
        } else if (miniBossesToKill == 1) {
            lMessageStream << "1 mini boss beaten are needed to access final boss.\n\n\n";
        } else {
            lMessageStream << "No mini boss beaten are needed to access final boss.\n\n\n";
        }
    }

    aData += lMessageStream.str();
}

/**
 * Add information about big bosses beaten in `data`.
 *
 * @param aData Where the information about item should be put.
 */
void Randomizer::appendBigBossHelpData(std::string &aData) {
    std::stringstream lMessageStream;
    lMessageStream << "[Bosses beaten]\n";
    writeHelpData(&lMessageStream, "Fallen God", dsq->continuity.getFlag(FLAG_ENERGYBOSSDEAD));
    writeHelpData(&lMessageStream, "Mithalan God", dsq->continuity.getFlag(FLAG_BOSS_MITHALA));
    writeHelpData(&lMessageStream, "Drunian God", dsq->continuity.getFlag(FLAG_BOSS_FOREST));
    writeHelpData(&lMessageStream, "Sun God", dsq->continuity.getFlag(FLAG_BOSS_SUNWORM));
    writeHelpData(&lMessageStream, "Golem", dsq->continuity.getFlag(FLAG_SUNKENCITY_BOSS));

    lMessageStream << "\n";
    if (dsq->continuity.getFlag(FLAG_BLIND_GOAL) == 0) {
        if (bigBossesToKill > 1) {
            lMessageStream << bigBossesToKill << " big bosses beaten are needed to access final boss.\n\n\n";
        } else if (bigBossesToKill == 1) {
            lMessageStream << "1 big boss beaten are needed to access final boss.\n\n\n";
        } else {
            lMessageStream << "No big boss beaten are needed to access final boss.\n\n\n";
        }
    }

    aData += lMessageStream.str();
}

/**
 * Add information about secrets obtained in `data`.
 *
 * @param aData Where the information about item should be put.
 */
void Randomizer::appendSecretHelpData(std::string &aData) {

    std::stringstream lMessageStream;
    lMessageStream << "[Secrets obtained]\n";
    writeHelpData(&lMessageStream, "First secret", dsq->continuity.getFlag(FLAG_SECRET01));
    writeHelpData(&lMessageStream, "Second secret", dsq->continuity.getFlag(FLAG_SECRET02));
    writeHelpData(&lMessageStream, "Third Secret", dsq->continuity.getFlag(FLAG_SECRET03));

    lMessageStream << "\n";
    if (dsq->continuity.getFlag(FLAG_BLIND_GOAL) == 0) {
        if (secretsNeeded) {
            lMessageStream << "Secrets are needed to access final boss.\n\n\n";
        } else {
            lMessageStream << "Secrets are not needed to access final boss.\n\n\n";
        }
    }

    aData += lMessageStream.str();
}

/**
 * Add information about locations in `data`.
 *
 * @param aData Where the information about item should be put.
 */
void Randomizer::appendLocationsHelpData(std::string &aData) {
    const int order[218] = {107, 108, 175, 200, 21, 22, 23, 58, 59, 60, 61, 62, 63, 64, 65, 194, 213, 119, 120,
                            206, 71, 72, 73, 74, 75, 160, 178, 162, 205, 27, 170, 28, 163, 29, 169, 195, 1, 2, 3, 4, 5,
                            6, 7, 8, 148, 149, 150, 9, 211, 11, 10, 12, 13, 177, 14, 15, 16, 179, 191, 164, 217, 187,
                            156, 216, 30, 35, 31, 33, 34, 41, 37, 38, 39, 123, 124, 125, 126, 127, 32, 40, 36, 174,
                            128, 173, 129, 42, 165, 130, 131, 132, 133, 134, 135, 208, 183, 136, 137, 138, 139, 140,
                            141, 142, 143, 144, 145, 146, 147, 189, 198, 113, 114, 115, 116, 117, 118, 202, 44, 45, 46,
                            185, 47, 158, 48, 49, 51, 52, 53, 167, 50, 54, 186, 212, 168, 204, 55, 207, 56, 57, 176,
                            121, 197, 199, 78, 76, 209, 77, 184, 0, 193, 79, 180, 80, 210, 82, 81, 157, 181, 196, 122,
                            94, 95, 96, 171, 91, 92, 93, 182, 17, 18, 19, 20, 203, 24, 25, 166, 172, 26, 109, 110, 111,
                            112, 214, 83, 84, 85, 86, 87, 89, 90, 161, 88, 188, 159, 154, 155, 151, 152, 153, 192, 43,
                            201, 97, 66, 69, 67, 68, 70, 100, 98, 99, 101, 102, 190, 103, 104, 105, 215, 106};
    std::stringstream lMessageStream;
    lMessageStream << "[Locations obtained]\n";
    for (int i = 0; i < 218; i = i + 1) {
        writeHelpData(&lMessageStream, checks->at(order[i]).location,
                      dsq->continuity.getFlag(checks->at(order[i]).flag));
    }
    lMessageStream << "\n\n";
    aData += lMessageStream.str();
}



/**
 * A now or saves game has been load
   @param aNewGame True if a new game is launched.
 */
void Randomizer::onLoad(bool aNewGame){
    if (aNewGame) {
        if (blindGoal) {
            dsq->continuity.setFlag(FLAG_BLIND_GOAL, 1);
        } else {
            dsq->continuity.setFlag(FLAG_BLIND_GOAL, 0);
        }
    } else {
        dsq->toggleCursor(true);
        if (dsq->continuity.getFlag(FLAG_ENTER_HOMECAVE) == 0) {
            if (dsq->confirm("Restart at Naija's rock?","", false, 3.0)) {
                dsq->game->sceneToLoad = "naijacave";
                dsq->game->positionToAvatar = Vector(8880, 3881);
            }
        } else {
            if (dsq->confirm("Restart at Naija's home?","", false, 3.0)) {
                dsq->game->sceneToLoad = "vedhacave";
                dsq->game->positionToAvatar = Vector(1743, 2888);
            }
        }
        dsq->toggleCursor(false);
    }
    dsq->continuity.setFlag(FLAG_ENERGYSLOT_FIRST, 15);
    if (skipFirstVision) {
        dsq->continuity.setFlag(FLAG_VISION_ENERGYTEMPLE, 1);
    }
    if (unconfine_home_water_transturtle) {
        dsq->continuity.setFlag(FLAG_MAINAREA_TRANSTURTLE_ROCK, 1);
    }
    if (unconfine_home_water_energy_door) {
        dsq->continuity.setFlag(FLAG_ENERGYSLOT_MAINAREA, 29);
    }
    inGame = true;
}

/**
 * When a game is quitting.
 */
void Randomizer::onClose() {
    inGame = false;
}


/**
 * Lunched at each game loop iteration
 */
void Randomizer::update(){
    auto lNow = std::chrono::system_clock::now();
    if (currentMessageTime) {
        auto lTime = std::chrono::system_clock::from_time_t (currentMessageTime);
        auto lDuration = std::chrono::duration_cast<std::chrono::seconds>(lNow - lTime);
        if (lDuration.count() > 9) {
            currentMessageTime = 0;
            if (!nextMessages->empty()) {
                randomessage_t lMessage = nextMessages->front();
                nextMessages->pop();
                showText(lMessage.text, lMessage.x, lMessage.y);
            }
        }
    }
    if (infiniteHotSoup) {
        Recipe * lHotSoup = getRecipe("hotsoup");
        if (lHotSoup && lHotSoup->isKnown()) {
            IngredientData * lIngredient = dsq->continuity.getIngredientDataByName("hotsoup");
            if (lIngredient && lIngredient->amount < 1) {
                dsq->continuity.pickupIngredient(lIngredient, 1, false, false);
            }
        }
    }
}

/**
 * True when the game should skip the final boss 3rd form (hide and seek)
 */
bool Randomizer::mustSkipFinalBoss3rdForm() {
    return skipFinalBoss3rdForm;
}

/**
 * Tne number of mini bosses that as been slain.
 *
 * @return the number of mini bosses that as been beaten by the player
 */
int Randomizer::miniBossCount() {
    int lMiniBosses = 0;
    for (int i = FLAG_MINIBOSS_START; i <= FLAG_MINIBOSS_END; i = i + 1) {
        if (dsq->continuity.getFlag(i) > 0) {
            lMiniBosses = lMiniBosses + 1;
        }
    }
    return lMiniBosses;
}

/**
 * Tne number of big bosses that as been slain.
 *
 * @return the number of big bosses that as been beaten by the player
 */
int Randomizer::bigBossCount() {
    int lBigBosses = 0;
    if (dsq->continuity.getFlag(FLAG_ENERGYBOSSDEAD) > 0) {
        lBigBosses = lBigBosses + 1;
    }
    if (dsq->continuity.getFlag(FLAG_SUNKENCITY_BOSS) > 0) {
        lBigBosses = lBigBosses + 1;
    }
    if (dsq->continuity.getFlag(FLAG_BOSS_FOREST) > 0) {
        lBigBosses = lBigBosses + 1;
    }
    if (dsq->continuity.getFlag(FLAG_BOSS_MITHALA) > 0) {
        lBigBosses = lBigBosses + 1;
    }
    if (dsq->continuity.getFlag(FLAG_BOSS_SUNWORM) > 0) {
        lBigBosses = lBigBosses + 1;
    }
    return lBigBosses;
}

/**
 * Tne number of secrets that has been found.
 *
 * @return the number of secrets founded by the player
 */
int Randomizer::secretsFound() {
    int lSecretsCount = 0;
    if (dsq->continuity.getFlag(FLAG_SECRET01) != 0) {
        lSecretsCount = lSecretsCount + 1;
    }
    if (dsq->continuity.getFlag(FLAG_SECRET02) != 0) {
        lSecretsCount = lSecretsCount + 1;
    }
    if (dsq->continuity.getFlag(FLAG_SECRET03) != 0) {
        lSecretsCount = lSecretsCount + 1;
    }
    return lSecretsCount;
}


/**
 * Is the final boss is accessible.
 * @return True if the final boss is accessible. False if not.
 */
bool Randomizer::accessFinalBoss() {
    return dsq->continuity.hasLi() and dsq->continuity.hasSong(SONG_DUALFORM) and
           dsq->continuity.hasSong(SONG_ENERGYFORM) and dsq->continuity.hasSong(SONG_SUNFORM)
           and dsq->continuity.hasSong(SONG_BIND) and miniBossCount() >= miniBossesToKill and
           bigBossCount() >= bigBossesToKill and (!secretsNeeded || (secretsFound() == 3));
}

void Randomizer::showHint(int aCount, int aObjective, const std::string& aMessage) {
    if (aCount < aObjective) {
        std::stringstream lMessageStream;
        lMessageStream << "You have " << aCount << " " << aMessage << ". Needing " << aObjective <<
                            " to access final boss.";
        showText(lMessageStream.str());
    }
}

/**
 * Show what is missing to access final boss.
 */
void Randomizer::showHintFinalBoss() {
    if (!dsq->continuity.hasLi()) {
        showText("Li needed to access final boss..");
    }
    if (!dsq->continuity.hasSong(SONG_BIND)) {
        showText("Bind song needed to access final boss..");
    }
    if (!dsq->continuity.hasSong(SONG_ENERGYFORM)) {
        showText("Energy form needed to access final boss..");
    }
    if (!dsq->continuity.hasSong(SONG_SUNFORM)) {
        showText("Sun form needed to access final boss..");
    }
    if (!dsq->continuity.hasSong(SONG_DUALFORM)) {
        showText("Dual form needed to access final boss..");
    }
    showHint(miniBossCount(), miniBossesToKill, "mini bosses beaten");
    showHint(bigBossCount(), bigBossesToKill, "big bosses beaten");
    if (secretsNeeded) {
        showHint(secretsFound(), 3, "secret memories founded");
    }
    dsq->continuity.setFlag(FLAG_BLIND_GOAL, 0);
}


/**
 * The number of messages that need to be shown to screen.
 *
 * @return The size of the nextMessages queue.
 */
unsigned long Randomizer::nextMessagesSize() {
    return nextMessages->size();
}

/**
 * Show a text in game at a certain position (with (x,y) between (0,0) and (800,600))
 * @param aText The text to show in game
 * @param aX The horizontal coordinate of the top corner of the text to show
 * @param aX The vertical coordinate of the top corner of the text to show
 */
void Randomizer::showText(const std::string &aText, float aX, float aY)
{
    if (currentMessageTime) {
        nextMessages->push({aText, aX, aY});
    } else {
        auto lNow = std::chrono::system_clock::now();
        std::time_t currentTime = std::chrono::system_clock::to_time_t(lNow);
        currentMessageTime = currentTime;
        Vector pos(aX,aY);
        float time = 8;

        BitmapText *s = new BitmapText(&(dsq->smallFont));
        s->setAlign(ALIGN_LEFT);
        s->setWidth(700.0);
        s->color = Vector(0,0,0);
        s->position = pos;
        s->offset = Vector(1,1);
        s->setText(aText);
        s->setLife(time + 0.5f);
        s->setDecayRate(1);
        s->followCamera = 1;
        s->alpha.ensureData();
        s->alpha.data->path.addPathNode(0, 0);
        s->alpha.data->path.addPathNode(1, 0.1);
        s->alpha.data->path.addPathNode(1, 0.8);
        s->alpha.data->path.addPathNode(0, 1);
        s->alpha.startPath(time);
        dsq->getTopStateData()->addRenderObject(s, LR_HUD);


        BitmapText *t = new BitmapText(&(dsq->smallFont));

        t->position =pos;
        t->setAlign(ALIGN_LEFT);
        t->setWidth(700.0);
        t->alpha.ensureData();
        t->alpha.data->path.addPathNode(0, 0);
        t->alpha.data->path.addPathNode(1, 0.1);
        t->alpha.data->path.addPathNode(1, 0.8);
        t->alpha.data->path.addPathNode(0, 1);
        t->alpha.startPath(time);
        t->followCamera = 1;
        t->setLife(time + 0.5f);
        t->setDecayRate(1);
        //t->scrollText(text, 0.1);
        t->setText(aText);
        dsq->getTopStateData()->addRenderObject(t, LR_HUD);
    }
}

/**
 * Event for the Transportation menu to cancel the process.
 */
void Randomizer::onCancelTransportation() {
	transporatationDone = true;
}

/**
 * Event for the Transportation menu to manage the Naija's home destination.
 */
void Randomizer::onNaijaHomeTransportation() {
	transportationSelected = FLAG_TRANSTURTLE_NAIJAHOME;
	if (dsq->confirm("Go to Naija's home?","", false, 0.0)) {
		transporatationDone = true;
	}
}

/**
 * Event for the Transportation menu to manage the Naija's rock destination
 */
void Randomizer::onNaijaRockTransportation() {
	transportationSelected = FLAG_TRANSTURTLE_NAIJAROCK;
	if (dsq->confirm("Go to Naija's rock?","", false, 0.0)) {
		transporatationDone = true;
	}
}

/**
 * Event for the Transportation menu to manage the Veil left area destination
 */
void Randomizer::onVeil1Transportation() {
	transportationSelected = FLAG_TRANSTURTLE_VEIL01;
	if (dsq->confirm("Go to the Veil left area?","", false, 0.0)) {
		transporatationDone = true;
	}
}

/**
 * Event for the Transportation menu to manage the Veil right area destination
 */
void Randomizer::onVeil2Transportation() {
	transportationSelected = FLAG_TRANSTURTLE_VEIL02;
	if (dsq->confirm("Go to the Veil right area?","", false, 0.0)) {
		transporatationDone = true;
	}
}

/**
 * Event for the Transportation menu to manage the Arnassi Ruins destination
 */
void Randomizer::onArnassiTransportation() {
	transportationSelected = FLAG_TRANSTURTLE_SEAHORSE;
	if (dsq->confirm("Go to Arnassi Ruins?","", false, 0.0)) {
		transporatationDone = true;
	}
}

/**
 * Event for the Transportation menu to manage the Kelp Forest destination
 */
void Randomizer::onForestTransportation() {
	transportationSelected = FLAG_TRANSTURTLE_FOREST04;
	if (dsq->confirm("Go to Kelp Forest?","", false, 0.0)) {
		transporatationDone = true;
	}
}

/**
 * Event for the Transportation menu to manage the Simon says destination
 */
void Randomizer::onSimonTransportation() {
	transportationSelected = FLAG_TRANSTURTLE_FOREST05;
	if (dsq->confirm("Go to Simon Says?","", false, 0.0)) {
		transporatationDone = true;
	}
}

/**
 * Event for the Transportation menu to manage the Abyss destination
 */
void Randomizer::onAbyssTransportation() {
	transportationSelected = FLAG_TRANSTURTLE_ABYSS03;
	if (dsq->confirm("Go to the Abyss?","", false, 0.0)) {
		transporatationDone = true;
	}
}

/**
 * Event for the Transportation menu to manage the Body destination
 */
void Randomizer::onBodyTransportation() {
	transportationSelected = FLAG_TRANSTURTLE_FINALBOSS;
	if (dsq->confirm("Go to the Body?","", false, 0.0)) {
		transporatationDone = true;
	}
}

/**
 * Event for the Transportation menu to manage the Open Waters destination
 */
void Randomizer::onOpenWaterTransportation() {
    transportationSelected = FLAG_TRANSTURTLE_OPENWATER03;
	if (dsq->confirm("Go to Open Waters?","", false, 0.0)) {
		transporatationDone = true;
	}
}

/**
 * Event for the Transportation menu to manage the Home Waters destination
 */
void Randomizer::onHomeWaterTransportation() {
    transportationSelected = FLAG_TRANSTURTLE_MAINAREA;
	if (dsq->confirm("Go to Home Waters?","", false, 0.0)) {
		transporatationDone = true;
	}
}

/**
 * Setup a menu item and a label for an option of the transportation menu
 *
 * @param aItem The menu item
 * @param aItemLabel The menu item label
 * @param aIcon The icon to show on the `aItem`
 * @param aX The horizontal position of the menu item
 * @param aY The vertical position of the menu item
 * @param aText The text to put on the `aItemLabel`
 */
void Randomizer::setupTransportationItem(AquariaMenuItem *aItem, BitmapText *aItemLabel, const std::string& aIcon,
                                         float aX, float aY, const std::string& aText) {
	aItem->useQuad(aIcon);
	aItem->useSound("click");
	aItem->useGlow("particles/glow", 64, 64);
	aItem->position = Vector(aX, aY);
	aItem->followCamera = 1;
	aItem->scale = Vector(2.0, 2.0);
	aItem->guiInputLevel = GUILEVEL_TRANSPORT;
    aItem->setCanDirMove(true);
	dsq->game->addRenderObject(aItem, LR_TRANSPORT);

	aItemLabel->color = 0;
	aItemLabel->setText(aText);
	aItemLabel->color = 0;
	aItemLabel->followCamera = 1;
	aItemLabel->position = Vector(aX, aY + 30);
	aItemLabel->scale = Vector(1.0, 1.0);
	game->addRenderObject(aItemLabel, LR_TRANSPORT);
}

/**
 * When the user pressed escape.
 */
void Randomizer::onPressEscape() {
    onCancelTransportation();
}

/**
 * Show the transportation menu and return the selected destination flag.
 *
 * @return the selected destination flag
 */
int Randomizer::askTransportation() {
	transportationSelected = 0;
	if (!game->isSceneEditorActive() && !core->getShiftState() && !dsq->screenTransition->isGoing() && !dsq->isNested() &&
		dsq->saveSlotMode == SSM_NONE) {
	    transporatationDone = false;
	    dsq->game->togglePause(true);
	    sound->playSfx("menu-open");
	    Quad *bgimage = new Quad("gui/recipe-scroll.png", Vector(400,300));
	    bgimage->followCamera = 1;
	    bgimage->alpha = 0;
	    bgimage->alpha.interpolateTo(1, 0.5);
	    //bgLabel->setWidthHeight(512*0.9f, 256*0.9f);
	    bgimage->scale = Vector(0, 0);
	    bgimage->scale.interpolateTo(Vector(1.5,1), 0.5);
	    game->addRenderObject(bgimage, LR_TRANSPORT);
	    dsq->main(0.5);

	    BitmapText *lTitle = new BitmapText(&dsq->font);
	    lTitle->color = 0;
	    lTitle->setFontSize(50);
	    lTitle->followCamera = 1;
	    lTitle->position = Vector(400,75);
	    lTitle->setText("Transportation turtle\nDestinations");
	    lTitle->scale = Vector(1.0, 1.0);
	    game->addRenderObject(lTitle, LR_TRANSPORT);

	    float lVerticalPosition = 200.0;
	    float lHorizontalPosition = 175.0;
	    bool lFirst = true;

		AquariaMenuItem *menuCancel = new AquariaMenuItem;

	    AquariaMenuItem *lHomeWater = new AquariaMenuItem;
	    BitmapText *lHomeWaterText = new BitmapText(&dsq->smallFont);
	    if (dsq->continuity.getFlag(FLAG_TRANSTURTLE_MAINAREA)) {
	        setupTransportationItem(lHomeWater, lHomeWaterText, "gems/turtle", lHorizontalPosition,
                            lVerticalPosition, "Home Waters");
	        lHomeWater->event.set(MakeFunctionEvent(Randomizer,onHomeWaterTransportation));
            if (lFirst) {
	            lHomeWater->setDirMove(DIR_LEFT, menuCancel);
                menuCancel->setDirMove(DIR_RIGHT, lHomeWater);
                lHomeWater->setFocus(true);
                lFirst = false;
            }
	        if (lHorizontalPosition > 500) {
	            lHorizontalPosition = 175.0;
	            lVerticalPosition = lVerticalPosition + 100.0;
	        } else {
	            lHorizontalPosition = lHorizontalPosition + 150;
	        }
	    } else {
	        lHomeWater->setCanDirMove(false);
	    }

	    AquariaMenuItem *lOpenWater = new AquariaMenuItem;
	    BitmapText *lOpenWaterText = new BitmapText(&dsq->smallFont);
	    if (dsq->continuity.getFlag(FLAG_TRANSTURTLE_OPENWATER03)) {
	        setupTransportationItem(lOpenWater, lOpenWaterText, "gems/turtle", lHorizontalPosition,
                            lVerticalPosition, "Open Waters");
	        lOpenWater->event.set(MakeFunctionEvent(Randomizer,onOpenWaterTransportation));
	        if (lFirst) {
	            lOpenWater->setDirMove(DIR_LEFT, menuCancel);
                menuCancel->setDirMove(DIR_RIGHT, lOpenWater);
	            lOpenWater->setFocus(true);
	            lFirst = false;
	        }
	        if (lHorizontalPosition > 500) {
	            lHorizontalPosition = 175.0;
	            lVerticalPosition = lVerticalPosition + 100.0;
	        } else {
	            lHorizontalPosition = lHorizontalPosition + 150;
	        }
	    } else {
	        lOpenWater->setCanDirMove(false);
	    }

	    AquariaMenuItem *lForest = new AquariaMenuItem;
	    BitmapText *lForestText = new BitmapText(&dsq->smallFont);
	    if (dsq->continuity.getFlag(FLAG_TRANSTURTLE_FOREST04)) {
	        setupTransportationItem(lForest, lForestText, "gems/turtle", lHorizontalPosition,
                            lVerticalPosition, "Kelp Forest");
	        lForest->event.set(MakeFunctionEvent(Randomizer,onForestTransportation));
	        if (lFirst) {
	            lForest->setDirMove(DIR_LEFT, menuCancel);
                menuCancel->setDirMove(DIR_RIGHT, lForest);
	            lForest->setFocus(true);
	            lFirst = false;
	        }
	        if (lHorizontalPosition > 500) {
	            lHorizontalPosition = 175.0;
	            lVerticalPosition = lVerticalPosition + 100.0;
	        } else {
	            lHorizontalPosition = lHorizontalPosition + 150;
	        }
	    } else {
	        lForest->setCanDirMove(false);
	    }

	    AquariaMenuItem *lVeil1 = new AquariaMenuItem;
	    BitmapText *lVeil1Text = new BitmapText(&dsq->smallFont);
	    if (dsq->continuity.getFlag(FLAG_TRANSTURTLE_VEIL01)) {
	        setupTransportationItem(lVeil1, lVeil1Text, "gems/turtle", lHorizontalPosition,
                            lVerticalPosition, "Left Veil");
	        lVeil1->event.set(MakeFunctionEvent(Randomizer,onVeil1Transportation));
	        if (lFirst) {
	            lVeil1->setDirMove(DIR_LEFT, menuCancel);
                menuCancel->setDirMove(DIR_RIGHT, lVeil1);
	            lVeil1->setFocus(true);
	            lFirst = false;
	        }
	        if (lHorizontalPosition > 500) {
	            lHorizontalPosition = 175.0;
	            lVerticalPosition = lVerticalPosition + 100.0;
	        } else {
	            lHorizontalPosition = lHorizontalPosition + 150;
	        }
	    } else {
	        lVeil1->setCanDirMove(false);
	    }

	    AquariaMenuItem *lVeil2 = new AquariaMenuItem;
	    BitmapText *lVeil2Text = new BitmapText(&dsq->smallFont);
	    if (dsq->continuity.getFlag(FLAG_TRANSTURTLE_VEIL02)) {
	        setupTransportationItem(lVeil2, lVeil2Text, "gems/turtle", lHorizontalPosition,
                            lVerticalPosition, "Right Veil");
	        lVeil2->event.set(MakeFunctionEvent(Randomizer,onVeil2Transportation));
	        if (lFirst) {
	            lVeil2->setDirMove(DIR_LEFT, menuCancel);
                menuCancel->setDirMove(DIR_RIGHT, lVeil2);
	            lVeil2->setFocus(true);
	            lFirst = false;
	        }
	        if (lHorizontalPosition > 500) {
	            lHorizontalPosition = 175.0;
	            lVerticalPosition = lVerticalPosition + 100.0;
	        } else {
	            lHorizontalPosition = lHorizontalPosition + 150;
	        }
	    } else {
	        lVeil2->setCanDirMove(false);
	    }

	    AquariaMenuItem *lArnassi = new AquariaMenuItem;
	    BitmapText *lArnassiText = new BitmapText(&dsq->smallFont);
	    if (dsq->continuity.getFlag(FLAG_TRANSTURTLE_SEAHORSE)) {
	        setupTransportationItem(lArnassi, lArnassiText, "gems/turtle", lHorizontalPosition,
                            lVerticalPosition, "Arnassi Ruins");
	        lArnassi->event.set(MakeFunctionEvent(Randomizer,onArnassiTransportation));
	        if (lFirst) {
	            lArnassi->setDirMove(DIR_LEFT, menuCancel);
                menuCancel->setDirMove(DIR_RIGHT, lArnassi);
	            lArnassi->setFocus(true);
	            lFirst = false;
	        }
	        if (lHorizontalPosition > 500) {
	            lHorizontalPosition = 175.0;
	            lVerticalPosition = lVerticalPosition + 100.0;
	        } else {
	            lHorizontalPosition = lHorizontalPosition + 150;
	        }
	    } else {
	        lArnassi->setCanDirMove(false);
	    }

	    AquariaMenuItem *lAbyss = new AquariaMenuItem;
	    BitmapText *lAbyssText = new BitmapText(&dsq->smallFont);
	    if (dsq->continuity.getFlag(FLAG_TRANSTURTLE_ABYSS03)) {
	        setupTransportationItem(lAbyss, lAbyssText, "gems/turtle", lHorizontalPosition,
                            lVerticalPosition, "Abyss");
	        lAbyss->event.set(MakeFunctionEvent(Randomizer,onAbyssTransportation));
	        if (lFirst) {
	            lAbyss->setDirMove(DIR_LEFT, menuCancel);
                menuCancel->setDirMove(DIR_RIGHT, lAbyss);
	            lAbyss->setFocus(true);
	            lFirst = false;
	        }
	        if (lHorizontalPosition > 500) {
	            lHorizontalPosition = 175.0;
	            lVerticalPosition = lVerticalPosition + 100.0;
	        } else {
	            lHorizontalPosition = lHorizontalPosition + 150;
	        }
	    } else {
	        lAbyss->setCanDirMove(false);
	    }

	    AquariaMenuItem *lBody = new AquariaMenuItem;
	    BitmapText *lBodyText = new BitmapText(&dsq->smallFont);
	    if (dsq->continuity.getFlag(FLAG_TRANSTURTLE_FINALBOSS)) {
	        setupTransportationItem(lBody, lBodyText, "gems/turtle", lHorizontalPosition,
                            lVerticalPosition, "Body");
	        lBody->event.set(MakeFunctionEvent(Randomizer,onBodyTransportation));
	        if (lFirst) {
	            lBody->setDirMove(DIR_LEFT, menuCancel);
                menuCancel->setDirMove(DIR_RIGHT, lBody);
	            lBody->setFocus(true);
	            lFirst = false;
	        }
	        if (lHorizontalPosition > 500) {
	            lHorizontalPosition = 175.0;
	            lVerticalPosition = lVerticalPosition + 100.0;
	            if (lVerticalPosition > 350) {
	                lHorizontalPosition = 325.0;
	            }
	        } else {
	            lHorizontalPosition = lHorizontalPosition + 150;
	        }
	    } else {
	        lBody->setCanDirMove(false);
	    }

	    AquariaMenuItem *lSimon = new AquariaMenuItem;
	    BitmapText *lSimonText = new BitmapText(&dsq->smallFont);
	    if (dsq->continuity.getFlag(FLAG_TRANSTURTLE_FOREST05)) {
	        setupTransportationItem(lSimon, lSimonText, "gems/turtle", lHorizontalPosition,
                            lVerticalPosition, "Simon says");
	        lSimon->event.set(MakeFunctionEvent(Randomizer,onSimonTransportation));
	        if (lFirst) {
	            lSimon->setDirMove(DIR_LEFT, menuCancel);
                menuCancel->setDirMove(DIR_RIGHT, lSimon);
	            lSimon->setFocus(true);
	            lFirst = false;
	        }
	        if (lHorizontalPosition > 500) {
	            lHorizontalPosition = 175.0;
	            lVerticalPosition = lVerticalPosition + 100.0;
	            if (lVerticalPosition > 350) {
	                lHorizontalPosition = 325.0;
	            }
	        } else {
	            lHorizontalPosition = lHorizontalPosition + 150;
	        }
	    } else {
	        lSimon->setCanDirMove(false);
	    }

		AquariaMenuItem *lReturnBase = new AquariaMenuItem;
		BitmapText *lReturnBaseText = new BitmapText(&dsq->smallFont);
		if (dsq->continuity.getFlag(FLAG_ENTER_HOMECAVE) == 0) {
			setupTransportationItem(lReturnBase, lReturnBaseText, "gems/naija-token", lHorizontalPosition,
				lVerticalPosition, "Naija's rock");
			lReturnBase->event.set(MakeFunctionEvent(Randomizer,onNaijaRockTransportation));
		} else {
			setupTransportationItem(lReturnBase, lReturnBaseText, "gems/naija-token", lHorizontalPosition,
				lVerticalPosition, "Naija's home");
			lReturnBase->event.set(MakeFunctionEvent(Randomizer,onNaijaHomeTransportation));
		}
	    if (lFirst) {
	        lReturnBase->setDirMove(DIR_LEFT, menuCancel);
	        menuCancel->setDirMove(DIR_RIGHT, lReturnBase);
	        lReturnBase->setFocus(true);
	        lFirst = false;
	    }

	    if (dsq->continuity.getFlag(FLAG_TRANSTURTLE_MAINAREA)) {
	        if (dsq->continuity.getFlag(FLAG_TRANSTURTLE_OPENWATER03)) {
	            lHomeWater->setDirMove(DIR_RIGHT, lOpenWater);
	            lOpenWater->setDirMove(DIR_LEFT, lHomeWater);
	        } else if (dsq->continuity.getFlag(FLAG_TRANSTURTLE_FOREST04)) {
	            lHomeWater->setDirMove(DIR_RIGHT, lForest);
	            lForest->setDirMove(DIR_LEFT, lHomeWater);
	        } else if (dsq->continuity.getFlag(FLAG_TRANSTURTLE_VEIL01)) {
	            lHomeWater->setDirMove(DIR_RIGHT, lVeil1);
	            lVeil1->setDirMove(DIR_LEFT, lHomeWater);
	        } else if (dsq->continuity.getFlag(FLAG_TRANSTURTLE_VEIL02)) {
	            lHomeWater->setDirMove(DIR_RIGHT, lVeil2);
	            lVeil2->setDirMove(DIR_LEFT, lHomeWater);
	        } else if (dsq->continuity.getFlag(FLAG_TRANSTURTLE_SEAHORSE)) {
	            lHomeWater->setDirMove(DIR_RIGHT, lArnassi);
	            lArnassi->setDirMove(DIR_LEFT, lHomeWater);
	        } else if (dsq->continuity.getFlag(FLAG_TRANSTURTLE_ABYSS03)) {
	            lHomeWater->setDirMove(DIR_RIGHT, lAbyss);
	            lAbyss->setDirMove(DIR_LEFT, lHomeWater);
	        } else if (dsq->continuity.getFlag(FLAG_TRANSTURTLE_FINALBOSS)) {
	            lHomeWater->setDirMove(DIR_RIGHT, lBody);
	            lBody->setDirMove(DIR_LEFT, lHomeWater);
	        } else if (dsq->continuity.getFlag(FLAG_TRANSTURTLE_FOREST05)) {
	            lHomeWater->setDirMove(DIR_RIGHT, lSimon);
	            lSimon->setDirMove(DIR_LEFT, lHomeWater);
	        } else {
	            lHomeWater->setDirMove(DIR_RIGHT, lReturnBase);
	            lReturnBase->setDirMove(DIR_LEFT, lHomeWater);
	        }
	    }
	    if (dsq->continuity.getFlag(FLAG_TRANSTURTLE_OPENWATER03)) {
	        if (dsq->continuity.getFlag(FLAG_TRANSTURTLE_FOREST04)) {
	            lOpenWater->setDirMove(DIR_RIGHT, lForest);
	            lForest->setDirMove(DIR_LEFT, lOpenWater);
	        } else if (dsq->continuity.getFlag(FLAG_TRANSTURTLE_VEIL01)) {
	            lOpenWater->setDirMove(DIR_RIGHT, lVeil1);
	            lVeil1->setDirMove(DIR_LEFT, lOpenWater);
	        } else if (dsq->continuity.getFlag(FLAG_TRANSTURTLE_VEIL02)) {
	            lOpenWater->setDirMove(DIR_RIGHT, lVeil2);
	            lVeil2->setDirMove(DIR_LEFT, lOpenWater);
	        } else if (dsq->continuity.getFlag(FLAG_TRANSTURTLE_SEAHORSE)) {
	            lOpenWater->setDirMove(DIR_RIGHT, lArnassi);
	            lArnassi->setDirMove(DIR_LEFT, lOpenWater);
	        } else if (dsq->continuity.getFlag(FLAG_TRANSTURTLE_ABYSS03)) {
	            lOpenWater->setDirMove(DIR_RIGHT, lAbyss);
	            lAbyss->setDirMove(DIR_LEFT, lOpenWater);
	        } else if (dsq->continuity.getFlag(FLAG_TRANSTURTLE_FINALBOSS)) {
	            lOpenWater->setDirMove(DIR_RIGHT, lBody);
	            lBody->setDirMove(DIR_LEFT, lOpenWater);
	        } else if (dsq->continuity.getFlag(FLAG_TRANSTURTLE_FOREST05)) {
	            lOpenWater->setDirMove(DIR_RIGHT, lSimon);
	            lSimon->setDirMove(DIR_LEFT, lOpenWater);
	        } else {
	            lOpenWater->setDirMove(DIR_RIGHT, lReturnBase);
	            lReturnBase->setDirMove(DIR_LEFT, lOpenWater);
	        }
	    }
	    if (dsq->continuity.getFlag(FLAG_TRANSTURTLE_FOREST04)) {
	        if (dsq->continuity.getFlag(FLAG_TRANSTURTLE_VEIL01)) {
	            lForest->setDirMove(DIR_RIGHT, lVeil1);
	            lVeil1->setDirMove(DIR_LEFT, lForest);
	        } else if (dsq->continuity.getFlag(FLAG_TRANSTURTLE_VEIL02)) {
	            lForest->setDirMove(DIR_RIGHT, lVeil2);
	            lVeil2->setDirMove(DIR_LEFT, lForest);
	        } else if (dsq->continuity.getFlag(FLAG_TRANSTURTLE_SEAHORSE)) {
	            lForest->setDirMove(DIR_RIGHT, lArnassi);
	            lArnassi->setDirMove(DIR_LEFT, lForest);
	        } else if (dsq->continuity.getFlag(FLAG_TRANSTURTLE_ABYSS03)) {
	            lForest->setDirMove(DIR_RIGHT, lAbyss);
	            lAbyss->setDirMove(DIR_LEFT, lForest);
	        } else if (dsq->continuity.getFlag(FLAG_TRANSTURTLE_FINALBOSS)) {
	            lForest->setDirMove(DIR_RIGHT, lBody);
	            lBody->setDirMove(DIR_LEFT, lForest);
	        } else if (dsq->continuity.getFlag(FLAG_TRANSTURTLE_FOREST05)) {
	            lForest->setDirMove(DIR_RIGHT, lSimon);
	            lSimon->setDirMove(DIR_LEFT, lForest);
	        } else {
	            lForest->setDirMove(DIR_RIGHT, lReturnBase);
	            lReturnBase->setDirMove(DIR_LEFT, lForest);
	        }
	    }
	    if (dsq->continuity.getFlag(FLAG_TRANSTURTLE_VEIL01)) {
	        if (dsq->continuity.getFlag(FLAG_TRANSTURTLE_VEIL02)) {
	            lVeil1->setDirMove(DIR_RIGHT, lVeil2);
	            lVeil2->setDirMove(DIR_LEFT, lVeil1);
	        } else if (dsq->continuity.getFlag(FLAG_TRANSTURTLE_SEAHORSE)) {
	            lVeil1->setDirMove(DIR_RIGHT, lArnassi);
	            lArnassi->setDirMove(DIR_LEFT, lVeil1);
	        } else if (dsq->continuity.getFlag(FLAG_TRANSTURTLE_ABYSS03)) {
	            lVeil1->setDirMove(DIR_RIGHT, lAbyss);
	            lAbyss->setDirMove(DIR_LEFT, lVeil1);
	        } else if (dsq->continuity.getFlag(FLAG_TRANSTURTLE_FINALBOSS)) {
	            lVeil1->setDirMove(DIR_RIGHT, lBody);
	            lBody->setDirMove(DIR_LEFT, lVeil1);
	        } else if (dsq->continuity.getFlag(FLAG_TRANSTURTLE_FOREST05)) {
	            lVeil1->setDirMove(DIR_RIGHT, lSimon);
	            lSimon->setDirMove(DIR_LEFT, lVeil1);
	        } else {
	            lVeil1->setDirMove(DIR_RIGHT, lReturnBase);
	            lReturnBase->setDirMove(DIR_LEFT, lVeil1);
	        }
	    }
	    if (dsq->continuity.getFlag(FLAG_TRANSTURTLE_VEIL02)) {
	        if (dsq->continuity.getFlag(FLAG_TRANSTURTLE_SEAHORSE)) {
	            lVeil2->setDirMove(DIR_RIGHT, lArnassi);
	            lArnassi->setDirMove(DIR_LEFT, lVeil2);
	        } else if (dsq->continuity.getFlag(FLAG_TRANSTURTLE_ABYSS03)) {
	            lVeil2->setDirMove(DIR_RIGHT, lAbyss);
	            lAbyss->setDirMove(DIR_LEFT, lVeil2);
	        } else if (dsq->continuity.getFlag(FLAG_TRANSTURTLE_FINALBOSS)) {
	            lVeil2->setDirMove(DIR_RIGHT, lBody);
	            lBody->setDirMove(DIR_LEFT, lVeil2);
	        } else if (dsq->continuity.getFlag(FLAG_TRANSTURTLE_FOREST05)) {
	            lVeil2->setDirMove(DIR_RIGHT, lSimon);
	            lSimon->setDirMove(DIR_LEFT, lVeil2);
	        } else {
	            lVeil2->setDirMove(DIR_RIGHT, lReturnBase);
	            lReturnBase->setDirMove(DIR_LEFT, lVeil2);
	        }
	    }
	    if (dsq->continuity.getFlag(FLAG_TRANSTURTLE_SEAHORSE)) {
	        if (dsq->continuity.getFlag(FLAG_TRANSTURTLE_ABYSS03)) {
	            lArnassi->setDirMove(DIR_RIGHT, lAbyss);
	            lAbyss->setDirMove(DIR_LEFT, lArnassi);
	        } else if (dsq->continuity.getFlag(FLAG_TRANSTURTLE_FINALBOSS)) {
	            lArnassi->setDirMove(DIR_RIGHT, lBody);
	            lBody->setDirMove(DIR_LEFT, lArnassi);
	        } else if (dsq->continuity.getFlag(FLAG_TRANSTURTLE_FOREST05)) {
	            lArnassi->setDirMove(DIR_RIGHT, lSimon);
	            lSimon->setDirMove(DIR_LEFT, lArnassi);
	        } else {
	            lArnassi->setDirMove(DIR_RIGHT, lReturnBase);
	            lReturnBase->setDirMove(DIR_LEFT, lArnassi);
	        }
	    }
	    if (dsq->continuity.getFlag(FLAG_TRANSTURTLE_ABYSS03)) {
	        if (dsq->continuity.getFlag(FLAG_TRANSTURTLE_FINALBOSS)) {
	            lAbyss->setDirMove(DIR_RIGHT, lBody);
	            lBody->setDirMove(DIR_LEFT, lAbyss);
	        } else if (dsq->continuity.getFlag(FLAG_TRANSTURTLE_FOREST05)) {
	            lAbyss->setDirMove(DIR_RIGHT, lSimon);
	            lSimon->setDirMove(DIR_LEFT, lAbyss);
	        } else {
	            lAbyss->setDirMove(DIR_RIGHT, lReturnBase);
	            lReturnBase->setDirMove(DIR_LEFT, lAbyss);
	        }
	    }
	    if (dsq->continuity.getFlag(FLAG_TRANSTURTLE_FINALBOSS)) {
	        if (dsq->continuity.getFlag(FLAG_TRANSTURTLE_FOREST05)) {
	            lBody->setDirMove(DIR_RIGHT, lSimon);
	            lSimon->setDirMove(DIR_LEFT, lBody);
	        } else {
	            lBody->setDirMove(DIR_RIGHT, lReturnBase);
	            lReturnBase->setDirMove(DIR_LEFT, lBody);
	        }
	    }
	    if (dsq->continuity.getFlag(FLAG_TRANSTURTLE_FOREST05)) {
	        lSimon->setDirMove(DIR_RIGHT, lReturnBase);
	        lReturnBase->setDirMove(DIR_LEFT, lSimon);
	    }

		menuCancel->useQuad("Gui/cancel");
		menuCancel->useSound("click");
		menuCancel->useGlow("particles/glow", 128, 40);
		menuCancel->position = Vector(400, 500);
		menuCancel->followCamera = 1;
		menuCancel->event.set(MakeFunctionEvent(Randomizer,onCancelTransportation));
		menuCancel->scale = Vector(0.9, 0.9);
		menuCancel->guiInputLevel = GUILEVEL_TRANSPORT;
		dsq->game->addRenderObject(menuCancel, LR_TRANSPORT);

	    lReturnBase->setDirMove(DIR_RIGHT, menuCancel);
	    menuCancel->setDirMove(DIR_LEFT, lReturnBase);




		AquariaGuiElement::currentGuiInputLevel = GUILEVEL_TRANSPORT;
		dsq->toggleCursor(true);

		while (!transporatationDone)
		{
		    transportationSelected = 0;
			dsq->main(FRAME_TIME);
		    if (transportationSelected == FLAG_TRANSTURTLE_MAINAREA) {
		        lHomeWater->setFocus(true);
		    } else if (transportationSelected == FLAG_TRANSTURTLE_OPENWATER03) {
		        lOpenWater->setFocus(true);
		    } else if (transportationSelected == FLAG_TRANSTURTLE_FOREST04) {
		        lForest->setFocus(true);
		    } else if (transportationSelected == FLAG_TRANSTURTLE_VEIL01) {
		        lVeil1->setFocus(true);
		    } else if (transportationSelected == FLAG_TRANSTURTLE_VEIL02) {
		        lVeil2->setFocus(true);
		    } else if (transportationSelected == FLAG_TRANSTURTLE_SEAHORSE) {
		        lArnassi->setFocus(true);
		    } else if (transportationSelected == FLAG_TRANSTURTLE_ABYSS03) {
		        lAbyss->setFocus(true);
		    } else if (transportationSelected == FLAG_TRANSTURTLE_FINALBOSS) {
		        lBody->setFocus(true);
		    } else if (transportationSelected == FLAG_TRANSTURTLE_FOREST05) {
		        lSimon->setFocus(true);
		    } else if (transportationSelected == FLAG_TRANSTURTLE_NAIJAHOME ||
		        transportationSelected == FLAG_TRANSTURTLE_NAIJAROCK) {
		        lReturnBase->setFocus(true);
		    }
		}
		sound->playSfx("menu-close");
		AquariaGuiElement::currentGuiInputLevel = 0;
		bgimage->alpha.interpolateTo(0, 0.5);
		bgimage->scale.interpolateTo(Vector(0.5, 0.5), 0.5);
		menuCancel->setFocus(false);
		menuCancel->safeKill();
		lTitle->safeKill();
		lHomeWater->setFocus(false);
		lHomeWater->safeKill();
		lHomeWaterText->safeKill();
		lOpenWater->setFocus(false);
		lOpenWater->safeKill();
		lOpenWaterText->safeKill();
		lForest->setFocus(false);
		lForest->safeKill();
		lForestText->safeKill();
		lVeil1->setFocus(false);
		lVeil1->safeKill();
		lVeil1Text->safeKill();
		lVeil2->setFocus(false);
		lVeil2->safeKill();
		lVeil2Text->safeKill();
		lArnassi->setFocus(false);
		lArnassi->safeKill();
		lArnassiText->safeKill();
		lAbyss->setFocus(false);
		lAbyss->safeKill();
		lAbyssText->safeKill();
		lBody->setFocus(false);
		lBody->safeKill();
		lBodyText->safeKill();
		lSimon->setFocus(false);
		lSimon->safeKill();
		lSimonText->safeKill();
		lReturnBase->setFocus(false);
		lReturnBase->safeKill();
		lReturnBaseText->safeKill();
		dsq->main(0.5);
		bgimage->safeKill();
		dsq->game->togglePause(false);
		}
	return transportationSelected;
}


