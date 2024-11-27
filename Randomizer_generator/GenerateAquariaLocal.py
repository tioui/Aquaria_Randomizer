"""
Author: Louis M
Date: Fri, 19 Apr 2024 19:50:39 +0000
Description: Generator for the Aquaria local randomizer
"""

import sys
from wsgiref.simple_server import make_server
from pyramid.config import Configurator
from pyramid.renderers import render_to_response
from pyramid.response import Response
from typing import Dict, List
from argparse import Namespace
import json

import Main
from BaseClasses import get_seed, MultiWorld, Location
from worlds.alttp.EntranceRandomizer import parse_arguments

from Options import ProgressionBalancing, Accessibility, LocalItems, NonLocalItems, StartInventory, StartHints, \
    StartLocationHints, ExcludeLocations, PriorityLocations, ItemLinks, StartInventoryPool, DeathLink
from worlds.aquaria import AquariaWorld
from worlds.aquaria.Options import AquarianTranslation, IngredientRandomizer, DishRandomizer, Objective, \
                                   TurtleRandomizer, EarlyEnergyForm, BigBossesToBeat, MiniBossesToBeat, \
                                   SkipFirstVision, NoProgressionHardOrHiddenLocation, LightNeededToGetToDarkPlaces, \
                                   BindSongNeededToGetUnderRockBulb, UnconfineHomeWater, BlindGoal, \
                                   InfiniteHotSoup, OpenBodyTongue, SkipFinalBoss3rdForm, MaximumIngredientAmount, \
                                   NoProgressionSimonSays, NoProgressionKelpForest, NoProgressionVeil, \
                                   NoProgressionMithalas, NoProgressionEnergyTemple, NoProgressionArnassiRuins, \
                                   NoProgressionFrozenVeil, NoProgressionAbyss, NoProgressionSunkenCity, \
                                   NoProgressionBody, EarlyBindSong

# Every checks (association Location -> Item)
checks: Dict[int, int] = {
    698000: 698107,
    698001: 698048,
    698002: 698096,
    698003: 698040,
    698004: 698049,
    698005: 698112,
    698006: 698085,
    698007: 698084,
    698008: 698043,
    698009: 698085,
    698010: 698106,
    698011: 698104,
    698012: 698089,
    698013: 698062,
    698014: 698090,
    698015: 698082,
    698016: 698083,
    698017: 698109,
    698018: 698092,
    698019: 698083,
    698020: 698082,
    698021: 698048,
    698022: 698052,
    698023: 698050,
    698024: 698041,
    698025: 698104,
    698026: 698078,
    698027: 698055,
    698028: 698085,
    698029: 698108,
    698030: 698085,
    698031: 698084,
    698032: 698093,
    698033: 698050,
    698034: 698049,
    698035: 698093,
    698036: 698072,
    698037: 698111,
    698038: 698081,
    698039: 698075,
    698040: 698113,
    698041: 698048,
    698042: 698050,
    698043: 698085,
    698044: 698075,
    698045: 698085,
    698046: 698056,
    698047: 698070,
    698048: 698087,
    698049: 698094,
    698050: 698088,
    698051: 698077,
    698052: 698049,
    698053: 698070,
    698054: 698087,
    698055: 698048,
    698056: 698056,
    698057: 698096,
    698058: 698114,
    698059: 698055,
    698060: 698055,
    698061: 698109,
    698062: 698070,
    698063: 698052,
    698064: 698101,
    698065: 698075,
    698066: 698038,
    698067: 698044,
    698068: 698085,
    698069: 698097,
    698070: 698038,
    698071: 698082,
    698072: 698048,
    698073: 698100,
    698074: 698055,
    698075: 698052,
    698076: 698086,
    698077: 698059,
    698078: 698105,
    698079: 698077,
    698080: 698057,
    698081: 698088,
    698082: 698088,
    698083: 698053,
    698084: 698039,
    698085: 698095,
    698086: 698045,
    698087: 698053,
    698088: 698082,
    698089: 698042,
    698090: 698041,
    698091: 698103,
    698092: 698060,
    698093: 698074,
    698094: 698054,
    698095: 698092,
    698096: 698050,
    698097: 698037,
    698098: 698064,
    698099: 698038,
    698100: 698038,
    698101: 698059,
    698102: 698085,
    698103: 698036,
    698104: 698058,
    698105: 698082,
    698106: 698045,
    698107: 698046,
    698108: 698080,
    698109: 698045,
    698110: 698090,
    698111: 698049,
    698112: 698051,
    698113: 698038,
    698114: 698063,
    698115: 698038,
    698116: 698069,
    698117: 698055,
    698118: 698038,
    698119: 698085,
    698120: 698050,
    698121: 698056,
    698122: 698078,
    698123: 698110,
    698124: 698047,
    698125: 698067,
    698126: 698067,
    698127: 698067,
    698128: 698109,
    698129: 698085,
    698130: 698067,
    698131: 698079,
    698132: 698073,
    698133: 698046,
    698134: 698073,
    698135: 698068,
    698136: 698063,
    698137: 698071,
    698138: 698091,
    698139: 698085,
    698140: 698073,
    698141: 698063,
    698142: 698056,
    698143: 698113,
    698144: 698108,
    698145: 698073,
    698146: 698065,
    698147: 698066,
    698148: 698113,
    698149: 698073,
    698150: 698076,
    698151: 698102,
    698152: 698061,
    698153: 698084,
    698154: 698075,
    698155: 698109,
    698156: 698099,
    698157: 698098,
    698158: 698098,
    698159: 698098,
    698160: 698098,
    698161: 698098,
    698162: 698000,
    698163: 698010,
    698164: 698001,
    698165: 698018,
    698166: 698003,
    698167: 698004,
    698168: 698030,
    698169: 698008,
    698170: 698009,
    698171: 698012,
    698172: 698015,
    698173: 698016,
    698174: 698019,
    698175: 698002,
    698176: 698024,
    698177: 698025,
    698178: 698013,
    698179: 698026,
    698180: 698011,
    698181: 698027,
    698182: 698028,
    698183: 698031,
    698184: 698032,
    698185: 698033,
    698186: 698035,
    698187: 698006,
    698188: 698014,
    698189: 698017,
    698190: 698020,
    698191: 698023,
    698192: 698029,
    698193: 698034,
    698194: 698021,
    698195: 698005,
    698196: 698007,
    698197: 698022,
    698198: 698107,
    698199: 698115,
    698200: 698116,
    698201: 698124,
    698202: 698117,
    698203: 698118,
    698204: 698119,
    698205: 698120,
    698206: 698121,
    698207: 698122,
    698208: 698123,
    698209: 698125,
    698210: 698126,
    698211: 698127,
    698212: 698128,
    698213: 698129,
    698214: 698130,
    698215: 698131,
    698216: 698132,
    698217: 698133,
}


def generate_basic_arguments() -> Namespace:
    """Generate the standard Archipelago's arguments"""
    arguments = parse_arguments([])
    arguments.skip_output = True
    arguments.plando_arguments = []
    arguments.plando_options = []
    arguments.accessibility = {1: Accessibility(2)}
    arguments.progression_balancing = {1: ProgressionBalancing(50)}
    arguments.local_items = {1: LocalItems([])}
    arguments.non_local_items = {1: NonLocalItems([])}
    arguments.start_inventory = {1: StartInventory({})}
    arguments.start_hints = {1: StartHints({})}
    arguments.start_location_hints = {1: StartLocationHints([])}
    arguments.exclude_locations = {1: ExcludeLocations([])}
    arguments.priority_locations = {1: PriorityLocations([])}
    arguments.item_links = {1: ItemLinks([])}
    arguments.start_inventory_from_pool = {1: StartInventoryPool({})}
    arguments.death_link = {1: DeathLink(0)}
    argument.csv_output = None
    return arguments

def generate_aquaria_arguments(options: Dict, arguments: Namespace) -> None:
    """Generating the Aquaria part of the Archipelago's arguments."""
    arguments.name = {1: "Player"}
    arguments.game = {1: "Aquaria"}
    if "aquarianTranslate" in options and options["aquarianTranslate"]:
        arguments.aquarian_translation = {1: AquarianTranslation(1)}
    else:
        arguments.aquarian_translation = {1: AquarianTranslation(0)}
    if "blindGoal" in options and options["blindGoal"]:
        arguments.blind_goal = {1: BlindGoal(1)}
    else:
        arguments.blind_goal = {1: BlindGoal(0)}
    if "randomizeIngredients" in options and 0 <= options["randomizeIngredients"] <= 2:
        arguments.ingredient_randomizer = {1: IngredientRandomizer(options["randomizeIngredients"])}
    else:
        arguments.ingredient_randomizer = {1: IngredientRandomizer(0)}
    if "randomizeDishes" in options and options["randomizeDishes"]:
        arguments.dish_randomizer = {1: DishRandomizer(1)}
    else:
        arguments.dish_randomizer = {1: DishRandomizer(0)}
    if "secretsNeeded" in options and options["secretsNeeded"]:
        arguments.objective = {1: Objective(1)}
    else:
        arguments.objective = {1: Objective(0)}
    if "randomizeTurtles" in options and 0 <= options["randomizeTurtles"] <= 2:
        arguments.turtle_randomizer = {1: TurtleRandomizer(options["randomizeTurtles"])}
    else:
        arguments.turtle_randomizer = {1: TurtleRandomizer(2)}
    if "earlyEnergyForm" in options and not options["earlyEnergyForm"]:
        arguments.early_energy_form = {1: EarlyEnergyForm(0)}
    else:
        arguments.early_energy_form = {1: EarlyEnergyForm(1)}
    if "earlyBindSong" in options and not options["earlyBindSong"]:
        arguments.early_bind_song = {1: EarlyBindSong(0)}
    else:
        arguments.early_bind_song = {1: EarlyBindSong(1)}
    if "bigBossesToBeat" in options and 0 <= options["bigBossesToBeat"] <= 5:
        arguments.big_bosses_to_beat = {1: BigBossesToBeat(options["bigBossesToBeat"])}
    else:
        arguments.big_bosses_to_beat = {1: BigBossesToBeat(0)}
    if "miniBossesToBeat" in options and 0 <= options["miniBossesToBeat"] <= 5:
        arguments.mini_bosses_to_beat = {1: MiniBossesToBeat(options["miniBossesToBeat"])}
    else:
        arguments.mini_bosses_to_beat = {1: MiniBossesToBeat(0)}
    if "skipFirstVision" in options and options["skipFirstVision"]:
        arguments.skip_first_vision = {1: SkipFirstVision(1)}
    else:
        arguments.skip_first_vision = {1: SkipFirstVision(0)}
    if "excludeHardItem" in options and options["excludeHardItem"]:
        arguments.no_progression_hard_or_hidden_locations = {1: NoProgressionHardOrHiddenLocation(1)}
    else:
        arguments.no_progression_hard_or_hidden_locations = {1: NoProgressionHardOrHiddenLocation(0)}
    if "noProgressionSimonSays" in options and options["noProgressionSimonSays"]:
        arguments.no_progression_simon_says = {1: NoProgressionSimonSays(1)}
    else:
        arguments.no_progression_simon_says = {1: NoProgressionSimonSays(0)}
    if "noProgressionKelpForest" in options and options["noProgressionKelpForest"]:
        arguments.no_progression_kelp_forest = {1: NoProgressionKelpForest(1)}
    else:
        arguments.no_progression_kelp_forest = {1: NoProgressionKelpForest(0)}
    if "noProgressionVeil" in options and options["noProgressionVeil"]:
        arguments.no_progression_veil = {1: NoProgressionVeil(1)}
    else:
        arguments.no_progression_veil = {1: NoProgressionVeil(0)}
    if "noProgressionMithalas" in options and options["noProgressionMithalas"]:
        arguments.no_progression_mithalas = {1: NoProgressionMithalas(1)}
    else:
        arguments.no_progression_mithalas = {1: NoProgressionMithalas(0)}
    if "noProgressionEnergyTemple" in options and options["noProgressionEnergyTemple"]:
        arguments.no_progression_energy_temple = {1: NoProgressionEnergyTemple(1)}
    else:
        arguments.no_progression_energy_temple = {1: NoProgressionEnergyTemple(0)}
    if "noProgressionArnassiRuins" in options and options["noProgressionArnassiRuins"]:
        arguments.no_progression_arnassi_ruins = {1: NoProgressionArnassiRuins(1)}
    else:
        arguments.no_progression_arnassi_ruins = {1: NoProgressionArnassiRuins(0)}
    if "noProgressionFrozenVeil" in options and options["noProgressionFrozenVeil"]:
        arguments.no_progression_frozen_veil = {1: NoProgressionFrozenVeil(1)}
    else:
        arguments.no_progression_frozen_veil = {1: NoProgressionFrozenVeil(0)}
    if "noProgressionAbyss" in options and options["noProgressionAbyss"]:
        arguments.no_progression_abyss = {1: NoProgressionAbyss(1)}
    else:
        arguments.no_progression_abyss = {1: NoProgressionAbyss(0)}
    if "noProgressionSunkenCity" in options and options["noProgressionSunkenCity"]:
        arguments.no_progression_sunken_city = {1: NoProgressionSunkenCity(1)}
    else:
        arguments.no_progression_sunken_city = {1: NoProgressionSunkenCity(0)}
    if "noProgressionBody" in options and options["noProgressionBody"]:
        arguments.no_progression_body = {1: NoProgressionBody(1)}
    else:
        arguments.no_progression_body = {1: NoProgressionBody(0)}
    if "lightNeededInDarkPlaces" in options and options["lightNeededInDarkPlaces"]:
        arguments.light_needed_to_get_to_dark_places = {1: LightNeededToGetToDarkPlaces(1)}
    else:
        arguments.light_needed_to_get_to_dark_places = {1: LightNeededToGetToDarkPlaces(0)}
    if "bindSongNeededForBulbUnderRock" in options and options["bindSongNeededForBulbUnderRock"]:
        arguments.bind_song_needed_to_get_under_rock_bulb = {1: BindSongNeededToGetUnderRockBulb(1)}
    else:
        arguments.bind_song_needed_to_get_under_rock_bulb = {1: BindSongNeededToGetUnderRockBulb(0)}
    if "infiniteHotSoup" in options and options["infiniteHotSoup"]:
        arguments.infinite_hot_soup = {1: InfiniteHotSoup(1)}
    else:
        arguments.infinite_hot_soup = {1: InfiniteHotSoup(0)}
    if "openBodyTongue" in options and options["openBodyTongue"]:
        arguments.open_body_tongue = {1: OpenBodyTongue(1)}
    else:
        arguments.open_body_tongue = {1: OpenBodyTongue(0)}
    if "skipFinalBoss3rdForm" in options and options["skipFinalBoss3rdForm"]:
        arguments.skip_final_boss_3rd_form = {1: SkipFinalBoss3rdForm(1)}
    else:
        arguments.skip_final_boss_3rd_form = {1: SkipFinalBoss3rdForm(0)}
    if "unconfineHomeWater" in options and 0 <= options["unconfineHomeWater"] <= 3:
        arguments.unconfine_home_water ={1: UnconfineHomeWater(options["unconfineHomeWater"])}
    else:
        arguments.unconfine_home_water ={1: UnconfineHomeWater(0)}
    if "maximumIngredientAmount" in options and 2 <= options["maximumIngredientAmount"] <= 20:
        arguments.maximum_ingredient_amount ={1: MaximumIngredientAmount(options["maximumIngredientAmount"])}
    else:
        arguments.maximum_ingredient_amount ={1: MaximumIngredientAmount(8)}


def generate_aquaria_multiworld(options: Dict) -> MultiWorld:
    """Generating a single player multiworld"""
    arguments = generate_basic_arguments()
    generate_aquaria_arguments(options, arguments)
    seed = get_seed()
    multiworld = Main.main(arguments, seed)
    return multiworld


def index_of_check(location_id: int) -> int:
    result: int = -1
    count = 0
    for check_id in checks:
        if location_id == check_id:
            result = count
        count = count + 1
    return result


def assign_location_to_item(checks_copy: Dict[int, int], array: list, location_index: int, item_id: int) -> None:
    item_location_id: int = -1
    item_index: int = -1
    count: int = 0
    for check_id in checks_copy:
        if (checks_copy[check_id] == item_id):
            item_location_id = check_id
            item_index = count
        count = count + 1
    assert item_location_id >= 0 and item_index >= 0
    array[location_index] = item_index
    checks_copy[item_location_id] = -1


def generate_json(options: Dict) -> str:
    """Generate the randomized json file to return to the player."""
    multiworld: MultiWorld = generate_aquaria_multiworld(options)
    values = {
        "version": 1,
        "uid": str(multiworld.seed),
        "aquarianTranslate": bool(options["aquarianTranslate"]),
        "blindGoal": bool(options["blindGoal"]),
        "secretsNeeded": bool(options["secretsNeeded"]),
        "bigBossesToBeat": options["bigBossesToBeat"],
        "miniBossesToBeat": options["miniBossesToBeat"],
        "skipFirstVision": bool(options["skipFirstVision"]),
        "infiniteHotSoup": bool(options["infiniteHotSoup"]),
        "openBodyTongue": bool(options["openBodyTongue"]),
        "skipFinalBoss3rdForm": bool(options["skipFinalBoss3rdForm"]),
        "maximumIngredientAmount": int(options["maximumIngredientAmount"]),
        "ingredientReplacement": [i for i in range(76)],
        "unconfineHomeWaterEnergyDoor": options["unconfineHomeWater"] in [1, 3],
        "unconfineHomeWaterTransturtle": options["unconfineHomeWater"] in [2, 3],
        "checksReplacement": [i for i in range(218)],
    }
    if isinstance(multiworld.worlds[1], AquariaWorld):
        # noinspection PyTypeChecker
        aquaria_world: AquariaWorld = multiworld.worlds[1]
        values["ingredientReplacement"] = aquaria_world.ingredients_substitution
        locations: List[Location] = multiworld.get_filled_locations(1)
        checks_copy: Dict[int, int] = checks.copy()
        for location in locations:
            location_id: int = location.address
            if location_id is not None:
                location_index: int = index_of_check(location_id)
                assign_location_to_item(checks_copy, values["checksReplacement"], location_index, location.item.code)

    return json.dumps(values)


def view_home_page(request) -> Response:
    """Return the home page view."""
    return render_to_response("templates/home.pt", {}, request)

def view_home_page_fr(request) -> Response:
    """Return the home page view.n french"""
    return render_to_response("templates/home_fr.pt", {}, request)

def view_generation(request) -> Response:
    """Return a json download Response"""
    result = None
    if request.method == "POST":
        options = {
            "aquarianTranslate": False,
            "blindGoal": False,
            "secretsNeeded": 0,
            "bigBossesToBeat": 0,
            "miniBossesToBeat": 0,
            "skipFirstVision": False,
            "randomizeIngredients": 0,
            "randomizeDishes": False,
            "randomizeTurtles": 0,
            "earlyEnergyForm": 1,
            "earlyBindSong": 1,
            "excludeHardItem": 0,
            "lightNeededInDarkPlaces": 1,
            "bindSongNeededForBulbUnderRock": 0,
            "unconfineHomeWater": 0,
            "skipFinalBoss3rdForm": 0,
            "openBodyTongue": 0,
            "infiniteHotSoup": 1,
            "maximumIngredientAmount": 8,
            "noProgressionSimonSays": 0,
            "noProgressionKelpForest": 0,
            "noProgressionVeil": 0,
            "noProgressionMithalas": 0,
            "noProgressionEnergyTemple": 0,
            "noProgressionArnassiRuins": 0,
            "noProgressionFrozenVeil": 0,
            "noProgressionAbyss": 0,
            "noProgressionSunkenCity": 0,
            "noProgressionBody": 0,
        }
        for key, value in request.POST.items():
            try:
                options[key] = int(value)
            except ValueError:
                options[key] = value
        json = generate_json(options)
        result = Response(json)
        result.content_type = 'application/json'
        result.content_disposition = 'attachment; filename="aquaria_randomized.json"'
    else:
        result = render_to_response("templates/home.pt", {}, request)
    return result


if __name__ == '__main__':
    with Configurator() as config:
        config.include("pyramid_chameleon")
        config.add_route('home', '/')
        config.add_route('homefr', '/fr')
        config.add_route('generation', '/generation')
        config.add_view(view_home_page, route_name='home')
        config.add_view(view_home_page_fr, route_name='homefr')
        config.add_view(view_generation, route_name='generation')
        config.add_static_view(name='static', path='static_assets')
        app = config.make_wsgi_app()
    port_number: int
    if len(sys.argv) > 1:
        try:
            port_number = int(sys.argv[1])
        except ValueError:
            port_number = 6543
    else:
        port_number = 6543
    server = make_server('0.0.0.0', port_number, app)
    server.serve_forever()
