/**
 * @author      : Louis Marchand (prog@tioui.com)
 * @created     : Thu, 25 Jan 2024 17:21:06 +0000
 * @license     : MIT
 */

#ifndef RANDOMIZER_H

#define RANDOMIZER_H


#include "../Aquaria/DSQ.h"

typedef struct check {
	std::string id;
	std::string item;
	int count;
	std::string message;
} check_t;

/**
 * Class that encapsulate every randomization functionalities
*/
class Randomizer
{
	public:
		/**
		 * Constructor for connecting to a multiworld randomizer server
		 * \param name The name of the user
		 * \param server The ip and port of the server
		 */
		Randomizer(std::string name, std::string server);

		/**
		 * Constructor for using a local json file
		 * \param filename The json filename
		 */
		Randomizer(std::string filename);

		/**
		 * Destructor of the object
		 */
		~Randomizer();

		/**
		 * Randomize the IngredientData using ingredient in continuity.
		 * \param data The IngredientData to randomize
		 * \return The randomized IngredientData.
		 */
		IngredientData *getRandomizedIngredientData(IngredientData* data);

		/**
		 * Activate a randomizer check
		 * \param check The check to activate
		*/
		void activateCheck(const std::string check);


	private:
		/**
		 * Replacement of every ingredients.
		 */
		std::vector<int> ingredientReplacement;

		/**
		 * Assign the ingredient replacement
		 * \param dsq The DSQ to assing
		 */
		void initialiseIngredientReplacements(const std::string &filename);

		/**
		 * Get a new collectible item to activate in the local game
		 * \param aCollectible The collectible item to activate
		 */
		void receivingCollectible(const std::string aCollectible);
		/**
		 * Get a new item to activate in the local game
		 * \param item The item to activate
		 * \param count The number of element to receive
		 * \todo The method
		 */
		void receivingItem(const std::string item, int count);

		/**
		 * Retreive a check structure from a check Id
		 * \param checkId The Id of the check to retreive
		 * \return A pointer to the check_t object
		 */
		check_t *getCheck(const std::string checkId);

		/**
		 * Retreive a check structure from an item Id
		 * \param aItem The item Id of the check to retreive
		 * \return A pointer to the check_t object
		 */
		check_t *getCheckByItem(const std::string aItem);


		/**
		 * The name of the multiworld randomizer user 
		 */
		FILE *file;

		/**
		 * The name of the multiworld randomizer user 
		 */
		std::string name;

		/**
		 * The name of the multiworld randomizer server and port 
		 */
		std::string server;
};

const int FLAG_COLLECTIBLE_INHOME_SONGCAVE = 550;
const int FLAG_COLLECTIBLE_INHOME_ENERGYTEMPLE = 551;
const int FLAG_COLLECTIBLE_INHOME_ENERGYSTATUE = 552;
const int FLAG_COLLECTIBLE_INHOME_ENERGYBOSS = 553;
const int FLAG_COLLECTIBLE_INHOME_NAIJACAVE = 554;
const int FLAG_COLLECTIBLE_INHOME_CRABCOSTUME = 555;
const int FLAG_COLLECTIBLE_INHOME_JELLYPLANT = 556;
const int FLAG_COLLECTIBLE_INHOME_MITHALASPOT = 557;
const int FLAG_COLLECTIBLE_INHOME_SEAHORSECOSTUME = 558;
const int FLAG_COLLECTIBLE_INHOME_CHEST = 559;
const int FLAG_COLLECTIBLE_INHOME_BANNER = 560;
const int FLAG_COLLECTIBLE_INHOME_MITHALADOLL = 561;
const int FLAG_COLLECTIBLE_INHOME_WALKERBABY = 562;
const int FLAG_COLLECTIBLE_INHOME_SEEDBAG = 563;
const int FLAG_COLLECTIBLE_INHOME_ARNASSISTATUE = 564;
const int FLAG_COLLECTIBLE_INHOME_GEAR = 565;
const int FLAG_COLLECTIBLE_INHOME_SUNKEY = 566;
const int FLAG_COLLECTIBLE_INHOME_URCHINCOSTUME = 567;
const int FLAG_COLLECTIBLE_INHOME_TEENCOSTUME = 568;
const int FLAG_COLLECTIBLE_INHOME_MUTANTCOSTUME = 569;
const int FLAG_COLLECTIBLE_INHOME_JELLYCOSTUME = 570;
const int FLAG_COLLECTIBLE_INHOME_MITHALANCOSTUME = 571;
const int FLAG_COLLECTIBLE_INHOME_ANEMONESEED = 572;
const int FLAG_COLLECTIBLE_INHOME_BIOSEED = 573;
const int FLAG_COLLECTIBLE_INHOME_TURTLEEGG = 574;
const int FLAG_COLLECTIBLE_INHOME_SKULL = 575;
const int FLAG_COLLECTIBLE_INHOME_TRIDENTHEAD = 576;
const int FLAG_COLLECTIBLE_INHOME_SPORESEED = 577;
const int FLAG_COLLECTIBLE_INHOME_UPSIDEDOWNSEED = 578;
const int FLAG_COLLECTIBLE_INHOME_STONEHEAD = 579;
const int FLAG_COLLECTIBLE_INHOME_STARFISH = 580;
const int FLAG_COLLECTIBLE_INHOME_BLACKPEARL = 581;
const int FLAG_COLLECTIBLE_INHOME_BLASTER = 582;
const int FLAG_COLLECTIBLE_INHOME_NAUTILUS = 583;
const int FLAG_COLLECTIBLE_INHOME_DUMBO = 584;
const int FLAG_COLLECTIBLE_INHOME_PIRANHA = 585;

static std::vector<check_t> CHECKS = {
	(check_t){"bulb_turtlecave","ingredient_poultice",3, "Leaf poultice"},
	(check_t){"bulb_openwater_tl_1","ingredient_handroll",1, "Hand roll"},
	(check_t){"bulb_openwater_tl_2","ingredient_veggiesoup",1, "Veggie soup"},
	(check_t){"bulb_openwater_tl_3","ingredient_butterysealoaf",1, "Buttery sea loaf"},
	(check_t){"bulb_openwater_tr_1","ingredient_healingpoultice",1, "Healing poultice"},
	(check_t){"bulb_openwater_tr_2","ingredient_sealoaf",2, "Sea loaf"},
	(check_t){"bulb_openwater_tr_3","ingredient_spicyroll",1, "Spicy roll"},
	(check_t){"bulb_openwater_tr_4","ingredient_spicymeat",2, "Spicy meat"},
	(check_t){"bulb_openwater_tr_5","ingredient_crabcake",1, "Crab cake"},
	(check_t){"bulb_openwater_tr_6","ingredient_spicyroll",1, "Spicy roll"},
	(check_t){"bulb_openwater_bl_1","ingredient_leadershiproll",2, "Leadership roll"},
	(check_t){"bulb_openwater_bl_2","ingredient_healingpoultice",2, "Healing poultice"},
	(check_t){"bulb_skeleton_path_1","ingredient_tastycake",1, "Tasty cake"},
	(check_t){"bulb_skeleton_path_2","ingredient_perogi",1, "Perogi"},
	(check_t){"bulb_arnassi_1","ingredient_tastyrool",1, "Tasty roll"},
	(check_t){"bulb_arnassi_2","ingredient_specialbulb",1, "Special bulb"},
	(check_t){"bulb_arnassi_3","ingredient_specialcake",1, "Special cake"},
	(check_t){"bulb_sunworm_1","ingredient_plantleaf",3, "Plant leaf"},
	(check_t){"bulb_sunworm_2","ingredient_turtlesoup",1, "Turtle soup"},
	(check_t){"bulb_sunworm_3","ingredient_specialcake",1, "Special cake"},
	(check_t){"bulb_sunworm_4","ingredient_specialbulb",1, "Special bulb"},
	(check_t){"bulb_tutorial_1","ingredient_handroll",1, "Hand roll"},
	(check_t){"bulb_tutorial_2","ingredient_hotsoup",1, "Hot soup"},
	(check_t){"bulb_tutorial_3","ingredient_heartysoup",1, "Hearty soup"},
	(check_t){"bulb_abyss_l_1","ingredient_coldborscht",1, "Cold borscht"},
	(check_t){"bulb_abyss_l_2","ingredient_healingpoultice",2, "Healing poultice"},
	(check_t){"bulb_abyss_l_3","ingredient_sightpoultice",1, "Sight poultice"},
	(check_t){"bulb_energy_temple_1_1","ingredient_poultice",1, "Leaf poultice"},
	(check_t){"bulb_energy_temple_2_1","ingredient_spicyroll",1, "Spicy roll"},
	(check_t){"bulb_energy_temple_3_1","ingredient_plantleaf",2, "Plant leaf"},
	(check_t){"bulb_mithalas_city_01","ingredient_spicyroll",1, "Spicy roll"},
	(check_t){"bulb_mithalas_city_02","ingredient_spicymeat",2, "Spicy meat"},
	(check_t){"bulb_mithalas_city_03","ingredient_vedhaseacrisp",1, "Vedha sea crisp"},
	(check_t){"bulb_mithalas_city_04","ingredient_heartysoup",1, "Hearty soup"},
	(check_t){"bulb_mithalas_city_05","ingredient_healingpoultice",1, "Healing poultice"},
	(check_t){"bulb_mithalas_city_06","ingredient_vedhaseacrisp",1, "Vedha sea crisp"},
	(check_t){"bulb_mithalas_city_07","ingredient_rottenloaf",8, "Rotten loaf"},
	(check_t){"bulb_mithalas_city_08","ingredient_rottenmeat",8, "Rotten meat"},
	(check_t){"bulb_mithalas_city_09","ingredient_smalltentacle",2, "Small tentacle"},
	(check_t){"bulb_mithalas_city_10","ingredient_seacake",1, "Sea cake"},
	(check_t){"bulb_mithalas_city_11","ingredient_smallbone",3, "Small bone"},
	(check_t){"bulb_mithalas_city_12","ingredient_handroll",1, "Hand roll"},
	(check_t){"bulb_cathedral_l_2","ingredient_heartysoup",1, "Hearty soup"},
	(check_t){"bulb_boilerroom_1","ingredient_spicyroll",1, "Spicy rool"},
	(check_t){"bulb_forest_tl_1","ingredient_seacake",1, "Sea cake"},
	(check_t){"bulb_forest_tl_2","ingredient_spicyroll",1, "Spicy roll"},
	(check_t){"bulb_forest_tl_3","ingredient_leechingpoultice",1, "Leeching poultice"},
	(check_t){"bulb_forest_tl_4","ingredient_redbulb",2, "Red bulb"},
	(check_t){"bulb_forest_tr_1","ingredient_spiderroll",1, "Spider roll"},
	(check_t){"bulb_forest_tr_2","ingredient_veggiecake",1, "Veggie cake"},
	(check_t){"bulb_forest_tr_3","ingredient_swampcake",1, "Swamp cake"},
	(check_t){"bulb_forest_tr_4","ingredient_sharkfinsoup",1, "Shark fin soup"},
	(check_t){"bulb_forest_tr_5","ingredient_healingpoultice",1, "Healing poultice"},
	(check_t){"bulb_forest_tr_6","ingredient_redbulb",2, "Red bulb"},
	(check_t){"bulb_forest_bl_1","ingredient_spiderroll",1, "Spider roll"},
	(check_t){"bulb_forest_boss_room_1","ingredient_handroll",1, "Hand roll"},
	(check_t){"bulb_forest_sprite_cave_1","ingredient_leechingpoultice",1, "Leeching poultice"},
	(check_t){"bulb_forest_sprite_cave_2","ingredient_veggiesoup",1, "Veggie soup"},
	(check_t){"bulb_home_water_1","ingredient_smallegg",2, "Small egg"},
	(check_t){"bulb_home_water_2","ingredient_poultice",1, "Leaf poultice"},
	(check_t){"bulb_home_water_3","ingredient_poultice",1, "Leaf poultice"},
	(check_t){"bulb_home_water_4","ingredient_plantleaf",3, "Plant leaf"},
	(check_t){"bulb_home_water_5","ingredient_redbulb",2, "Red bulb"},
	(check_t){"bulb_home_water_6","ingredient_hotsoup",1, "Hot soup"},
	(check_t){"bulb_home_water_7","ingredient_fishmeat",2, "Fish meat"},
	(check_t){"bulb_home_water_8","ingredient_seacake",1, "Sea cake"},
	(check_t){"bulb_final_l_1","ingredient_arcanepoultice",1, "Arcane poultice"},
	(check_t){"bulb_final_l_2","ingredient_divinesoup",1, "Divine soup"},
	(check_t){"bulb_final_l_3","ingredient_spicyroll",1, "Spicy roll"},
	(check_t){"bulb_final_l_4","ingredient_volcanoroll",1, "Volcano roll"},
	(check_t){"bulb_final_l_5","ingredient_arcanepoultice",1, "Arcane poultice"},
	(check_t){"bulb_song_cave_1","ingredient_specialbulb",1, "Special bulb"},
	(check_t){"bulb_song_cave_2","ingredient_handroll",1, "Hand roll"},
	(check_t){"bulb_song_cave_3","ingredient_eeloil",2, "Eel oil"},
	(check_t){"bulb_song_cave_4","ingredient_poultice",1, "Leaf poultice"},
	(check_t){"bulb_song_cave_5","ingredient_hotsoup",1, "Hot soup"},
	(check_t){"bulb_veil_tl_1","ingredient_spicysoup",1, "Spicy soup"},
	(check_t){"bulb_veil_tl_2","ingredient_longlifesoup",1, "Long life soup"},
	(check_t){"bulb_veil_tl_3","ingredient_hotsoup",2, "Hot soup"},
	(check_t){"bulb_veil_tr_1","ingredient_sharkfinsoup",1, "Shark fin soup"},
	(check_t){"bulb_veil_tr_2","ingredient_legendarycake",1, "Legendary cake"},
	(check_t){"bulb_veil_b_1","ingredient_swampcake",1, "Swamp cake"},
	(check_t){"bulb_veil_b_2","ingredient_swampcake",1, "Swamp cake"},
	(check_t){"bulb_ice_cave_1","ingredient_icecream",1, "Ice cream"},
	(check_t){"bulb_ice_cave_2","ingredient_berryicecream",1, "Berry ice cream"},
	(check_t){"bulb_ice_cave_3","ingredient_veggieicecream",1, "Veggie ice cream"},
	(check_t){"bulb_ice_cave_4","ingredient_dumboicecream",1, "Dumbo ice cream"},
	(check_t){"bulb_ice_cave_5","ingredient_icecream",1, "Ice cream"},
	(check_t){"bulb_king_jellyfish_cave_1","ingredient_specialbulb",1, "Special bulb"},
	(check_t){"bulb_bubble_cave_1","ingredient_coldsoup",1, "Cold soup"},
	(check_t){"bulb_bubble_cave_2","ingredient_coldborscht",1, "Cold borscht"},
	(check_t){"bulb_sun_temple_1","ingredient_glowingegg",2, "Glowing egg"},
	(check_t){"bulb_sun_temple_2","ingredient_magicsoup",1, "Magic soup"},
	(check_t){"bulb_sun_temple_3","ingredient_royalsoup",1, "Royal soup"},
	(check_t){"bulb_sun_temple_4","ingredient_leadershiproll",1, "Leadership roll"},
	(check_t){"bulb_sun_temple_5","ingredient_turtlesoup",1, "Turtle soup"},
	(check_t){"bulb_sun_temple_6","ingredient_heartysoup",1, "Hearty soup"},
	(check_t){"bulb_final_c_1","ingredient_Zuuna'sperogi",1, "Zuuna's perogi"},
	(check_t){"bulb_final_r_1","ingredient_plumpperogi",1, "Plump perogi"},
	(check_t){"bulb_final_r_2","ingredient_arcanepoultice",1, "Arcane poultice"},
	(check_t){"bulb_final_r_3","ingredient_arcanepoultice",1, "Arcane poultice"},
	(check_t){"bulb_final_b_1","ingredient_longlifesoup",1, "Long life soup"},
	(check_t){"bulb_final_b_2","ingredient_spicyroll",1, "Spicy roll"},
	(check_t){"bulb_final_boss_1","ingredient_Vedha'sCure-All",1, "Vedha's Cure-All"},
	(check_t){"bulb_final_boss_2","ingredient_loafoflife",1, "Loaf of life"},
	(check_t){"bulb_final_boss_3","ingredient_specialbulb",1, "Special bulb"},
	(check_t){"bulb_final_boss_4","ingredient_dumboicecream",1, "Dumbo ice cream"},
	(check_t){"bulb_starting_cave_1","ingredient_fishoil",1, "Fish oil"},
	(check_t){"bulb_starting_cave_2","ingredient_smallegg",1, "Small egg"},
	(check_t){"bulb_abyss_r_1","ingredient_dumboicecream",1, "Dumbo ice cream"},
	(check_t){"bulb_abyss_r_2","ingredient_tastyroll",1, "Tasty roll"},
	(check_t){"bulb_abyss_r_3","ingredient_healingpoultice",1, "Healing poultice"},
	(check_t){"bulb_abyss_r_4","ingredient_hotborscht",1, "Hot borscht"},
	(check_t){"bulb_cathedral_under_ground_1","ingredient_arcanepoultice",1, "Arcane poultice"},
	(check_t){"bulb_cathedral_under_ground_2","ingredient_plantleaf",1, "Plant leaf"},
	(check_t){"bulb_cathedral_under_ground_3","ingredient_arcanepoultice",1, "Arcane poultice"},
	(check_t){"bulb_cathedral_under_ground_4","ingredient_redberry",1, "Red berry"},
	(check_t){"bulb_cathedral_under_ground_5","ingredient_poultice",1, "Leaf poultice"},
	(check_t){"bulb_cathedral_under_ground_6","ingredient_arcanepoultice",1, "Arcane poultice"},
	(check_t){"bulb_naija_home_1","ingredient_spicyroll",1, "Spicy roll"},
	(check_t){"bulb_naija_home_2","ingredient_heartysoup",1, "Hearty soup"},
	(check_t){"bulb_mermog_cave_1","ingredient_leechingpoultice",1, "Leeching poultice"},
	(check_t){"bulb_octo_cave_1","ingredient_sightpoultice",1, "Sight poultice"},
	(check_t){"urn_mithalas_city_1","ingredient_rottenmeat",2, "Rotten meat"},
	(check_t){"urn_mithalas_city_2","ingredient_glowingegg",1, "Glowing egg"},
	(check_t){"urn_mithalas_city_3","ingredient_rainbowmushroom",1, "Rainbow mushroom"},
	(check_t){"urn_mithalas_city_4","ingredient_rainbowmushroom",1, "Rainbow mushroom"},
	(check_t){"urn_mithalas_city_5","ingredient_rainbowmushroom",1, "Rainbow mushroom"},
	(check_t){"urn_mithalas_city_6","ingredient_plantleaf",3, "Plant leaf"},
	(check_t){"urn_mithalas_city_7","ingredient_spicyroll",1, "Spicy roll"},
	(check_t){"urn_cathedral_l_1","ingredient_rainbowmushroom",1, "Rainbow mushroom"},
	(check_t){"urn_cathedral_l_2","ingredient_smallbone",2, "Small bone"},
	(check_t){"urn_cathedral_l_3","ingredient_rottenmeat",1, "Rotten meat"},
	(check_t){"urn_cathedral_l_4","ingredient_fishoil",1, "Fish oil"},
	(check_t){"urn_cathedral_l_5","ingredient_rottenmeat",1, "Rotten meat"},
	(check_t){"urn_cathedral_l_6","ingredient_rainbowsoup",1, "Rainbow soup"},
	(check_t){"urn_cathedral_r_01","ingredient_plantleaf",1, "Plant leaf"},
	(check_t){"urn_cathedral_r_02","ingredient_rottencake",1, "Rotten cake"},
	(check_t){"urn_cathedral_r_03","ingredient_toughcake",1, "Tough cake"},
	(check_t){"urn_cathedral_r_04","ingredient_spicyroll",1, "Spicy roll"},
	(check_t){"urn_cathedral_r_05","ingredient_rottenmeat",1, "Rottem meat"},
	(check_t){"urn_cathedral_r_06","ingredient_plantleaf",1, "Plant leaf"},
	(check_t){"urn_cathedral_r_07","ingredient_leechingpoultice",1, "Leeching poultice"},
	(check_t){"urn_cathedral_r_08","ingredient_smallbone",3, "Small bone"},
	(check_t){"urn_cathedral_r_09","ingredient_plantleaf",2, "Plant leaf"},
	(check_t){"urn_cathedral_r_10","ingredient_rottenmeat",1, "Rotten meat"},
	(check_t){"urn_cathedral_r_11","ingredient_poisonloaf",1, "Poison loaf"},
	(check_t){"urn_cathedral_r_12","ingredient_poisonsoup",1, "Poison soup"},
	(check_t){"urn_openwater_tr_1","ingredient_smallbone",3, "Small bone"},
	(check_t){"urn_openwater_tr_2","ingredient_rottenmeat",1, "Rotten meat"},
	(check_t){"urn_openwater_tr_3","ingredient_sealoaf",1, "Sea loaf"},
	(check_t){"crate_sunkencity_2_1","ingredient_fishoil",3, "Fish oil"},
	(check_t){"crate_sunkencity_2_2","ingredient_mushroom",2, "Mushroom"},
	(check_t){"crate_sunkencity_2_3","ingredient_spicymeat",2, "Spicy meat"},
	(check_t){"crate_sunkencity_1_1","ingredient_seacake",1, "Sea cake"},
	(check_t){"crate_sunkencity_1_2","ingredient_plantleaf",3, "Plant leaf"},
	(check_t){"beating_simon","upgrade_wok",1, "Wok"},
	(check_t){"health_egg_1","upgrade_health_1",1, "Health"},
	(check_t){"health_egg_2","upgrade_health_2",1, "Health"},
	(check_t){"health_egg_3","upgrade_health_3",1, "Health"},
	(check_t){"health_egg_4","upgrade_health_4",1, "Health"},
	(check_t){"health_egg_5","upgrade_health_5",1, "Health"},
	(check_t){"collect_anemone","collectible_anemone",1, "Anemone"},
	(check_t){"collect_arnassi_statue","collectible_arnassi_statue",1, "Arnassi statue"},
	(check_t){"collect_mithalas_banner","collectible_mithalas_banner",1, "Mithalas banner"},
	(check_t){"collect_bio_seed","collectible_bio_seed",1, "Bio sead"},
	(check_t){"collect_blackpearl","collectible_blackpearl",1, "Black pearl"},
	(check_t){"collect_treasure_chest","collectible_treasure_chest",1, "Treasure chest"},
	(check_t){"collect_energy_boss","collectible_energy_boss",1, "Energy boss"},
	(check_t){"collect_energy_statue","collectible_energy_statue",1, "Energy statue"},
	(check_t){"collect_golden_gear","collectible_golden_gear",1, "Golden gear"},
	(check_t){"collect_jelly_plant","collectible_jelly_plant",1, "Jelly plant"},
	(check_t){"collect_mithala_doll","collectible_mithala_doll",1, "Mithalas doll"},
	(check_t){"collect_mithala_spot","collectible_mithala_spot",1, "Mithalas spot"},
	(check_t){"collect_big_seed","collectible_big_seed",1, "Big seed"},
	(check_t){"collect_seed_bag","collectible_seed_bag",1, "Seed bag"},
	(check_t){"collect_skull","collectible_skull",1, "Skull"},
	(check_t){"collect_jelly_beacon","collectible_jelly_beacon",1, "Jelly beacon"},
	(check_t){"collect_spore_seed","collectible_spore_seed",1, "Spore seed"},
	(check_t){"collect_gold_star","collectible_gold_star",1, "Golden star"},
	(check_t){"collect_stone_head","collectible_stone_head",1, "Stone head"},
	(check_t){"collect_sun_key","collectible_sun_key",1, "Sun key"},
	(check_t){"collect_trident_head","collectible_trident_head",1, "Trident"},
	(check_t){"collect_turtle_egg","collectible_turtle_egg",1, "Turtle egg"},
	(check_t){"collect_upsidedown_seed","collectible_upsidedown_seed",1, "Upside down seed"},
	(check_t){"collect_walker","collectible_walker",1, "Baby walker"},
	(check_t){"collect_crab_costume","collectible_crab_costume",1, "Crab costume"},
	(check_t){"collect_jelly_costume","collectible_jelly_costume",1, "Jelly costume"},
	(check_t){"collect_mithalan_costume","collectible_mithalan_costume",1, "Mithalan costume"},
	(check_t){"collect_mutant_costume","collectible_mutant_costume",1, "Mutan costume"},
	(check_t){"collect_seahorse_costume","collectible_seahorse_costume",1, "Seahorse costume"},
	(check_t){"collect_teen_costume","collectible_teen_costume",1, "Teen costume"},
	(check_t){"collect_urchin_costume","collectible_urchin_costume",1, "Urchin costume"},
	(check_t){"collect_blaster","collectible_blaster",1, "Baby blaster"},
	(check_t){"collect_nautilus","collectible_nautilus",1, "Baby nautilus"},
	(check_t){"collect_piranha","collectible_piranha",1, "Baby piranha"}
};

#endif /* end of include guard RANDOMIZER_H */
