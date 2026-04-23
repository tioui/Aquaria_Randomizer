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
    transportationDone = false;
    transportationSelected = 0;
    errorMessage = "";
    mustUpgradeHealth = false;
    blindGoal = false;
    is_muted = false;
    killCreatorGoal = true;
    killFourGodsGoal = false;
    maximumIngredientAmount = 8;
    skipFirstVision = false;
    skipFinalBoss3rdForm = false;
    infiniteHotSoup = false;
    unconfine_home_water_transturtle = false;
    unconfine_home_water_energy_door = false;
    isAquarianTranslated = false;
    secretsNeeded = false;
    justLoading = false;
    seedNumberText = nullptr;
    removeTongue = false;
    saveHeal = true;
    locations = new std::vector<location_t>();
    items = new std::vector<item_t>();
    ingredients = new std::vector<ingredient_t>();
    collectibles = new std::vector<collectible_t>();
    nextMessages = new std::queue<randomessage_t>();
    currentMessageTime = 0;
    miniBossesToKill = 0;
    bigBossesToKill = 0;
    menuCancel = nullptr;
    homeWater = nullptr;
    openWater = nullptr;
    forest = nullptr;
    veil1 = nullptr;
    veil2 = nullptr;
    arnassi = nullptr;
    simon = nullptr;
    abyss = nullptr;
    body = nullptr;
    returnBase = nullptr;
    progressiveLoafIndex = 0;
    progressiveSoupIndex = 0;
    progressiveCakeIndex = 0;
    progressivePoulticeIndex = 0;
    progressiveRollIndex = 0;
    progressivePerogiIndex = 0;
    progressiveIceCreamIndex = 0;
    initialiseLocations();
    initialiseItems();
    initialiseIngredients();
    initialiseCollectibles();
}

/**
 * Initialize the ingredients vector
 */
void Randomizer::initialiseIngredients() const {
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
    ingredients->push_back({"SpicySoup", IT_SOUP});
    ingredients->push_back({"ColdSoup", IT_SOUP});
    ingredients->push_back({"SharkFinSoup", IT_SOUP});
    ingredients->push_back({"MagicSoup", IT_SOUP});
    ingredients->push_back({"RoyalSoup", IT_SOUP});
    ingredients->push_back({"VeggieSoup", IT_SOUP});
    ingredients->push_back({"LongLifeSoup", IT_SOUP});
    ingredients->push_back({"ColdBorscht", IT_SOUP});
    ingredients->push_back({"HotBorscht", IT_SOUP});
    ingredients->push_back({"TurtleSoup", IT_SOUP});
    ingredients->push_back({"DivineSoup", IT_SOUP});
    ingredients->push_back({"RainbowSoup", IT_SOUP});
    ingredients->push_back({"PoisonSoup", IT_SOUP});
    ingredients->push_back({"SeaLoaf", IT_LOAF});
    ingredients->push_back({"ButterySeaLoaf", IT_LOAF});
    ingredients->push_back({"VedhaSeaCrisp", IT_LOAF});
    ingredients->push_back({"RottenLoaf", IT_LOAF});
    ingredients->push_back({"PoisonLoaf", IT_LOAF});
    ingredients->push_back({"LoafOfLife", IT_LOAF});
    ingredients->push_back({"SeaCake", IT_CAKE});
    ingredients->push_back({"TastyCake", IT_CAKE});
    ingredients->push_back({"VeggieCake", IT_CAKE});
    ingredients->push_back({"ToughCake", IT_CAKE});
    ingredients->push_back({"CrabCake", IT_CAKE});
    ingredients->push_back({"SpecialCake", IT_CAKE});
    ingredients->push_back({"SwampCake", IT_CAKE});
    ingredients->push_back({"LegendaryCake", IT_CAKE});
    ingredients->push_back({"RottenCake", IT_CAKE});
    ingredients->push_back({"LeafPoultice", IT_POULTICE});
    ingredients->push_back({"HealingPoultice", IT_POULTICE});
    ingredients->push_back({"SightPoultice", IT_POULTICE});
    ingredients->push_back({"LeechingPoultice", IT_POULTICE});
    ingredients->push_back({"ArcanePoultice", IT_POULTICE});
    ingredients->push_back({"Vedha'sCure-All", IT_POULTICE});
    ingredients->push_back({"IceCream", IT_ICECREAM});
    ingredients->push_back({"DumboIceCream", IT_ICECREAM});
    ingredients->push_back({"VeggieIceCream", IT_ICECREAM});
    ingredients->push_back({"BerryIceCream", IT_ICECREAM});
    ingredients->push_back({"HandRoll", IT_ROLL});
    ingredients->push_back({"TastyRoll", IT_ROLL});
    ingredients->push_back({"SpicyRoll", IT_ROLL});
    ingredients->push_back({"SpiderRoll", IT_ROLL});
    ingredients->push_back({"LeadershipRoll", IT_ROLL});
    ingredients->push_back({"VolcanoRoll", IT_ROLL});
    ingredients->push_back({"Perogi", IT_PEROGI});
    ingredients->push_back({"PlumpPerogi", IT_PEROGI});
    ingredients->push_back({"Zuuna'sPerogi", IT_PEROGI});
}

/**
 * Initialize every location
 */
void Randomizer::initialiseLocations() const {
    locations->push_back({1101, "bulb_turtlecave","Turtle cave, bulb in Bubble Cliff"});
    locations->push_back({1102, "bulb_openwater_tl_1","Open Waters top left area, bulb under the rock in the right path"});
    locations->push_back({1103, "bulb_openwater_tl_2","Open Waters top left area, bulb under the rock in the left path"});
    locations->push_back({1104, "bulb_openwater_tl_3","Open Waters top left area, bulb to the right of the save crystal"});
    locations->push_back({1105, "bulb_openwater_tr_1","Open Waters top right area, bulb in the small path before Mithalas"});
    locations->push_back({1106, "bulb_openwater_tr_2","Open Waters top right area, bulb in the path from the left entrance"});
    locations->push_back({1107, "bulb_openwater_tr_3","Open Waters top right area, bulb in the clearing close to the bottom exit"});
    locations->push_back({1108, "bulb_openwater_tr_4","Open Waters top right area, bulb in the big clearing close to the save crystal"});
    locations->push_back({1109, "bulb_openwater_tr_5","Open Waters top right area, bulb in the big clearing to the top exit"});
    locations->push_back({1110, "bulb_openwater_tr_6","Open Waters top right area, bulb in the turtle room"});
    locations->push_back({1111, "bulb_openwater_bl_1","Open Waters bottom left area, bulb inside the lowest fish pass"});
    locations->push_back({1112, "bulb_openwater_bl_2","Open Waters bottom left area, bulb behind the chomper fish"});
    locations->push_back({1113, "bulb_skeleton_path_1","Open Waters skeleton path, bulb close to the right exit"});
    locations->push_back({1114, "bulb_skeleton_path_2","Open Waters skeleton path, bulb behind the chomper fish"});
    locations->push_back({1115, "bulb_arnassi_1","Arnassi Ruins, bulb in the right part"});
    locations->push_back({1116, "bulb_arnassi_2","Arnassi Ruins, bulb in the left part"});
    locations->push_back({1117, "bulb_arnassi_3","Arnassi Ruins, bulb in the center part"});
    locations->push_back({1118, "bulb_sunworm_1","Sun temple boss path, first path bulb"});
    locations->push_back({1119, "bulb_sunworm_2","Sun temple boss path, second path bulb"});
    locations->push_back({1120, "bulb_sunworm_3","Sun temple boss path, first cliff bulb"});
    locations->push_back({1121, "bulb_sunworm_4","Sun temple boss path, second cliff bulb"});
    locations->push_back({1122, "bulb_tutorial_1","Verse Cave left area, bulb in the center part"});
    locations->push_back({1123, "bulb_tutorial_2","Verse Cave left area, bulb in the right part"});
    locations->push_back({1124, "bulb_tutorial_3","Verse Cave left area, bulb under the rock at the end of the path"});
    locations->push_back({1125, "bulb_abyss_l_1","Abyss left area, bulb in hidden path room"});
    locations->push_back({1126, "bulb_abyss_l_2","Abyss left area, bulb in the right part"});
    locations->push_back({1127, "bulb_abyss_l_3","Abyss left area, bulb in the bottom fish pass"});
    locations->push_back({1128, "bulb_energy_temple_1_1","Energy Temple first area, bulb in the bottom room blocked by a rock"});
    locations->push_back({1129, "bulb_energy_temple_2_1","Energy Temple second area, bulb under the rock"});
    locations->push_back({1130, "bulb_energy_temple_3_1","Energy Temple third area, bulb in the bottom path"});
    locations->push_back({1131, "bulb_mithalas_city_01","Mithalas City, first bulb in the left city part"});
    locations->push_back({1132, "bulb_mithalas_city_02","Mithalas City, bulb in the right part"});
    locations->push_back({1133, "bulb_mithalas_city_03","Mithalas City, first bulb at the end of the top path"});
    locations->push_back({1134, "bulb_mithalas_city_04","Mithalas City, bulb at the top of the city"});
    locations->push_back({1135, "bulb_mithalas_city_05","Mithalas City, first bulb in a broken home"});
    locations->push_back({1136, "bulb_mithalas_city_06","Mithalas City, second bulb in the left city part"});
    locations->push_back({1137, "bulb_mithalas_city_07","Mithalas City, bulb in the top path"});
    locations->push_back({1138, "bulb_mithalas_city_08","Mithalas City, bulb in the bottom left part"});
    locations->push_back({1139, "bulb_mithalas_city_09","Mithalas City, first bulb in one of the homes"});
    locations->push_back({1140, "bulb_mithalas_city_10","Mithalas City, second bulb in one of the homes"});
    locations->push_back({1141, "bulb_mithalas_city_11","Mithalas City, second bulb at the end of the top path"});
    locations->push_back({1142, "bulb_mithalas_city_12","Mithalas City, second bulb in a broken home"});
    locations->push_back({1143, "bulb_cathedral_l_2","Mithalas City Castle, bulb in the flesh hole"});
    locations->push_back({1144, "bulb_boilerroom_1","Sunken City, bulb on top of the boss area"});
    locations->push_back({1145, "bulb_forest_tl_1","Kelp Forest top left area, bulb in the bottom left clearing"});
    locations->push_back({1146, "bulb_forest_tl_2","Kelp Forest top left area, bulb in the path down from the top left clearing"});
    locations->push_back({1147, "bulb_forest_tl_3","Kelp Forest top left area, bulb in the top left clearing"});
    locations->push_back({1148, "bulb_forest_tl_4","Kelp Forest top left area, bulb close to the Verse Egg"});
    locations->push_back({1149, "bulb_forest_tr_1","Kelp Forest top right area, bulb under the rock in the right path"});
    locations->push_back({1150, "bulb_forest_tr_2","Kelp Forest top right area, bulb at the left of the center clearing"});
    locations->push_back({1151, "bulb_forest_tr_3","Kelp Forest top right area, bulb in the top fish pass"});
    locations->push_back({1152, "bulb_forest_tr_4","Kelp Forest top right area, bulb in the left path's big room"});
    locations->push_back({1153, "bulb_forest_tr_5","Kelp Forest top right area, bulb in the left path's small room"});
    locations->push_back({1154, "bulb_forest_tr_6","Kelp Forest top right area, bulb at the top of the center clearing"});
    locations->push_back({1155, "bulb_forest_bl_1","Kelp Forest bottom left area, bulb close to the spirit crystals"});
    locations->push_back({1156, "bulb_forest_boss_room_1","Kelp Forest boss room, bulb at the bottom of the area"});
    locations->push_back({1157, "bulb_forest_sprite_cave_1","Kelp Forest sprite cave, bulb inside the fish pass"});
    locations->push_back({1158, "bulb_forest_sprite_cave_2","Kelp Forest sprite cave, bulb in the second room"});
    locations->push_back({1159, "bulb_home_water_1","Home Waters, bulb below the grouper fish"});
    locations->push_back({1160, "bulb_home_water_2","Home Waters, bulb in the path below Nautilus Prime"});
    locations->push_back({1161, "bulb_home_water_3","Home Waters, bulb in the little room above the grouper fish"});
    locations->push_back({1162, "bulb_home_water_4","Home Waters, bulb in the end of the path close to the Verse Cave"});
    locations->push_back({1163, "bulb_home_water_5","Home Waters, bulb in the top left path"});
    locations->push_back({1164, "bulb_home_water_6","Home Waters, bulb in the bottom left room"});
    locations->push_back({1165, "bulb_home_water_7","Home Waters, bulb close to Naija's Home"});
    locations->push_back({1166, "bulb_home_water_8","Home Waters, bulb under the rock in the left path from the Verse Cave"});
    locations->push_back({1167, "bulb_final_l_1","The Body left area, first bulb in the top face room"});
    locations->push_back({1168, "bulb_final_l_2","The Body left area, bulb below the water stream"});
    locations->push_back({1169, "bulb_final_l_3","The Body left area, bulb in the top path to the top face room"});
    locations->push_back({1170, "bulb_final_l_4","The Body left area, second bulb in the top face room"});
    locations->push_back({1171, "bulb_final_l_5","The Body left area, bulb in the bottom face room"});
    locations->push_back({1172, "bulb_song_cave_1","Song Cave, bulb in the top right part"});
    locations->push_back({1173, "bulb_song_cave_2","Song Cave, bulb in the big anemone room"});
    locations->push_back({1174, "bulb_song_cave_3","Song Cave, bulb in the path to the singing statues"});
    locations->push_back({1175, "bulb_song_cave_4","Song Cave, bulb under the rock in the path to the singing statues"});
    locations->push_back({1176, "bulb_song_cave_5","Song Cave, bulb under the rock close to the song door"});
    locations->push_back({1177, "bulb_veil_tl_1","The Veil top left area, bulb hidden behind the blocking rock"});
    locations->push_back({1178, "bulb_veil_tl_2","The Veil top left area, bulb inside the fish pass"});
    locations->push_back({1179, "bulb_veil_tl_3","The Veil top left area, bulb under the rock in the top right path"});
    locations->push_back({1180, "bulb_veil_tr_1","The Veil top right area, bulb in the middle of the wall jump cliff"});
    locations->push_back({1181, "bulb_veil_tr_2","The Veil top right area, bulb at the top of the waterfall"});
    locations->push_back({1182, "bulb_veil_b_1","The Veil bottom area, bulb in the spirit path"});
    locations->push_back({1183, "bulb_veil_b_2","The Veil bottom area, bulb in the left path"});
    locations->push_back({1184, "bulb_ice_cave_1","Ice Cavern, bulb in the room to the right"});
    locations->push_back({1185, "bulb_ice_cave_2","Ice Cavern, first bulb in the top exit room"});
    locations->push_back({1186, "bulb_ice_cave_3","Ice Cavern, second bulb in the top exit room"});
    locations->push_back({1187, "bulb_ice_cave_4","Ice Cavern, third bulb in the top exit room"});
    locations->push_back({1188, "bulb_ice_cave_5","Ice Cavern, bulb in the left room"});
    locations->push_back({1189, "bulb_king_jellyfish_cave_1","King Jellyfish Cave, bulb in the right path from King Jelly"});
    locations->push_back({1190, "bulb_bubble_cave_1","Bubble Cave, bulb in the left cave wall"});
    locations->push_back({1191, "bulb_bubble_cave_2","Bubble Cave, bulb in the right cave wall (behind the ice crystal)"});
    locations->push_back({1192, "bulb_sun_temple_1","Sun Temple, first bulb of the temple"});
    locations->push_back({1193, "bulb_sun_temple_2","Sun Temple, bulb on the right part"});
    locations->push_back({1194, "bulb_sun_temple_3","Sun Temple, bulb in the hidden room of the right part"});
    locations->push_back({1195, "bulb_sun_temple_4","Sun Temple, bulb in the top left part"});
    locations->push_back({1196, "bulb_sun_temple_5","Sun Temple, bulb in the top right part"});
    locations->push_back({1197, "bulb_sun_temple_6","Sun Temple, bulb at the top of the high dark room"});
    locations->push_back({1198, "bulb_final_c_1","The Body center area, bulb on the main path blocking tube"});
    locations->push_back({1199, "bulb_final_r_1","The Body right area, bulb in the top path to the bottom face room"});
    locations->push_back({1200, "bulb_final_r_2","The Body right area, bulb in the bottom face room"});
    locations->push_back({1201, "bulb_final_r_3","The Body right area, bulb in the top face room"});
    locations->push_back({1202, "bulb_final_b_1","The Body bottom area, bulb in the Jelly Zap room"});
    locations->push_back({1203, "bulb_final_b_2","The Body bottom area, bulb in the nautilus room"});
    locations->push_back({1204, "bulb_final_boss_1","Final Boss area, first bulb in the turtle room"});
    locations->push_back({1205, "bulb_final_boss_2","Final Boss area, second bulb in the turtle room"});
    locations->push_back({1206, "bulb_final_boss_3","Final Boss area, third bulb in the turtle room"});
    locations->push_back({1207, "bulb_final_boss_4","Final Boss area, bulb in the boss third form room"});
    locations->push_back({1208, "bulb_starting_cave_1","Verse Cave right area, bulb in the skeleton room"});
    locations->push_back({1209, "bulb_starting_cave_2","Verse Cave right area, bulb in the path right of the skeleton room"});
    locations->push_back({1210, "bulb_abyss_r_1","Abyss right area, bulb behind the rock in the whale room"});
    locations->push_back({1211, "bulb_abyss_r_2","Abyss right area, bulb in the middle path"});
    locations->push_back({1212, "bulb_abyss_r_3","Abyss right area, bulb behind the rock in the middle path"});
    locations->push_back({1213, "bulb_abyss_r_4","Abyss right area, bulb in the left green room"});
    locations->push_back({1214, "bulb_cathedral_under_ground_1","Mithalas Cathedral Underground, bulb in the center part"});
    locations->push_back({1215, "bulb_cathedral_under_ground_2","Mithalas Cathedral Underground, first bulb in the top left part"});
    locations->push_back({1216, "bulb_cathedral_under_ground_3","Mithalas Cathedral Underground, second bulb in the top left part"});
    locations->push_back({1217, "bulb_cathedral_under_ground_4","Mithalas Cathedral Underground, third bulb in the top left part"});
    locations->push_back({1218, "bulb_cathedral_under_ground_5","Mithalas Cathedral Underground, bulb close to the save crystal"});
    locations->push_back({1219, "bulb_cathedral_under_ground_6","Mithalas Cathedral Underground, bulb in the bottom right path"});
    locations->push_back({1220, "bulb_naija_home_1","Naija's Home, bulb after the energy door"});
    locations->push_back({1221, "bulb_naija_home_2","Naija's Home, bulb under the rock at the right of the main path"});
    locations->push_back({1222, "bulb_mermog_cave_1","Mermog cave, bulb in the left part of the cave"});
    locations->push_back({1223, "bulb_octo_cave_1","Octopus Cave, bulb in the path below the Octopus Cave path"});
    locations->push_back({1224, "urn_mithalas_city_1","Mithalas City, first urn in one of the homes"});
    locations->push_back({1225, "urn_mithalas_city_2","Mithalas City, second urn in one of the homes"});
    locations->push_back({1226, "urn_mithalas_city_3","Mithalas City, first urn in the city reserve"});
    locations->push_back({1227, "urn_mithalas_city_4","Mithalas City, second urn in the city reserve"});
    locations->push_back({1228, "urn_mithalas_city_5","Mithalas City, third urn in the city reserve"});
    locations->push_back({1229, "urn_mithalas_city_6","Mithalas City, urn in the Castle flower tube entrance"});
    locations->push_back({1230, "urn_mithalas_city_7","Mithalas City, urn inside a home fish pass"});
    locations->push_back({1231, "urn_cathedral_l_1","Mithalas City Castle, urn in the bedroom"});
    locations->push_back({1232, "urn_cathedral_l_2","Mithalas City Castle, first urn of the single lamp path"});
    locations->push_back({1233, "urn_cathedral_l_3","Mithalas City Castle, second urn of the single lamp path"});
    locations->push_back({1234, "urn_cathedral_l_4","Mithalas City Castle, urn in the bottom room"});
    locations->push_back({1235, "urn_cathedral_l_5","Mithalas City Castle, first urn on the entrance path"});
    locations->push_back({1236, "urn_cathedral_l_6","Mithalas City Castle, second urn on the entrance path"});
    locations->push_back({1237, "urn_cathedral_r_01","Mithalas Cathedral, first urn in the top right room"});
    locations->push_back({1238, "urn_cathedral_r_02","Mithalas Cathedral, second urn in the top right room"});
    locations->push_back({1239, "urn_cathedral_r_03","Mithalas Cathedral, third urn in the top right room"});
    locations->push_back({1240, "urn_cathedral_r_04","Mithalas Cathedral, bulb in the flesh room with fleas"});
    locations->push_back({1241, "urn_cathedral_r_05","Mithalas Cathedral, first urn in the bottom right path"});
    locations->push_back({1242, "urn_cathedral_r_06","Mithalas Cathedral, second urn in the bottom right path"});
    locations->push_back({1243, "urn_cathedral_r_07","Mithalas Cathedral, urn behind the flesh vein"});
    locations->push_back({1244, "urn_cathedral_r_08","Mithalas Cathedral, urn in the top left eyes boss room"});
    locations->push_back({1245, "urn_cathedral_r_09","Mithalas Cathedral, first urn in the path behind the flesh vein"});
    locations->push_back({1246, "urn_cathedral_r_10","Mithalas Cathedral, second urn in the path behind the flesh vein"});
    locations->push_back({1247, "urn_cathedral_r_11","Mithalas Cathedral, third urn in the path behind the flesh vein"});
    locations->push_back({1248, "urn_cathedral_r_12","Mithalas Cathedral, fourth urn in the top right room"});
    locations->push_back({1249, "urn_openwater_tr_1","Open Waters top right area, first urn in the Mithalas exit"});
    locations->push_back({1250, "urn_openwater_tr_2","Open Waters top right area, second urn in the Mithalas exit"});
    locations->push_back({1251, "urn_openwater_tr_3","Open Waters top right area, third urn in the Mithalas exit"});
    locations->push_back({1252, "crate_sunkencity_2_1","Sunken City left area, crate in the little pipe room"});
    locations->push_back({1253, "crate_sunkencity_2_2","Sunken City left area, crate close to the save crystal"});
    locations->push_back({1254, "crate_sunkencity_2_3","Sunken City left area, crate before the bedroom"});
    locations->push_back({1255, "crate_sunkencity_1_1","Sunken City right area, crate close to the save crystal"});
    locations->push_back({1256, "crate_sunkencity_1_2","Sunken City right area, crate in the left bottom room"});
    locations->push_back({1257, "beating_simon","Simon Says area, beating Simon Says"});
    locations->push_back({1258, "health_egg_1","The Veil bottom area, Verse Egg"});
    locations->push_back({1259, "health_egg_2","Kelp Forest top left area, Verse Egg"});
    locations->push_back({1260, "health_egg_3","The Whale, Verse Egg"});
    locations->push_back({1261, "health_egg_4","Song Cave, Verse Egg"});
    locations->push_back({1262, "health_egg_5","Bubble Cave, Verse Egg"});
    locations->push_back({1263, "collect_anemone","Song Cave, Anemone Seed"});
    locations->push_back({1264, "collect_energy_temple","Energy Temple bottom entrance, Krotite Armor"});
    locations->push_back({1265, "collect_arnassi_statue","Arnassi Ruins, Arnassi Statue"});
    locations->push_back({1266, "collect_mithalas_banner","Mithalas City Castle, Blue Banner"});
    locations->push_back({1267, "collect_bio_seed","Abyss left area, Glowing Seed"});
    locations->push_back({1268, "collect_blackpearl","Kelp Forest top right area, Black Pearl"});
    locations->push_back({1269, "collect_treasure_chest","Kelp Forest bottom right area, Odd Container"});
    locations->push_back({1270, "collect_energy_boss","Energy Temple boss area, Fallen God Tooth"});
    locations->push_back({1271, "collect_energy_statue","Energy Temple, Energy Idol"});
    locations->push_back({1272, "collect_golden_gear","Sun Temple, Golden Gear"});
    locations->push_back({1273, "collect_jelly_plant","Abyss left area, Glowing Plant"});
    locations->push_back({1274, "collect_mithala_doll","Mithalas City, Doll"});
    locations->push_back({1275, "collect_mithalas_pot","Mithalas City, Mithalas Pot"});
    locations->push_back({1276, "collect_big_seed","Verse Cave right area, Big Seed"});
    locations->push_back({1277, "collect_seed_bag","Kelp Forest sprite cave, Seed Bag"});
    locations->push_back({1278, "collect_skull","Open Waters skeleton path, King Skull"});
    locations->push_back({1279, "collect_jelly_beacon","Song Cave, Jelly Beacon"});
    locations->push_back({1280, "collect_spore_seed","Arnassi Ruins, Song Plant Spore"});
    locations->push_back({1281, "collect_gold_star","The Veil top right area, Golden Starfish"});
    locations->push_back({1282, "collect_stone_head","The Veil bottom area, Stone Head"});
    locations->push_back({1283, "collect_sun_key","Sun Temple, Sun Key"});
    locations->push_back({1284, "collect_trident_head","Mithalas City Castle, Trident Head"});
    locations->push_back({1285, "collect_turtle_egg","Turtle cave, Turtle Egg"});
    locations->push_back({1286, "collect_upsidedown_seed","Kelp Forest top left area, Jelly Egg"});
    locations->push_back({1287, "collect_walker","Kelp Forest bottom left area, Walker Baby"});
    locations->push_back({1288, "collect_crab_costume","Arnassi Ruins, Crab Armor"});
    locations->push_back({1289, "collect_jelly_costume","King Jellyfish Cave, Jellyfish Costume"});
    locations->push_back({1290, "collect_mithalan_costume","Mithalas Cathedral, Mithalan Dress"});
    locations->push_back({1291, "collect_mutant_costume","The Body bottom area, Mutant Costume"});
    locations->push_back({1292, "collect_seahorse_costume","Arnassi Ruins, Arnassi Armor"});
    locations->push_back({1293, "collect_teen_costume","Sunken City left area, Girl Costume"});
    locations->push_back({1294, "collect_urchin_costume","Turtle cave, Urchin Costume"});
    locations->push_back({1295, "collect_nautilus","Home Waters, Nautilus Egg"});
    locations->push_back({1296, "collect_blaster","Energy Temple blaster room, Blaster Egg"});
    locations->push_back({1297, "collect_dumbo","Octopus Cave, Dumbo Egg"});
    locations->push_back({1298, "collect_piranha","Mermog cave, Piranha Egg"});
    locations->push_back({1299, "urn_cathedral_r_13","Mithalas Cathedral, urn below the left entrance"});
    locations->push_back({1300, "li_cave","The Veil top left area, In Li's cave"});
    locations->push_back({1301, "song_shield_hint","Verse Cave left area, the Naija hint about the shield ability"});
    locations->push_back({1302, "breaking_li_cage","The Body center area, breaking Li's cage"});
    locations->push_back({1303, "beating_mithalas","Mithalas boss area, beating Mithalan God"});
    locations->push_back({1304, "beating_sun_god","Sun Temple boss area, beating Lumerean God"});
    locations->push_back({1305, "beating_drunian_god","Kelp Forest boss area, beating Drunian God"});
    locations->push_back({1306, "beating_energy_statue","Energy Temple first area, beating the Energy Statue"});
    locations->push_back({1307, "erulian_spirit","Song Cave, Erulian spirit"});
    locations->push_back({1308, "fish_cave_puzzle","Kelp Forest bottom left area, Fish Cave puzzle"});
    locations->push_back({1309, "beating_priests","Mithalas City Castle, beating the Priests"});
    locations->push_back({1310, "transturtle_veil01","The Veil top left area, Transturtle"});
    locations->push_back({1311, "transturtle_veil02","The Veil top right area, Transturtle"});
    locations->push_back({1312, "transturtle_openwater03","Open Waters top right area, Transturtle"});
    locations->push_back({1313, "transturtle_forest04","Kelp Forest bottom left area, Transturtle"});
    locations->push_back({1314, "transturtle_mainarea","Home Waters, Transturtle"});
    locations->push_back({1315, "transturtle_abyss03","Abyss right area, Transturtle"});
    locations->push_back({1316, "transturtle_finalboss","Final Boss area, Transturtle"});
    locations->push_back({1317, "transturtle_forest05","Simon Says area, Transturtle"});
    locations->push_back({1318, "transturtle_seahorse","Arnassi Ruins, Transturtle"});
    locations->push_back({1319, "sitting_on_throne","Mithalas City Castle, sitting on the sealed throne"});
    locations->push_back({1320, "beating_golem","Sunken City, beating the Golem"});
}

/**
 * Initialize every item
 */
void Randomizer::initialiseItems() const {
    items->push_back({"ingredient_sealoaf", "Sea loaf"});
    items->push_back({"ingredient_leafpoultice", "Leaf poultice"});
    items->push_back({"ingredient_handroll", "Hand roll"});
    items->push_back({"ingredient_veggiesoup", "Veggie soup"});
    items->push_back({"ingredient_butterysealoaf", "Buttery sea loaf"});
    items->push_back({"ingredient_healingpoultice", "Healing poultice"});
    items->push_back({"ingredient_spicyroll", "Spicy roll"});
    items->push_back({"ingredient_spicymeat", "Spicy meat"});
    items->push_back({"ingredient_crabcake", "Crab cake"});
    items->push_back({"ingredient_leadershiproll", "Leadership roll"});
    items->push_back({"ingredient_tastycake", "Tasty cake"});
    items->push_back({"ingredient_perogi", "Perogi"});
    items->push_back({"ingredient_tastyroll", "Tasty roll"});
    items->push_back({"ingredient_specialbulb", "Special bulb"});
    items->push_back({"ingredient_specialcake", "Special cake"});
    items->push_back({"ingredient_plantleaf", "Plant leaf"});
    items->push_back({"ingredient_turtlesoup", "Turtle soup"});
    items->push_back({"ingredient_hotsoup", "Hot soup"});
    items->push_back({"ingredient_heartysoup", "Hearty soup"});
    items->push_back({"ingredient_coldborscht", "Cold borscht"});
    items->push_back({"ingredient_sightpoultice", "Sight poultice"});
    items->push_back({"ingredient_vedhaseacrisp", "Vedha sea crisp"});
    items->push_back({"ingredient_rottenloaf", "Rotten loaf"});
    items->push_back({"ingredient_rottenmeat", "Rotten meat"});
    items->push_back({"ingredient_smalltentacle", "Small tentacle"});
    items->push_back({"ingredient_seacake", "Sea cake"});
    items->push_back({"ingredient_smallbone", "Small bone"});
    items->push_back({"ingredient_leechingpoultice", "Leeching poultice"});
    items->push_back({"ingredient_redbulb", "Red bulb"});
    items->push_back({"ingredient_spiderroll", "Spider roll"});
    items->push_back({"ingredient_veggiecake", "Veggie cake"});
    items->push_back({"ingredient_swampcake", "Swamp cake"});
    items->push_back({"ingredient_sharkfinsoup", "Shark fin soup"});
    items->push_back({"ingredient_smallegg", "Small egg"});
    items->push_back({"ingredient_fishmeat", "Fish meat"});
    items->push_back({"ingredient_arcanepoultice", "Arcane poultice"});
    items->push_back({"ingredient_divinesoup", "Divine soup"});
    items->push_back({"ingredient_volcanoroll", "Volcano roll"});
    items->push_back({"ingredient_eeloil", "Eel oil"});
    items->push_back({"ingredient_spicysoup", "Spicy soup"});
    items->push_back({"ingredient_longlifesoup", "Long life soup"});
    items->push_back({"ingredient_legendarycake", "Legendary cake"});
    items->push_back({"ingredient_icecream", "Ice cream"});
    items->push_back({"ingredient_berryicecream", "Berry ice cream"});
    items->push_back({"ingredient_veggieicecream", "Veggie ice cream"});
    items->push_back({"ingredient_dumboicecream", "Dumbo ice cream"});
    items->push_back({"ingredient_coldsoup", "Cold soup"});
    items->push_back({"ingredient_glowingegg", "Glowing egg"});
    items->push_back({"ingredient_magicsoup", "Magic soup"});
    items->push_back({"ingredient_royalsoup", "Royal soup"});
    items->push_back({"ingredient_Zuuna'sperogi", "Zuuna's perogi"});
    items->push_back({"ingredient_plumpperogi", "Plump perogi"});
    items->push_back({"ingredient_Vedha'sCure-All", "Vedha's Cure-All"});
    items->push_back({"ingredient_loafoflife", "Loaf of life"});
    items->push_back({"ingredient_fishoil", "Fish oil"});
    items->push_back({"ingredient_hotborscht", "Hot borscht"});
    items->push_back({"ingredient_redberry", "Red berry"});
    items->push_back({"ingredient_rainbowmushroom", "Rainbow mushroom"});
    items->push_back({"ingredient_rainbowsoup", "Rainbow soup"});
    items->push_back({"ingredient_rottencake", "Rotten cake"});
    items->push_back({"ingredient_toughcake", "Tough cake"});
    items->push_back({"ingredient_poisonloaf", "Poison loaf"});
    items->push_back({"ingredient_poisonsoup", "Poison soup"});
    items->push_back({"ingredient_mushroom", "Mushroom"});
    items->push_back({"upgrade_wok", "Wok"});
    items->push_back({"upgrade_health", "Health"});
    items->push_back({"collectible_anemone", "Anemone"});
    items->push_back({"collectible_energy_temple", "Krotite armor"});
    items->push_back({"collectible_arnassi_statue", "Arnassi statue"});
    items->push_back({"collectible_mithalas_banner", "Mithalas banner"});
    items->push_back({"collectible_bio_seed", "Glowing seed"});
    items->push_back({"collectible_blackpearl", "Black pearl"});
    items->push_back({"collectible_treasure_chest", "Odd container"});
    items->push_back({"collectible_energy_boss", "Tooth"});
    items->push_back({"collectible_energy_statue", "Energy statue"});
    items->push_back({"collectible_golden_gear", "Golden gear"});
    items->push_back({"collectible_jelly_plant", "Jelly plant"});
    items->push_back({"collectible_mithala_doll", "Mithalas doll"});
    items->push_back({"collectible_mithalas_pot", "Mithalas pot"});
    items->push_back({"collectible_big_seed", "Big seed"});
    items->push_back({"collectible_seed_bag", "Seed bag"});
    items->push_back({"collectible_skull", "King's Skull"});
    items->push_back({"collectible_jelly_beacon", "Jelly beacon"});
    items->push_back({"collectible_spore_seed", "Song plant spore"});
    items->push_back({"collectible_gold_star", "Golden starfish"});
    items->push_back({"collectible_stone_head", "Stone head"});
    items->push_back({"collectible_sun_key", "Sun key"});
    items->push_back({"collectible_trident_head", "Trident"});
    items->push_back({"collectible_turtle_egg", "Turtle egg"});
    items->push_back({"collectible_upsidedown_seed", "Jelly egg"});
    items->push_back({"collectible_walker", "Baby walker"});
    items->push_back({"collectible_crab_costume", "Crab armor"});
    items->push_back({"collectible_jelly_costume", "Jelly costume"});
    items->push_back({"collectible_mithalan_costume", "Mithalan dress"});
    items->push_back({"collectible_mutant_costume", "Mutant costume"});
    items->push_back({"collectible_seahorse_costume", "Arnassi Armor"});
    items->push_back({"collectible_teen_costume", "Girl costume"});
    items->push_back({"collectible_urchin_costume", "Urchin costume"});
    items->push_back({"collectible_nautilus", "Baby nautilus"});
    items->push_back({"collectible_blaster", "Baby blaster"});
    items->push_back({"collectible_dumbo", "Baby dumbo"});
    items->push_back({"collectible_piranha", "Baby piranha"});
    items->push_back({"song_li", "Li and Li song"});
    items->push_back({"song_shield", "Shield song"});
    items->push_back({"song_dual", "Dual Form"});
    items->push_back({"song_beast", "Beast Form"});
    items->push_back({"song_sun", "Sun Form"});
    items->push_back({"song_nature", "Nature Form"});
    items->push_back({"song_energy", "Energy Form"});
    items->push_back({"song_bind", "Bind song"});
    items->push_back({"song_fish", "Fish form"});
    items->push_back({"song_spirit", "Spirit form"});
    items->push_back({"transport_veil01", "Transport to The Veil top left area"});
    items->push_back({"transport_veil02", "Transport to The Veil top right area"});
    items->push_back({"transport_openwater03", "Transport to Open waters top right area"});
    items->push_back({"transport_forest04", "Transport to Kelp Forest bottom left area"});
    items->push_back({"transport_mainarea", "Transport to home waters"});
    items->push_back({"transport_abyss03", "Transport to The Abyss right area"});
    items->push_back({"transport_finalboss", "Transport to The Creator"});
    items->push_back({"transport_forest05", "Transport to Simon says"});
    items->push_back({"transport_seahorse", "Transport to Arnassi Ruins right area"});
    items->push_back({"door_to_cathedral", "Opening door to the cathedral"});
    items->push_back({"door_to_body", "Body's tongue removed"});
    items->push_back({"trap_poison", "Poison trap"});
    items->push_back({"trap_blind", "Blind trap"});
    items->push_back({"trap_rainbow", "Rainbow trap"});
    items->push_back({"trap_mute", "Mute trap"});
    items->push_back({"progressive_recipe_loaf","Progressive Loaf"});
    items->push_back({"progressive_recipe_soup","Progressive Soup"});
    items->push_back({"progressive_recipe_cake","Progressive Cake"});
    items->push_back({"progressive_recipe_poultice","Progressive Poultice"});
    items->push_back({"progressive_recipe_roll","Progressive Roll"});
    items->push_back({"progressive_recipe_perogi","Progressive Perogi"});
    items->push_back({"progressive_recipe_ice_cream","Progressive Ice Cream"});
}


/**
 * Initialize `collectibles`
 */
void Randomizer::initialiseCollectibles() const {
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
    delete(locations);
    delete(items);
    delete(ingredients);
    delete(collectibles);
    delete(nextMessages);
}

/**
 * Get a new transport to a game location
 * @param aItem The transport item to activate
 */
void Randomizer::receivingTransport(const item_t *aItem) {
    int lAreaStringIndex = 0;
    if (aItem->name == "transport_veil01") {
        dsq->continuity.setFlag(FLAG_TRANSTURTLE_VEIL01, 1);
        lAreaStringIndex = 1014;
    } else if (aItem->name == "transport_veil02") {
        dsq->continuity.setFlag(FLAG_TRANSTURTLE_VEIL02, 1);
        lAreaStringIndex = 1014;
    } else if (aItem->name == "transport_openwater03") {
        dsq->continuity.setFlag(FLAG_TRANSTURTLE_OPENWATER03, 1);
        lAreaStringIndex = 1009;
    } else if (aItem->name == "transport_forest04") {
        dsq->continuity.setFlag(FLAG_TRANSTURTLE_FOREST04, 1);
        lAreaStringIndex = 1010;
    } else if (aItem->name == "transport_mainarea") {
        dsq->continuity.setFlag(FLAG_TRANSTURTLE_MAINAREA, 1);
        lAreaStringIndex = 1008;
    } else if (aItem->name == "transport_abyss03") {
        dsq->continuity.setFlag(FLAG_TRANSTURTLE_ABYSS03, 1);
        lAreaStringIndex = 1015;
    } else if (aItem->name == "transport_finalboss") {
        dsq->continuity.setFlag(FLAG_TRANSTURTLE_FINALBOSS, 1);
        lAreaStringIndex = 1021;
    } else if (aItem->name == "transport_forest05") {
        dsq->continuity.setFlag(FLAG_TRANSTURTLE_FOREST05, 1);
        lAreaStringIndex = 1010;
    } else if (aItem->name == "transport_seahorse") {
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
 * @param aItem The collectible item to activate
 */
void Randomizer::receivingCollectible(const item_t *aItem) const {
    collectible_t *lCollectible = nullptr;
    for (int i = 0; i < collectibles->size() && !lCollectible; i = i + 1) {
        if (collectibles->at(i).name == aItem->name) {
            lCollectible = &collectibles->at(i);
        }
    }
    assert(lCollectible && "The Collectible is not valid!");
    std::ostringstream lFileNameStream;
    lFileNameStream << "collectibles/" << lCollectible->imageFile;
    if (dsq->game->avatar != nullptr) {
        dsq->game->pickupItemEffects(lFileNameStream.str());
    }
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
 * @param aItem The song item to activate
 */
void Randomizer::receivingSong(const item_t *aItem) {
    int lSongType = 0;
    int lStrId = 0;
    if (aItem->name == "song_li") { // Li song
        if (dsq->continuity.getFlag(FLAG_LI) == 0) {
            dsq->continuity.setFlag(FLAG_LI, 100);
            lSongType = SONG_LI;
            lStrId = 42;
            if (dsq->game->avatar) {
                dsq->game->li = dsq->game->createEntity("li", 0, Vector (dsq->game->avatar->position.x, dsq->game->avatar->position.y), 0,
                                                        false, "Li", ET_ENEMY, true);
            }
        }
    } else if (aItem->name == "song_shield") { // Shield song
        if (!dsq->continuity.hasSong(SONG_SHIELDAURA)) {
            lSongType = SONG_SHIELDAURA;
            lStrId = 35;
        }
    } else if (aItem->name == "song_dual") { // Dual song
        if (!dsq->continuity.hasSong(SONG_DUALFORM)) {
            lSongType = SONG_DUALFORM;
            lStrId = 43;
        }
    } else if (aItem->name == "song_beast") { // Beast song
        if (!dsq->continuity.hasSong(SONG_BEASTFORM)) {
            lSongType = SONG_BEASTFORM;
            lStrId = 38;
        }
    } else if (aItem->name == "song_sun") { // Sun song
        if (!dsq->continuity.hasSong(SONG_SUNFORM)) {
            lSongType = SONG_SUNFORM;
            lStrId = 41;
        }
    } else if (aItem->name == "song_nature") { // Nature song
        if (!dsq->continuity.hasSong(SONG_NATUREFORM)) {
            lSongType = SONG_NATUREFORM;
            lStrId = 40;
        }
    } else if (aItem->name == "song_energy") { // Energy song
        if (!dsq->continuity.hasSong(SONG_ENERGYFORM)) {
            lSongType = SONG_ENERGYFORM;
            lStrId = 37;
        }
    } else if (aItem->name == "song_bind") { // Bind song
        if (!dsq->continuity.hasSong(SONG_BIND)) {
            lSongType = SONG_BIND;
            lStrId = 36;
        }
    } else if (aItem->name == "song_fish") { // Fish song
        if (!dsq->continuity.hasSong(SONG_FISHFORM)) {
            lSongType = SONG_FISHFORM;
            lStrId = 39;
        }
    } else if (aItem->name == "song_spirit") { // Fish song
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
 * Get a new ingredient to receive in the local game
 * @param aIngredientName The name of the ingredient to receive
 * @param aCount The number of ingredient to receive
 */
void Randomizer::receivingIngredient(const std::string& aIngredientName, int aCount) {
    IngredientData *lIngredient = dsq->continuity.getIngredientDataByName(aIngredientName);
    dsq->continuity.pickupIngredient(lIngredient, aCount);
    for (int i = 0; i < aCount; i = i + 1) {
        if (dsq->game->avatar != nullptr) {
            dsq->game->pickupIngredientEffects(lIngredient);
        }
    }
}

/**
 * Received an health upgrade
 */
void Randomizer::receivingUpgradeHealth() {
    if (dsq->game->avatar) {
        if (dsq->game->avatar->health < 10) {
            dsq->continuity.upgradeHealth();
        }
    } else {
        mustUpgradeHealth = true;
    }
    dsq->game->pickupItemEffects("healthupgrade/whole");
}

/**
 * Received a door opening item
 * @param aItem The item that has been received.
 */
void Randomizer::receivingDoorOpening(const item_t *aItem) {
    if (aItem->name == "door_to_cathedral" && dsq->continuity.getFlag(FLAG_MITHALAS_THRONEROOM) != 1) {
        dsq->continuity.setFlag(FLAG_MITHALAS_THRONEROOM, 1);
        dsq->game->pickupItemEffects("seal-prince");
    }
    if (aItem->name == "door_to_body" && dsq->continuity.getFlag(FLAG_REMOVE_TONGUE) != 1) {
        dsq->continuity.setFlag(FLAG_REMOVE_TONGUE, 1);
        dsq->game->pickupItemEffects("final-tongue");
        for (size_t i = 0; dsq->entities[i] != nullptr; i = i + 1) {
            if (dsq->entities[i]->name == "finaltongue") {
                dsq->entities[i]->setState(STATE_OPEN, -1, false);
            }
        }
    }


}

/**
 * Received a trap
 * @param aItem The item that has been received.
 */
void Randomizer::receivingTrap(const item_t *aItem) {
    if (aItem->name == "trap_poison") {
        if (dsq->game->avatar != nullptr) {
            dsq->game->avatar->setPoison(0.5, 10);
        }
        dsq->game->pickupItemEffects("particles/bubble");
    } else if (aItem->name == "trap_blind") {
        if (dsq->game->avatar != nullptr) {
            dsq->game->avatar->setBlind((rand()%20) + 10);
        }
        dsq->game->pickupItemEffects("particles/blinder");
    } else if (aItem->name == "trap_rainbow") {
        dsq->continuity.setTrip((rand()%20) + 10);
        dsq->game->pickupItemEffects("particles/tripper");
    } else if (aItem->name == "trap_mute") {
        if (dsq->game->avatar != nullptr) {
            dsq->game->avatar->changeForm(FORM_NORMAL);
            dsq->game->avatar->setBlockSinging(true);
            mute_timer.start(20);
            is_muted = true;
        }
        dsq->game->pickupItemEffects("gui/SongBubbles");
    }
}

/**
 * Received a progressive recipe
 * @param aItem The item that has been received.
 */
void Randomizer::receivingProgressiveRecipe(const item_t *aItem) {
    IngredientType lCategory = IT_ANYTHING;
    int *lProgressiveIndex = nullptr;
    if (aItem->name == "progressive_recipe_loaf") {
        lCategory = IT_LOAF;
        lProgressiveIndex = &progressiveLoafIndex;
    } else if (aItem->name == "progressive_recipe_soup") {
        lCategory = IT_SOUP;
        lProgressiveIndex = &progressiveSoupIndex;
    } else if (aItem->name == "progressive_recipe_cake") {
        lCategory = IT_CAKE;
        lProgressiveIndex = &progressiveCakeIndex;
    } else if (aItem->name == "progressive_recipe_poultice") {
        lCategory = IT_POULTICE;
        lProgressiveIndex = &progressivePoulticeIndex;
    } else if (aItem->name == "progressive_recipe_roll") {
        lCategory = IT_ROLL;
        lProgressiveIndex = &progressiveRollIndex;
    } else if (aItem->name == "progressive_recipe_perogi") {
        lCategory = IT_PEROGI;
        lProgressiveIndex = &progressivePerogiIndex;
    } else if (aItem->name == "progressive_recipe_ice_cream") {
        lCategory = IT_ICECREAM;
        lProgressiveIndex = &progressiveIceCreamIndex;
    }
    if (lCategory > -1) {
        int lIndex = 0;
        ingredient_t *lIngredient = nullptr;
        for (int i = 0; i < ingredients->size() && lIngredient == nullptr; i = i + 1) {
            if (ingredients->at(i).category == lCategory) {
                if (lIndex >= *lProgressiveIndex) {
                    lIngredient = &(ingredients->at(i));
                } else {
                    lIndex = lIndex + 1;
                }
            }
        }
        if (lIngredient != nullptr) {
            *lProgressiveIndex = *lProgressiveIndex + 1;
        } else {
            lIngredient = getRandomIngredient(lCategory);
        }
        receivingIngredient(lIngredient->name, 1);
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
        item_t * lItem = getItemByName(aItem);
        lMessageStream << lItem->message;
        if (aCount > 1) {
            lMessageStream << " x " << aCount;
        }
        std::string lIngredientName = aItem.substr(11);
        receivingIngredient(lIngredientName, aCount);
    } else if (aItem.compare(0, 11, "upgrade_wok") == 0) {
        lMessageStream << "Upgrade: Wok";
        dsq->continuity.setFlag(FLAG_UPGRADE_WOK, 1);
        dsq->game->pickupItemEffects("gui/wok");
    } else if (aItem.compare(0, 14, "upgrade_health") == 0) {
        lMessageStream << "Upgrade: Health";
        receivingUpgradeHealth();
    } else if (aItem.compare(0, 11, "collectible") == 0) {
        item_t *lItem = getItemByName(aItem);
        lMessageStream << lItem->message;
        receivingCollectible(lItem);
    } else if (aItem.compare(0, 5, "song_") == 0) {
        item_t *lItem = getItemByName(aItem);
        lMessageStream << lItem->message;
        receivingSong(lItem);
    } else if (aItem.compare(0, 10, "transport_") == 0) {
        item_t *lItem = getItemByName(aItem);
        lMessageStream << lItem->message;
        receivingTransport(lItem);
        dsq->game->pickupItemEffects("gems/turtle");
    } else if (aItem.compare(0, 5, "door_") == 0) {
        item_t *lItem = getItemByName(aItem);
        lMessageStream << lItem->message;
        receivingDoorOpening(lItem);
    } else if (aItem.compare(0, 5, "trap_") == 0) {
        item_t *lItem = getItemByName(aItem);
        lMessageStream << lItem->message;
        receivingTrap(lItem);
    } else if (aItem.compare(0, 19, "progressive_recipe_") == 0) {
        item_t *lItem = getItemByName(aItem);
        lMessageStream << lItem->message;
        receivingProgressiveRecipe(lItem);
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
 * Retreive a location from a location Id
 * @param aId The Id of the location to retreive
 * @return A pointer to the location_t object
 */
location_t *Randomizer::getLocationById(const std::string& aId)
{
    location_t *result = nullptr;
    int lIndex = getLocationIndex(aId);
    if (lIndex != -1) {
        result = getLocationByIndex(lIndex);
    }
    return result;
}

/**
 * Retreive the index of a location
 * @param id The Id of the location to retreive
 * @return The index of the location in the location list
 */
int Randomizer::getLocationIndex(const std::string& aId)
{
    int result = -1;
    for (int i = 0; i < locations->size() && result == -1; i = i + 1) {
        if (getLocationByIndex(i)->id == aId) {
            result = i;
        }
    }
    return result;
}

/**
 * Retreive the location at a certain index
 * @param aIndex The index of the location to retreive
 * @return The location
 */
location_t *Randomizer::getLocationByIndex(int aIndex) {
    location_t * lResult = nullptr;
    if (aIndex >= 0 && aIndex < locations->size()) {
        lResult = &(locations->at(aIndex));
    }
    return lResult;
}

/**
 * Retreive the item at a certain index
 * @param aIndex The index of the item to retreive
 * @return The item
 */
item_t *Randomizer::getItemByIndex(int aIndex) {
    item_t * lResult = nullptr;
    if (aIndex >= 0 && aIndex < items->size()) {
        lResult = &(items->at(aIndex));
    }
    return lResult;
}

/**
 * Retreive an item from an item name
 * @param aItem The item name of the item to retreive
 * @return A pointer to the item_t object
 */
item_t *Randomizer::getItemByName(const std::string& aItem)
{
    item_t *result = nullptr;
    for (int i = 0; i < items->size() && !result; i = i + 1) {
        item_t * lCheck = getItemByIndex(i);
        if (lCheck->name == aItem) {
            result = lCheck;
        }
    }
    return result;
}

/**
 * Retreive the maximum number of the same ingredients that can be stacked on the ingredient inventory
 * @return The maximum number
 */
int Randomizer::getMaximumIngredientAmount() const {
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
Entity *Randomizer::spawnRecipe(const Recipe * aRecipe, const Vector &aPosition, int aTimes, int aOut) {
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
 * @param aEntity The entity that spawn the recipe dish
 * @param aRecipe The recipe to spawn
 * @param aIngredientData The ingredient that represent the recipe
 */
void Randomizer::spawnRecipeFromEntity(Entity *aEntity, const Recipe * aRecipe, IngredientData *aIngredientData) {
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
     * The unique String for the Randomizer
     * @return The String of the Randomizer
     */
std::string Randomizer::getUniqueString() {
    return getUid();
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
bool Randomizer::getBlindGoal() const {
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
bool Randomizer::getIsAquarianTranslated() const{
    return isAquarianTranslated;
}

/**
 * Get the file name (without path and extension) of the graphic file to show Aquarian text
 * @return The filename
 */
std::string Randomizer::getAquarianGfx() const{
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
void Randomizer::writeHelpData(std::stringstream *aMessageStream, const std::string& aText, int aFlag){
    if (aFlag) {
        *aMessageStream << "[X] ";
    } else {
        *aMessageStream << " [ ] ";
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
    writeHelpData(&lMessageStream, "Baby Dumbo", dsq->continuity.getFlag(FLAG_COLLECTIBLE_DUMBO));
    Recipe *lRecipe = getRecipe("hotsoup");
    writeHelpData(&lMessageStream, "Hot soup", lRecipe && lRecipe->isKnown());
    writeHelpData(&lMessageStream, "Arnassi Armor",
        dsq->continuity.getFlag(FLAG_COLLECTIBLE_SEAHORSECOSTUME));
    writeHelpData(&lMessageStream, "Transport to The Veil top left area",
        dsq->continuity.getFlag(FLAG_TRANSTURTLE_VEIL01));
    writeHelpData(&lMessageStream, "Transport to The Veil top right area",
        dsq->continuity.getFlag(FLAG_TRANSTURTLE_VEIL02));
    writeHelpData(&lMessageStream, "Transport to Open waters top right area",
        dsq->continuity.getFlag(FLAG_TRANSTURTLE_OPENWATER03));
    writeHelpData(&lMessageStream, "Transport to Kelp Forest bottom left area",
        dsq->continuity.getFlag(FLAG_TRANSTURTLE_FOREST04));
    writeHelpData(&lMessageStream, "Transport to home waters",
        dsq->continuity.getFlag(FLAG_TRANSTURTLE_MAINAREA));
    if (!killFourGodsGoal) {
        writeHelpData(&lMessageStream, "Transport to The Abyss right area",
            dsq->continuity.getFlag(FLAG_TRANSTURTLE_ABYSS03));
    }
    if (killCreatorGoal) {
        writeHelpData(&lMessageStream, "Transport to The Creator",
        dsq->continuity.getFlag(FLAG_TRANSTURTLE_FINALBOSS));
    }
    writeHelpData(&lMessageStream, "Transport to Simon says",
        dsq->continuity.getFlag(FLAG_TRANSTURTLE_FOREST05));
    writeHelpData(&lMessageStream, "Transport to Arnassi Ruins right area",
    dsq->continuity.getFlag(FLAG_TRANSTURTLE_SEAHORSE));
    writeHelpData(&lMessageStream, "Door to the Cathedral opened",
    dsq->continuity.getFlag(FLAG_MITHALAS_THRONEROOM));
    writeHelpData(&lMessageStream, "Body's tongue removed",
        dsq->continuity.getFlag(FLAG_REMOVE_TONGUE));
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
            lMessageStream << miniBossesToKill << " mini bosses beaten are needed to access ";
        } else if (miniBossesToKill == 1) {
            lMessageStream << "1 mini boss beaten are needed to access ";
        } else {
            lMessageStream << "No mini boss beaten are needed to access ";
        }
        if (killCreatorGoal) {
            lMessageStream << "final boss.\n\n\n";
        } else {
            lMessageStream << "goal.\n\n\n";

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
    if (killFourGodsGoal) {
        lMessageStream << "[Gods beaten]\n";
    } else {
        lMessageStream << "[Bosses beaten]\n";
    }
    writeHelpData(&lMessageStream, "Fallen God", dsq->continuity.getFlag(FLAG_ENERGYBOSSDEAD));
    writeHelpData(&lMessageStream, "Mithalan God", dsq->continuity.getFlag(FLAG_BOSS_MITHALA));
    writeHelpData(&lMessageStream, "Drunian God", dsq->continuity.getFlag(FLAG_BOSS_FOREST));
    writeHelpData(&lMessageStream, "Lumerean God", dsq->continuity.getFlag(FLAG_BOSS_SUNWORM));
    if (!killFourGodsGoal) {
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
    } else {
        lMessageStream << "\n";
    }
    aData += lMessageStream.str();
}

/**
 * Add information about secrets obtained in `data`.
 *
 * @param aData Where the information about item should be put.
 */
void Randomizer::appendSecretHelpData(std::string &aData) {
    if (!killFourGodsGoal) {
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
}

/**
 * Add information about locations in `data`.
 *
 * @param aData Where the information about item should be put.
 */
void Randomizer::appendLocationsHelpData(std::string &aData) {
    std::stringstream lMessageStream;
    lMessageStream << "[Locations obtained]\n";
    if (killFourGodsGoal) {
        for (int i = 0; i < LOCATIONS_FOUR_GODS_SIZE; i = i + 1) {
            writeHelpData(&lMessageStream, locations->at(locationsOrderFourGods[i]).name,
                          dsq->continuity.getFlag(locations->at(locationsOrderFourGods[i]).flag));
        }
    } else {
        for (int i = 0; i < LOCATIONS_SIZE; i = i + 1) {
            writeHelpData(&lMessageStream, locations->at(locationsOrder[i]).name,
                          dsq->continuity.getFlag(locations->at(locationsOrder[i]).flag));
        }
    }
    lMessageStream << "\n\n";
    aData += lMessageStream.str();
}



/**
 * A new or saves game has been load
   @param aNewGame True if a new game is launched.
 */
void Randomizer::onLoad(bool aNewGame){
    justLoading = true;
    is_muted = false;
    if (removeTongue) {
        dsq->continuity.setFlag(FLAG_REMOVE_TONGUE, 1);
    }
    if (aNewGame) {
        if (blindGoal) {
            dsq->continuity.setFlag(FLAG_BLIND_GOAL, 1);
        } else {
            dsq->continuity.setFlag(FLAG_BLIND_GOAL, 0);
        }
    } else {
        if (!core->getShiftState()) {
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
    }
    for (int i = 0; i < dsq->continuity.worldMap.getNumWorldMapTiles(); i++) {
        WorldMapTile *tile = dsq->continuity.worldMap.getWorldMapTile(i);
        if (tile->stringIndex != 1020) {
            tile->revealed = true;
        }

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
    if (gameControlReady() && justLoading && dsq->game->avatar) {
        if (dsq->game->avatar->health <= 0) {
            if (isSaveHeal()) {
                dsq->game->avatar->revive();
            } else {
                dsq->game->avatar->health = 0;
                dsq->game->avatar->heal(0.5);
            }
        }
        if (dsq->game->avatar->getPoison() and dsq->game->avatar->health < 3) {
            dsq->game->avatar->health = 0;
            dsq->game->avatar->heal(3.0);
        }
        justLoading = false;
    }
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
    if (mustUpgradeHealth && dsq->game->avatar) {
        receivingUpgradeHealth();
    }
    if (inGame && killFourGodsGoal) {
        manageFourGodsEnding();
    }
}

/**
 * Lunched at each game loop iteration
 */
void Randomizer::onUpdate(float aTimestamp) {
    if (is_muted && dsq->game->isActive() && !dsq->game->isPaused()) {
        mute_timer.update(aTimestamp);
        if (mute_timer.isDone() && dsq->game->avatar != nullptr) {
            dsq->game->avatar->setBlockSinging(false);
            mute_timer.stop();
            is_muted = false;
        }
    }
}

/**
 * Check if it is the end of the four gods run
 */
void Randomizer::manageFourGodsEnding() {
    if (dsq->continuity.getFlag(FLAG_ENERGYBOSSDEAD) && dsq->continuity.getFlag(FLAG_BOSS_MITHALA) &&
        dsq->continuity.getFlag(FLAG_BOSS_FOREST) && dsq->continuity.getFlag(FLAG_BOSS_SUNWORM)) {
        if (!dsq->continuity.getFlag(FLAG_FOUR_GODS_MESSAGE) and gameControlReady()) {
            std::stringstream lMessageStream;
            lMessageStream << "You have beaten the four gods. Now you must beat the Creator to complete your goal. " <<
                              "The transportation turtle inside The Body has been activated and you can travel " <<
                              "directly to the final boss area.";
            showTextPanel(lMessageStream.str(), &dsq->font, true ,false);
            dsq->continuity.setFlag(FLAG_TRANSTURTLE_FINALBOSS, 1);
            dsq->continuity.setFlag(FLAG_FOUR_GODS_MESSAGE, 1);
        }
    }
}

/**
 * True when the game should skip the final boss 3rd form (hide and seek)
 */
bool Randomizer::mustSkipFinalBoss3rdForm() const {
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
    return dsq->continuity.hasLi() && dsq->continuity.hasSong(SONG_DUALFORM) &&
           dsq->continuity.hasSong(SONG_ENERGYFORM) && dsq->continuity.hasSong(SONG_SUNFORM)
           && dsq->continuity.hasSong(SONG_BIND) && miniBossCount() >= miniBossesToKill &&
           (killFourGodsGoal || bigBossCount() >= bigBossesToKill) && (!secretsNeeded || (secretsFound() == 3)) &&
           (!killFourGodsGoal || dsq->continuity.getFlag(FLAG_ENERGYBOSSDEAD) &&
            dsq->continuity.getFlag(FLAG_BOSS_MITHALA) && dsq->continuity.getFlag(FLAG_BOSS_FOREST) &&
            dsq->continuity.getFlag(FLAG_BOSS_SUNWORM));
}

/**
 *
 * @param aCount When getting to the final boss and you don't have the requirements, show a requirements.
 * @param aObjective The objective to validate and show
 * @param aMessage The message to show if the requirement is not obtained.
 */
void Randomizer::showHint(int aCount, int aObjective, const std::string& aMessage) {
    if (aCount < aObjective) {
        std::stringstream lMessageStream;
        lMessageStream << "You have " << aCount << " " << aMessage << ". Needing " << aObjective;
        if (killCreatorGoal) {
            lMessageStream << " to access final boss.";
        } else {
            lMessageStream << " to goal.";
        }
        showText(lMessageStream.str());
    }
}

/**
 * Event for when the user wish to open the final boss door
 */
void Randomizer::onYesOpenFinalDoor() {
    onOkPanel();
    openFinalDoor = true;
}

/**
 * Show a hint of the final boss
 *
 * @param aMessageStream Where to ptint the hint
 * @param aChecked If the hint must be checked or not.
 * @param aText The hint that have to be printed.
 */
void Randomizer::showIndividualHintFinalBoss(std::stringstream *aMessageStream, bool aChecked,const std::string& aText) {
    if (aChecked) {
        *aMessageStream << "[X] ";
    } else {
        *aMessageStream << "[  ] ";
    }
    *aMessageStream << aText << std::endl;
}

/**
 * Show a number hint of the final boss
 *
 * @param aMessageStream Where to ptint the hint
 * @param aNumber Number of elements that has been obtained by the user
 * @param aNeeded Number of elements needed
 * @param aText The hint that have to be printed.
 */
void Randomizer::showNumberHintFinalBoss(std::stringstream *aMessageStream, int aNumber, int aNeeded,
                                         const std::string& aText) {
    std::stringstream lMessageStream;
    lMessageStream << aText << " : " << aNumber << "/" << aNeeded;
    showIndividualHintFinalBoss(aMessageStream, aNumber >= aNeeded, lMessageStream.str());
}

/**
 * Show what is missing to access final boss.
 *
 * @return True if the door must be opened, False if not
 */
bool Randomizer::showHintFinalBoss() {
    std::stringstream lMessageStream;

    lMessageStream << "Here are the requirements to enter the door to the creator:" << std::endl;
    showIndividualHintFinalBoss(&lMessageStream, dsq->continuity.hasLi(), "Li");
    if (miniBossesToKill > 0) {
        showNumberHintFinalBoss(&lMessageStream, miniBossCount(), miniBossesToKill, "Mini bosses");
    }
    if (!killFourGodsGoal && bigBossesToKill > 0) {
        showNumberHintFinalBoss(&lMessageStream, bigBossCount(), bigBossesToKill, "Big bosses");
    }
    if (secretsNeeded) {
        showNumberHintFinalBoss(&lMessageStream, secretsFound(), 3, "Secret memories");
    }
    if (killFourGodsGoal) {
        showIndividualHintFinalBoss(&lMessageStream, dsq->continuity.getFlag(FLAG_ENERGYBOSSDEAD) &&
            dsq->continuity.getFlag(FLAG_BOSS_MITHALA) && dsq->continuity.getFlag(FLAG_BOSS_FOREST) &&
            dsq->continuity.getFlag(FLAG_BOSS_SUNWORM), "Four gods beaten");
    }
    lMessageStream << std::endl << std::endl << "Here are the songs and forms logically required to beat the creator:" << std::endl;
    showIndividualHintFinalBoss(&lMessageStream, dsq->continuity.hasSong(SONG_ENERGYFORM),
                                "Energy Form");
    showIndividualHintFinalBoss(&lMessageStream, dsq->continuity.hasSong(SONG_BIND),
                                "Bind Song");
    showIndividualHintFinalBoss(&lMessageStream, dsq->continuity.hasSong(SONG_SUNFORM),
                                "Sun Form");
    showIndividualHintFinalBoss(&lMessageStream, dsq->continuity.hasSong(SONG_DUALFORM),
                                "Dual Form");
    openFinalDoor = false;
    if (dsq->continuity.hasLi() && miniBossCount() >= miniBossesToKill &&
        (killFourGodsGoal || bigBossCount() >= bigBossesToKill) &&
        (!secretsNeeded || secretsFound() >= 3) && (!killFourGodsGoal || dsq->continuity.getFlag(FLAG_ENERGYBOSSDEAD) &&
        dsq->continuity.getFlag(FLAG_BOSS_MITHALA) && dsq->continuity.getFlag(FLAG_BOSS_FOREST) &&
        dsq->continuity.getFlag(FLAG_BOSS_SUNWORM))) {
        lMessageStream << std::endl << std::endl <<
            "You do not have what it takes to beat the creator. Do you still want to proceed?" << std::endl;
        showTextPanel(lMessageStream.str(), &dsq->mediumFont, false, true,
            MakeFunctionEvent(Randomizer,onYesOpenFinalDoor));
    } else {
        showTextPanel(lMessageStream.str(), &dsq->mediumFont, false, false);
    }
    dsq->continuity.setFlag(FLAG_BLIND_GOAL, 0);
    return openFinalDoor;
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
 * @param aY The vertical coordinate of the top corner of the text to show
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
 * Launched when a scene is loading
 *
 * @param aScene The scene name that is loading
 */
void Randomizer::onLoadScene(std::string aScene) {
    if (aScene == "title") {

        seedNumberText = new BitmapText(&dsq->smallFont);
        {
            std::stringstream lStream;
            lStream << "Seed number: " << getUid();
            seedNumberText->setText(lStream.str());
            seedNumberText->position = Vector(790 - (seedNumberText->getActualWidth() * 0.7), 575);
            seedNumberText->followCamera = 1;
            seedNumberText->setAlign(ALIGN_LEFT);
            seedNumberText->scale = Vector(0.7, 0.7);
            seedNumberText->alphaMod = 0.75;
            seedNumberText->alpha = 1;
        }
        dsq->addRenderObject(seedNumberText, LR_REGISTER_TEXT);
    } else {
        if (seedNumberText) {
            seedNumberText->safeKill();
            seedNumberText = nullptr;
        }
    }
    if (killFourGodsGoal && (aScene.substr(0, 5) == "abyss" || aScene == "boilerroom" || aScene == "whale" ||
            aScene.substr(0, 5) == "final" || aScene == "frozenveil" || aScene == "icecave" ||
            aScene == "kingjellycave" || aScene.substr(0, 10) == "sunkencity" || aScene == "bubblecave02")) {
        for (size_t i = 0; dsq->entities[i] != nullptr; i = i + 1) {
            if (dsq->entities[i]->name == "singbulb" || dsq->entities[i]->name == "sunkencrate" ||
                    dsq->entities[i]->name.substr(0, 11) == "collectible" ||
                    dsq->entities[i]->name.substr(0, 13) == "healthupgrade") {
                dsq->entities[i]->safeKill();
            }
        }
    }
}

/**
 * The goal is a four gods mode
 */
bool Randomizer::isFourGodsGoal() {
    return killFourGodsGoal;
}

/**
 * Event for the Transportation menu to cancel the process.
 */
void Randomizer::onCancelTransportation() {
    transportationDone = true;
}

/**
 * Event for the Transportation menu to manage the Naija's home destination.
 */
void Randomizer::onNaijaHomeTransportation() {
    transportationSelected = FLAG_TRANSTURTLE_NAIJAHOME;
    disableTransportationMenu();
    if (dsq->confirm("Go to Naija's home?","", false, 0.0)) {
        transportationDone = true;
    }
}

/**
 * Event for the Transportation menu to manage the Naija's rock destination
 */
void Randomizer::onNaijaRockTransportation() {
    transportationSelected = FLAG_TRANSTURTLE_NAIJAROCK;
    disableTransportationMenu();
    if (dsq->confirm("Go to Naija's rock?","", false, 0.0)) {
        transportationDone = true;
    }
    enableTransportationMenu();
}

/**
 * Event for the Transportation menu to manage the Veil left area destination
 */
void Randomizer::onVeil1Transportation() {
    transportationSelected = FLAG_TRANSTURTLE_VEIL01;
    disableTransportationMenu();
    if (dsq->confirm("Go to the Veil left area?","", false, 0.0)) {
        transportationDone = true;
    }
    enableTransportationMenu();
}

/**
 * Event for the Transportation menu to manage the Veil right area destination
 */
void Randomizer::onVeil2Transportation() {
    transportationSelected = FLAG_TRANSTURTLE_VEIL02;
    disableTransportationMenu();
    if (dsq->confirm("Go to the Veil right area?","", false, 0.0)) {
        transportationDone = true;
    }
    enableTransportationMenu();
}

/**
 * Event for the Transportation menu to manage the Arnassi Ruins destination
 */
void Randomizer::onArnassiTransportation() {
    transportationSelected = FLAG_TRANSTURTLE_SEAHORSE;
    disableTransportationMenu();
    if (dsq->confirm("Go to Arnassi Ruins?","", false, 0.0)) {
        transportationDone = true;
    }
    enableTransportationMenu();
}

/**
 * Event for the Transportation menu to manage the Kelp Forest destination
 */
void Randomizer::onForestTransportation() {
    transportationSelected = FLAG_TRANSTURTLE_FOREST04;
    disableTransportationMenu();
    if (dsq->confirm("Go to Kelp Forest?","", false, 0.0)) {
        transportationDone = true;
    }
    enableTransportationMenu();
}

/**
 * Event for the Transportation menu to manage the Simon says destination
 */
void Randomizer::onSimonTransportation() {
    transportationSelected = FLAG_TRANSTURTLE_FOREST05;
    disableTransportationMenu();
    if (dsq->confirm("Go to Simon Says?","", false, 0.0)) {
        transportationDone = true;
    }
    enableTransportationMenu();
}

/**
 * Event for the Transportation menu to manage the Abyss destination
 */
void Randomizer::onAbyssTransportation() {
    transportationSelected = FLAG_TRANSTURTLE_ABYSS03;
    disableTransportationMenu();
    if (dsq->confirm("Go to the Abyss?","", false, 0.0)) {
        transportationDone = true;
    }
    enableTransportationMenu();
}

/**
 * Event for the Transportation menu to manage the Body destination
 */
void Randomizer::onBodyTransportation() {
    transportationSelected = FLAG_TRANSTURTLE_FINALBOSS;
    disableTransportationMenu();
    if (dsq->confirm("Go to the Body?","", false, 0.0)) {
        transportationDone = true;
    }
    enableTransportationMenu();
}

/**
 * Event for the Transportation menu to manage the Open Waters destination
 */
void Randomizer::onOpenWaterTransportation() {
    transportationSelected = FLAG_TRANSTURTLE_OPENWATER03;
    disableTransportationMenu();
    if (dsq->confirm("Go to Open Waters?","", false, 0.0)) {
        transportationDone = true;
    }
    enableTransportationMenu();
}

/**
 * Event for the Transportation menu to manage the Home Waters destination
 */
void Randomizer::onHomeWaterTransportation() {
    transportationSelected = FLAG_TRANSTURTLE_MAINAREA;
    disableTransportationMenu();
    if (dsq->confirm("Go to Home Waters?","", false, 0.0)) {
        transportationDone = true;
    }
    enableTransportationMenu();
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
    dsq->game->addRenderObject(aItem, LR_RANDOMIZER_PANEL);

    aItemLabel->color = 0;
    aItemLabel->setText(aText);
    aItemLabel->color = 0;
    aItemLabel->followCamera = 1;
    aItemLabel->position = Vector(aX, aY + 30);
    aItemLabel->scale = Vector(1.0, 1.0);
    game->addRenderObject(aItemLabel, LR_RANDOMIZER_PANEL);
}

/**
 * When the user pressed escape.
 */
void Randomizer::onPressEscape() {
    onCancelTransportation();
}

/**
 * Assing the saveHeal value to a value
 * @param aValue The value to assing to saveHeal
 */
void Randomizer::setSaveHeal(bool aValue) {
    saveHeal = aValue;
}

/**
 * Save point must heal the user.

 * @return True if the save rystal must heal the character. False if not.
 */
bool Randomizer::isSaveHeal() {
    return saveHeal;
}

/**
 * Temporarrly disable the transportation menu (re-enable with `enableTransportationMenu`)
 */
void Randomizer::disableTransportationMenu() {
    menuCancel->disableInput();
    homeWater->disableInput();
    openWater->disableInput();
    forest->disableInput();
    veil1->disableInput();
    veil2->disableInput();
    arnassi->disableInput();
    abyss->disableInput();
    body->disableInput();
    simon->disableInput();
    returnBase->disableInput();
}

/**
 * Re-enable the transportation menu after a `disableTransportationMenu`
 */
void Randomizer::enableTransportationMenu() {
    menuCancel->enableInput();
    homeWater->enableInput();
    openWater->enableInput();
    forest->enableInput();
    veil1->enableInput();
    veil2->enableInput();
    arnassi->enableInput();
    abyss->enableInput();
    body->enableInput();
    simon->enableInput();
    returnBase->enableInput();
}

/**
 * Show the transportation menu and return the selected destination flag.
 *
 * @return the selected destination flag
 */
int Randomizer::askTransportation() {
    transportationSelected = 0;
    if (gameControlReady()) {
        transportationDone = false;
        dsq->game->togglePause(true);
        sound->playSfx("menu-open");
        Quad *bgimage = new Quad("gui/recipe-scroll.png", Vector(400,300));
        bgimage->followCamera = 1;
        bgimage->alpha = 0;
        bgimage->alpha.interpolateTo(1, 0.5);
        //bgLabel->setWidthHeight(512*0.9f, 256*0.9f);
        bgimage->scale = Vector(0, 0);
        bgimage->scale.interpolateTo(Vector(1.5,1), 0.5);
        game->addRenderObject(bgimage, LR_RANDOMIZER_PANEL);
        dsq->main(0.5);

        BitmapText *lTitle = new BitmapText(&dsq->font);
        lTitle->color = 0;
        lTitle->setFontSize(50);
        lTitle->followCamera = 1;
        lTitle->position = Vector(400,75);
        lTitle->setText("Transportation turtle\nDestinations");
        lTitle->scale = Vector(1.0, 1.0);
        game->addRenderObject(lTitle, LR_RANDOMIZER_PANEL);

        float lVerticalPosition = 200.0;
        float lHorizontalPosition = 175.0;
        bool lFirst = true;

        menuCancel = new AquariaMenuItem;

        homeWater = new AquariaMenuItem;
        BitmapText *lHomeWaterText = new BitmapText(&dsq->smallFont);
        if (dsq->continuity.getFlag(FLAG_TRANSTURTLE_MAINAREA)) {
            setupTransportationItem(homeWater, lHomeWaterText, "gems/turtle", lHorizontalPosition,
                            lVerticalPosition, "Home Waters");
            homeWater->event.set(MakeFunctionEvent(Randomizer,onHomeWaterTransportation));
            if (lFirst) {
                homeWater->setDirMove(DIR_LEFT, menuCancel);
                menuCancel->setDirMove(DIR_RIGHT, homeWater);
                homeWater->setFocus(true);
                lFirst = false;
            }
            if (lHorizontalPosition > 500.0f) {
                lHorizontalPosition = 175.0f;
                lVerticalPosition = lVerticalPosition + 100.0f;
            } else {
                lHorizontalPosition = lHorizontalPosition + 150.0f;
            }
        } else {
            homeWater->setCanDirMove(false);
        }

        openWater = new AquariaMenuItem;
        BitmapText *lOpenWaterText = new BitmapText(&dsq->smallFont);
        if (dsq->continuity.getFlag(FLAG_TRANSTURTLE_OPENWATER03)) {
            setupTransportationItem(openWater, lOpenWaterText, "gems/turtle", lHorizontalPosition,
                            lVerticalPosition, "Open Waters");
            openWater->event.set(MakeFunctionEvent(Randomizer,onOpenWaterTransportation));
            if (lFirst) {
                openWater->setDirMove(DIR_LEFT, menuCancel);
                menuCancel->setDirMove(DIR_RIGHT, openWater);
                openWater->setFocus(true);
                lFirst = false;
            }
            if (lHorizontalPosition > 500.0f) {
                lHorizontalPosition = 175.0f;
                lVerticalPosition = lVerticalPosition + 100.0f;
            } else {
                lHorizontalPosition = lHorizontalPosition + 150.0f;
            }
        } else {
            openWater->setCanDirMove(false);
        }

        forest = new AquariaMenuItem;
        BitmapText *lForestText = new BitmapText(&dsq->smallFont);
        if (dsq->continuity.getFlag(FLAG_TRANSTURTLE_FOREST04)) {
            setupTransportationItem(forest, lForestText, "gems/turtle", lHorizontalPosition,
                            lVerticalPosition, "Kelp Forest");
            forest->event.set(MakeFunctionEvent(Randomizer,onForestTransportation));
            if (lFirst) {
                forest->setDirMove(DIR_LEFT, menuCancel);
                menuCancel->setDirMove(DIR_RIGHT, forest);
                forest->setFocus(true);
                lFirst = false;
            }
            if (lHorizontalPosition > 500.0f) {
                lHorizontalPosition = 175.0f;
                lVerticalPosition = lVerticalPosition + 100.0f;
            } else {
                lHorizontalPosition = lHorizontalPosition + 150.0f;
            }
        } else {
            forest->setCanDirMove(false);
        }

        veil1 = new AquariaMenuItem;
        BitmapText *lVeil1Text = new BitmapText(&dsq->smallFont);
        if (dsq->continuity.getFlag(FLAG_TRANSTURTLE_VEIL01)) {
            setupTransportationItem(veil1, lVeil1Text, "gems/turtle", lHorizontalPosition,
                            lVerticalPosition, "Left Veil");
            veil1->event.set(MakeFunctionEvent(Randomizer,onVeil1Transportation));
            if (lFirst) {
                veil1->setDirMove(DIR_LEFT, menuCancel);
                menuCancel->setDirMove(DIR_RIGHT, veil1);
                veil1->setFocus(true);
                lFirst = false;
            }
            if (lHorizontalPosition > 500.0f) {
                lHorizontalPosition = 175.0f;
                lVerticalPosition = lVerticalPosition + 100.0f;
            } else {
                lHorizontalPosition = lHorizontalPosition + 150.0f;
            }
        } else {
            veil1->setCanDirMove(false);
        }

        veil2 = new AquariaMenuItem;
        BitmapText *lVeil2Text = new BitmapText(&dsq->smallFont);
        if (dsq->continuity.getFlag(FLAG_TRANSTURTLE_VEIL02)) {
            setupTransportationItem(veil2, lVeil2Text, "gems/turtle", lHorizontalPosition,
                            lVerticalPosition, "Right Veil");
            veil2->event.set(MakeFunctionEvent(Randomizer,onVeil2Transportation));
            if (lFirst) {
                veil2->setDirMove(DIR_LEFT, menuCancel);
                menuCancel->setDirMove(DIR_RIGHT, veil2);
                veil2->setFocus(true);
                lFirst = false;
            }
            if (lHorizontalPosition > 500.0f) {
                lHorizontalPosition = 175.0f;
                lVerticalPosition = lVerticalPosition + 100.0f;
            } else {
                lHorizontalPosition = lHorizontalPosition + 150.0f;
            }
        } else {
            veil2->setCanDirMove(false);
        }

        arnassi = new AquariaMenuItem;
        BitmapText *lArnassiText = new BitmapText(&dsq->smallFont);
        if (dsq->continuity.getFlag(FLAG_TRANSTURTLE_SEAHORSE)) {
            setupTransportationItem(arnassi, lArnassiText, "gems/turtle", lHorizontalPosition,
                            lVerticalPosition, "Arnassi Ruins");
            arnassi->event.set(MakeFunctionEvent(Randomizer,onArnassiTransportation));
            if (lFirst) {
                arnassi->setDirMove(DIR_LEFT, menuCancel);
                menuCancel->setDirMove(DIR_RIGHT, arnassi);
                arnassi->setFocus(true);
                lFirst = false;
            }
            if (lHorizontalPosition > 500.0f) {
                lHorizontalPosition = 175.0f;
                lVerticalPosition = lVerticalPosition + 100.0f;
            } else {
                lHorizontalPosition = lHorizontalPosition + 150.0f;
            }
        } else {
            arnassi->setCanDirMove(false);
        }

        abyss = new AquariaMenuItem;
        BitmapText *lAbyssText = new BitmapText(&dsq->smallFont);
        if (dsq->continuity.getFlag(FLAG_TRANSTURTLE_ABYSS03)) {
            setupTransportationItem(abyss, lAbyssText, "gems/turtle", lHorizontalPosition,
                            lVerticalPosition, "Abyss");
            abyss->event.set(MakeFunctionEvent(Randomizer,onAbyssTransportation));
            if (lFirst) {
                abyss->setDirMove(DIR_LEFT, menuCancel);
                menuCancel->setDirMove(DIR_RIGHT, abyss);
                abyss->setFocus(true);
                lFirst = false;
            }
            if (lHorizontalPosition > 500.0f) {
                lHorizontalPosition = 175.0f;
                lVerticalPosition = lVerticalPosition + 100.0f;
            } else {
                lHorizontalPosition = lHorizontalPosition + 150.0f;
            }
        } else {
            abyss->setCanDirMove(false);
        }

        body = new AquariaMenuItem;
        BitmapText *lBodyText = new BitmapText(&dsq->smallFont);
        if (dsq->continuity.getFlag(FLAG_TRANSTURTLE_FINALBOSS)) {
            setupTransportationItem(body, lBodyText, "gems/turtle", lHorizontalPosition,
                            lVerticalPosition, "Body");
            body->event.set(MakeFunctionEvent(Randomizer,onBodyTransportation));
            if (lFirst) {
                body->setDirMove(DIR_LEFT, menuCancel);
                menuCancel->setDirMove(DIR_RIGHT, body);
                body->setFocus(true);
                lFirst = false;
            }
            if (lHorizontalPosition > 500.0f) {
                lHorizontalPosition = 175.0f;
                lVerticalPosition = lVerticalPosition + 100.0f;
                if (lVerticalPosition > 350.0f) {
                    lHorizontalPosition = 325.0f;
                }
            } else {
                lHorizontalPosition = lHorizontalPosition + 150.0f;
            }
        } else {
            body->setCanDirMove(false);
        }

        simon = new AquariaMenuItem;
        BitmapText *lSimonText = new BitmapText(&dsq->smallFont);
        if (dsq->continuity.getFlag(FLAG_TRANSTURTLE_FOREST05)) {
            setupTransportationItem(simon, lSimonText, "gems/turtle", lHorizontalPosition,
                            lVerticalPosition, "Simon says");
            simon->event.set(MakeFunctionEvent(Randomizer,onSimonTransportation));
            if (lFirst) {
                simon->setDirMove(DIR_LEFT, menuCancel);
                menuCancel->setDirMove(DIR_RIGHT, simon);
                simon->setFocus(true);
                lFirst = false;
            }
            if (lHorizontalPosition > 500.0f) {
                lHorizontalPosition = 175.0f;
                lVerticalPosition = lVerticalPosition + 100.0f;
                if (lVerticalPosition > 350.0f) {
                    lHorizontalPosition = 325.0f;
                }
            } else {
                lHorizontalPosition = lHorizontalPosition + 150.0f;
            }
        } else {
            simon->setCanDirMove(false);
        }

        returnBase = new AquariaMenuItem;
        BitmapText *lReturnBaseText = new BitmapText(&dsq->smallFont);
        if (dsq->continuity.getFlag(FLAG_ENTER_HOMECAVE) == 0) {
            setupTransportationItem(returnBase, lReturnBaseText, "gems/naija-token", lHorizontalPosition,
                lVerticalPosition, "Naija's rock");
            returnBase->event.set(MakeFunctionEvent(Randomizer,onNaijaRockTransportation));
        } else {
            setupTransportationItem(returnBase, lReturnBaseText, "gems/naija-token", lHorizontalPosition,
                lVerticalPosition, "Naija's home");
            returnBase->event.set(MakeFunctionEvent(Randomizer,onNaijaHomeTransportation));
        }
        if (lFirst) {
            returnBase->setDirMove(DIR_LEFT, menuCancel);
            menuCancel->setDirMove(DIR_RIGHT, returnBase);
            returnBase->setFocus(true);
            lFirst = false;
        }

        if (dsq->continuity.getFlag(FLAG_TRANSTURTLE_MAINAREA)) {
            if (dsq->continuity.getFlag(FLAG_TRANSTURTLE_OPENWATER03)) {
                homeWater->setDirMove(DIR_RIGHT, openWater);
                openWater->setDirMove(DIR_LEFT, homeWater);
            } else if (dsq->continuity.getFlag(FLAG_TRANSTURTLE_FOREST04)) {
                homeWater->setDirMove(DIR_RIGHT, forest);
                forest->setDirMove(DIR_LEFT, homeWater);
            } else if (dsq->continuity.getFlag(FLAG_TRANSTURTLE_VEIL01)) {
                homeWater->setDirMove(DIR_RIGHT, veil1);
                veil1->setDirMove(DIR_LEFT, homeWater);
            } else if (dsq->continuity.getFlag(FLAG_TRANSTURTLE_VEIL02)) {
                homeWater->setDirMove(DIR_RIGHT, veil2);
                veil2->setDirMove(DIR_LEFT, homeWater);
            } else if (dsq->continuity.getFlag(FLAG_TRANSTURTLE_SEAHORSE)) {
                homeWater->setDirMove(DIR_RIGHT, arnassi);
                arnassi->setDirMove(DIR_LEFT, homeWater);
            } else if (dsq->continuity.getFlag(FLAG_TRANSTURTLE_ABYSS03)) {
                homeWater->setDirMove(DIR_RIGHT, abyss);
                abyss->setDirMove(DIR_LEFT, homeWater);
            } else if (dsq->continuity.getFlag(FLAG_TRANSTURTLE_FINALBOSS)) {
                homeWater->setDirMove(DIR_RIGHT, body);
                body->setDirMove(DIR_LEFT, homeWater);
            } else if (dsq->continuity.getFlag(FLAG_TRANSTURTLE_FOREST05)) {
                homeWater->setDirMove(DIR_RIGHT, simon);
                simon->setDirMove(DIR_LEFT, homeWater);
            } else {
                homeWater->setDirMove(DIR_RIGHT, returnBase);
                returnBase->setDirMove(DIR_LEFT, homeWater);
            }
        }
        if (dsq->continuity.getFlag(FLAG_TRANSTURTLE_OPENWATER03)) {
            if (dsq->continuity.getFlag(FLAG_TRANSTURTLE_FOREST04)) {
                openWater->setDirMove(DIR_RIGHT, forest);
                forest->setDirMove(DIR_LEFT, openWater);
            } else if (dsq->continuity.getFlag(FLAG_TRANSTURTLE_VEIL01)) {
                openWater->setDirMove(DIR_RIGHT, veil1);
                veil1->setDirMove(DIR_LEFT, openWater);
            } else if (dsq->continuity.getFlag(FLAG_TRANSTURTLE_VEIL02)) {
                openWater->setDirMove(DIR_RIGHT, veil2);
                veil2->setDirMove(DIR_LEFT, openWater);
            } else if (dsq->continuity.getFlag(FLAG_TRANSTURTLE_SEAHORSE)) {
                openWater->setDirMove(DIR_RIGHT, arnassi);
                arnassi->setDirMove(DIR_LEFT, openWater);
            } else if (dsq->continuity.getFlag(FLAG_TRANSTURTLE_ABYSS03)) {
                openWater->setDirMove(DIR_RIGHT, abyss);
                abyss->setDirMove(DIR_LEFT, openWater);
            } else if (dsq->continuity.getFlag(FLAG_TRANSTURTLE_FINALBOSS)) {
                openWater->setDirMove(DIR_RIGHT, body);
                body->setDirMove(DIR_LEFT, openWater);
            } else if (dsq->continuity.getFlag(FLAG_TRANSTURTLE_FOREST05)) {
                openWater->setDirMove(DIR_RIGHT, simon);
                simon->setDirMove(DIR_LEFT, openWater);
            } else {
                openWater->setDirMove(DIR_RIGHT, returnBase);
                returnBase->setDirMove(DIR_LEFT, openWater);
            }
        }
        if (dsq->continuity.getFlag(FLAG_TRANSTURTLE_FOREST04)) {
            if (dsq->continuity.getFlag(FLAG_TRANSTURTLE_VEIL01)) {
                forest->setDirMove(DIR_RIGHT, veil1);
                veil1->setDirMove(DIR_LEFT, forest);
            } else if (dsq->continuity.getFlag(FLAG_TRANSTURTLE_VEIL02)) {
                forest->setDirMove(DIR_RIGHT, veil2);
                veil2->setDirMove(DIR_LEFT, forest);
            } else if (dsq->continuity.getFlag(FLAG_TRANSTURTLE_SEAHORSE)) {
                forest->setDirMove(DIR_RIGHT, arnassi);
                arnassi->setDirMove(DIR_LEFT, forest);
            } else if (dsq->continuity.getFlag(FLAG_TRANSTURTLE_ABYSS03)) {
                forest->setDirMove(DIR_RIGHT, abyss);
                abyss->setDirMove(DIR_LEFT, forest);
            } else if (dsq->continuity.getFlag(FLAG_TRANSTURTLE_FINALBOSS)) {
                forest->setDirMove(DIR_RIGHT, body);
                body->setDirMove(DIR_LEFT, forest);
            } else if (dsq->continuity.getFlag(FLAG_TRANSTURTLE_FOREST05)) {
                forest->setDirMove(DIR_RIGHT, simon);
                simon->setDirMove(DIR_LEFT, forest);
            } else {
                forest->setDirMove(DIR_RIGHT, returnBase);
                returnBase->setDirMove(DIR_LEFT, forest);
            }
        }
        if (dsq->continuity.getFlag(FLAG_TRANSTURTLE_VEIL01)) {
            if (dsq->continuity.getFlag(FLAG_TRANSTURTLE_VEIL02)) {
                veil1->setDirMove(DIR_RIGHT, veil2);
                veil2->setDirMove(DIR_LEFT, veil1);
            } else if (dsq->continuity.getFlag(FLAG_TRANSTURTLE_SEAHORSE)) {
                veil1->setDirMove(DIR_RIGHT, arnassi);
                arnassi->setDirMove(DIR_LEFT, veil1);
            } else if (dsq->continuity.getFlag(FLAG_TRANSTURTLE_ABYSS03)) {
                veil1->setDirMove(DIR_RIGHT, abyss);
                abyss->setDirMove(DIR_LEFT, veil1);
            } else if (dsq->continuity.getFlag(FLAG_TRANSTURTLE_FINALBOSS)) {
                veil1->setDirMove(DIR_RIGHT, body);
                body->setDirMove(DIR_LEFT, veil1);
            } else if (dsq->continuity.getFlag(FLAG_TRANSTURTLE_FOREST05)) {
                veil1->setDirMove(DIR_RIGHT, simon);
                simon->setDirMove(DIR_LEFT, veil1);
            } else {
                veil1->setDirMove(DIR_RIGHT, returnBase);
                returnBase->setDirMove(DIR_LEFT, veil1);
            }
        }
        if (dsq->continuity.getFlag(FLAG_TRANSTURTLE_VEIL02)) {
            if (dsq->continuity.getFlag(FLAG_TRANSTURTLE_SEAHORSE)) {
                veil2->setDirMove(DIR_RIGHT, arnassi);
                arnassi->setDirMove(DIR_LEFT, veil2);
            } else if (dsq->continuity.getFlag(FLAG_TRANSTURTLE_ABYSS03)) {
                veil2->setDirMove(DIR_RIGHT, abyss);
                abyss->setDirMove(DIR_LEFT, veil2);
            } else if (dsq->continuity.getFlag(FLAG_TRANSTURTLE_FINALBOSS)) {
                veil2->setDirMove(DIR_RIGHT, body);
                body->setDirMove(DIR_LEFT, veil2);
            } else if (dsq->continuity.getFlag(FLAG_TRANSTURTLE_FOREST05)) {
                veil2->setDirMove(DIR_RIGHT, simon);
                simon->setDirMove(DIR_LEFT, veil2);
            } else {
                veil2->setDirMove(DIR_RIGHT, returnBase);
                returnBase->setDirMove(DIR_LEFT, veil2);
            }
        }
        if (dsq->continuity.getFlag(FLAG_TRANSTURTLE_SEAHORSE)) {
            if (dsq->continuity.getFlag(FLAG_TRANSTURTLE_ABYSS03)) {
                arnassi->setDirMove(DIR_RIGHT, abyss);
                abyss->setDirMove(DIR_LEFT, arnassi);
            } else if (dsq->continuity.getFlag(FLAG_TRANSTURTLE_FINALBOSS)) {
                arnassi->setDirMove(DIR_RIGHT, body);
                body->setDirMove(DIR_LEFT, arnassi);
            } else if (dsq->continuity.getFlag(FLAG_TRANSTURTLE_FOREST05)) {
                arnassi->setDirMove(DIR_RIGHT, simon);
                simon->setDirMove(DIR_LEFT, arnassi);
            } else {
                arnassi->setDirMove(DIR_RIGHT, returnBase);
                returnBase->setDirMove(DIR_LEFT, arnassi);
            }
        }
        if (dsq->continuity.getFlag(FLAG_TRANSTURTLE_ABYSS03)) {
            if (dsq->continuity.getFlag(FLAG_TRANSTURTLE_FINALBOSS)) {
                abyss->setDirMove(DIR_RIGHT, body);
                body->setDirMove(DIR_LEFT, abyss);
            } else if (dsq->continuity.getFlag(FLAG_TRANSTURTLE_FOREST05)) {
                abyss->setDirMove(DIR_RIGHT, simon);
                simon->setDirMove(DIR_LEFT, abyss);
            } else {
                abyss->setDirMove(DIR_RIGHT, returnBase);
                returnBase->setDirMove(DIR_LEFT, abyss);
            }
        }
        if (dsq->continuity.getFlag(FLAG_TRANSTURTLE_FINALBOSS)) {
            if (dsq->continuity.getFlag(FLAG_TRANSTURTLE_FOREST05)) {
                body->setDirMove(DIR_RIGHT, simon);
                simon->setDirMove(DIR_LEFT, body);
            } else {
                body->setDirMove(DIR_RIGHT, returnBase);
                returnBase->setDirMove(DIR_LEFT, body);
            }
        }
        if (dsq->continuity.getFlag(FLAG_TRANSTURTLE_FOREST05)) {
            simon->setDirMove(DIR_RIGHT, returnBase);
            returnBase->setDirMove(DIR_LEFT, simon);
        }

        menuCancel->useQuad("Gui/cancel");
        menuCancel->useSound("click");
        menuCancel->useGlow("particles/glow", 128, 40);
        menuCancel->position = Vector(400, 500);
        menuCancel->followCamera = 1;
        menuCancel->event.set(MakeFunctionEvent(Randomizer,onCancelTransportation));
        menuCancel->scale = Vector(0.9, 0.9);
        menuCancel->guiInputLevel = GUILEVEL_TRANSPORT;
        dsq->game->addRenderObject(menuCancel, LR_RANDOMIZER_PANEL);

        returnBase->setDirMove(DIR_RIGHT, menuCancel);
        menuCancel->setDirMove(DIR_LEFT, returnBase);




        AquariaGuiElement::currentGuiInputLevel = GUILEVEL_TRANSPORT;
        dsq->toggleCursor(true);

        while (!transportationDone)
        {
            transportationSelected = 0;
            dsq->main(FRAME_TIME);
            if (transportationSelected == FLAG_TRANSTURTLE_MAINAREA) {
                homeWater->setFocus(true);
            } else if (transportationSelected == FLAG_TRANSTURTLE_OPENWATER03) {
                openWater->setFocus(true);
            } else if (transportationSelected == FLAG_TRANSTURTLE_FOREST04) {
                forest->setFocus(true);
            } else if (transportationSelected == FLAG_TRANSTURTLE_VEIL01) {
                veil1->setFocus(true);
            } else if (transportationSelected == FLAG_TRANSTURTLE_VEIL02) {
                veil2->setFocus(true);
            } else if (transportationSelected == FLAG_TRANSTURTLE_SEAHORSE) {
                arnassi->setFocus(true);
            } else if (transportationSelected == FLAG_TRANSTURTLE_ABYSS03) {
                abyss->setFocus(true);
            } else if (transportationSelected == FLAG_TRANSTURTLE_FINALBOSS) {
                body->setFocus(true);
            } else if (transportationSelected == FLAG_TRANSTURTLE_FOREST05) {
                simon->setFocus(true);
            } else if (transportationSelected == FLAG_TRANSTURTLE_NAIJAHOME ||
                       transportationSelected == FLAG_TRANSTURTLE_NAIJAROCK) {
                returnBase->setFocus(true);
            }
        }
        sound->playSfx("menu-close");
        AquariaGuiElement::currentGuiInputLevel = 0;
        bgimage->alpha.interpolateTo(0, 0.5);
        bgimage->scale.interpolateTo(Vector(0.5, 0.5), 0.5);
        menuCancel->setFocus(false);
        menuCancel->safeKill();
        lTitle->safeKill();
        homeWater->setFocus(false);
        homeWater->safeKill();
        homeWater = nullptr;
        lHomeWaterText->safeKill();
        openWater->setFocus(false);
        openWater->safeKill();
        openWater = nullptr;
        lOpenWaterText->safeKill();
        forest->setFocus(false);
        forest->safeKill();
        forest = nullptr;
        lForestText->safeKill();
        veil1->setFocus(false);
        veil1->safeKill();
        veil1 = nullptr;
        lVeil1Text->safeKill();
        veil2->setFocus(false);
        veil2->safeKill();
        veil2 = nullptr;
        lVeil2Text->safeKill();
        arnassi->setFocus(false);
        arnassi->safeKill();
        arnassi = nullptr;
        lArnassiText->safeKill();
        abyss->setFocus(false);
        abyss->safeKill();
        abyss = nullptr;
        lAbyssText->safeKill();
        body->setFocus(false);
        body->safeKill();
        body = nullptr;
        lBodyText->safeKill();
        simon->setFocus(false);
        simon->safeKill();
        simon = nullptr;
        lSimonText->safeKill();
        returnBase->setFocus(false);
        returnBase->safeKill();
        returnBase = nullptr;
        lReturnBaseText->safeKill();
        dsq->main(0.5);
        bgimage->safeKill();
        dsq->game->togglePause(false);
        }
    return transportationSelected;
}

/**
 * Event for the Transportation menu to cancel the process.
 */
void Randomizer::onOkPanel() {
    panelDone = true;
}

/**
 * Check if the game is in a state where the showTextPanel can work.
 *
 * @return True when the showTextPanel can be launched. False if not
 */
bool Randomizer::gameControlReady() {
    return !game->isSceneEditorActive() && !dsq->screenTransition->isGoing() && !dsq->isNested() &&
        dsq->saveSlotMode == SSM_NONE;
}

/**
 * Show a text in a panel.
 * @param aText The text to show in the panel
 * @param aFont The font to use when drawing text
 * @param aCenter It the text must be centered
 * @param aYesNo If there is a yes and no buttons in the panel. If False an Ok button will be put instead
 * @param aEvent The event to use when the Yes button is used.
 */
void Randomizer::showTextPanel(const std::string& aText, BmpFont *aFont, bool aCenter, bool aYesNo, Event *aEvent) {
    if (gameControlReady()) {
        dsq->game->togglePause(true);
        sound->playSfx("menu-open");
        Quad *bgimage = new Quad("gui/recipe-scroll.png", Vector(400,300));
        bgimage->followCamera = 1;
        bgimage->alpha = 0;
        bgimage->alpha.interpolateTo(1, 0.5);
        //bgLabel->setWidthHeight(512*0.9f, 256*0.9f);
        bgimage->scale = Vector(0, 0);
        bgimage->scale.interpolateTo(Vector(1.5,1), 0.5);
        game->addRenderObject(bgimage, LR_RANDOMIZER_PANEL);
        dsq->main(0.5);

        BitmapText *lTitle = new BitmapText(aFont);
        lTitle->setWidth(550);
        lTitle->color = 0;
        lTitle->setFontSize(10);
        if (aCenter) {
            lTitle->setAlign(ALIGN_CENTER);
            lTitle->position = Vector(400,100);
        } else {
            lTitle->setAlign(ALIGN_LEFT);
            lTitle->position = Vector(120,100);
        }
        lTitle->followCamera = 1;

        lTitle->setText(aText);
        lTitle->scale = Vector(1.0, 1.0);
        game->addRenderObject(lTitle, LR_RANDOMIZER_PANEL);

        menuNoOk = new AquariaMenuItem;

        if (aYesNo) {
            menuNoOk->useQuad("no");
            menuNoOk->position = Vector(500, 500);
            menuYes = new AquariaMenuItem;
            menuYes->useQuad("yes");
            menuYes->position = Vector(300, 500);
            menuYes->followCamera = 1;
            if (aEvent) {
                menuYes->useSound("click");
                menuYes->useGlow("particles/glow", 128, 40);
                menuYes->event.set(aEvent);
            } else {
                menuYes->useSound("denied");
            }
            menuYes->scale = Vector(0.9, 0.9);
            menuYes->guiInputLevel = GUILEVEL_PANEL;
            dsq->game->addRenderObject(menuYes, LR_RANDOMIZER_PANEL);
            menuNoOk->setDirMove(DIR_LEFT, menuYes);
            menuYes->setDirMove(DIR_RIGHT, menuNoOk);
        } else {
            menuYes = nullptr;
            menuNoOk->useQuad("Gui/ok");
            menuNoOk->position = Vector(400, 500);
        }
        menuNoOk->useSound("click");
        menuNoOk->useGlow("particles/glow", 128, 40);
        menuNoOk->followCamera = 1;
        menuNoOk->event.set(MakeFunctionEvent(Randomizer,onOkPanel));
        menuNoOk->scale = Vector(0.9, 0.9);
        menuNoOk->guiInputLevel = GUILEVEL_PANEL;
        menuNoOk->setFocus(true);
        dsq->game->addRenderObject(menuNoOk, LR_RANDOMIZER_PANEL);
        AquariaGuiElement::currentGuiInputLevel = GUILEVEL_PANEL;
        dsq->toggleCursor(true);
        panelDone = false;
        while (!panelDone)
        {
            dsq->main(FRAME_TIME);
        }
        sound->playSfx("menu-close");
        AquariaGuiElement::currentGuiInputLevel = 0;
        bgimage->alpha.interpolateTo(0, 0.5);
        bgimage->scale.interpolateTo(Vector(0.5, 0.5), 0.5);
        menuNoOk->setFocus(false);
        menuNoOk->safeKill();
        lTitle->safeKill();
        if (menuYes) {
            menuYes->setFocus(false);
            menuYes->safeKill();
        }
        dsq->main(0.5);
        bgimage->safeKill();
        dsq->game->togglePause(false);
        }
}
