/*
 * Filename:       warfare.h
 * Description:    Should hold definitions for the warfare module
 *
 * Added to warfare module by Boron, Oct 25 1999
 *
 */
#ifndef WARFARE_DEFINES
#define WARFARE_DEFINES

#define WARFARE_ENABLED    1
#define WAR_PATH    "/d/Krynn/common/warfare/"

#define ARMY_PATH   (WAR_PATH + "armies/")
#define AREA_PATH   (WAR_PATH + "areas/")
#define REWARDS_PATH (WAR_PATH + "rewards/")
#define WEP_PATH    (WAR_PATH + "weapons/")
#define ARM_PATH    (WAR_PATH + "armours/")

/* Army master */
#ifndef ARMYMASTER
#define ARMYMASTER  (WAR_PATH + "armymaster")
#endif

/* Property recording attempted last time conquer command used */
#define PLAYER_LAST_CONQUER    "krynn_warfare_last_conquer_time"

#define WAR_CLUB_ADMIN ("/d/Krynn/clubs/warfare/warfare_club_manager")

#define ARMY_BASE   (WAR_PATH + "army")
#define AREA_BASE   (WAR_PATH + "area")
#define AUTO_RECRUIT (WAR_PATH + "auto_recruit")

#define RECRUITBASE (WAR_PATH + "recruit_base")
#define WARSHOP     (WAR_PATH + "std/warshop")

/* Warfare areas */
#define WAR_AREA_NEWPORT      "Newports Area"
#define WAR_AREA_WESTSOL      "Western Solamnian Plains"
#define WAR_AREA_ESTWILDE     "Estwilde Plains"
#define WAR_AREA_SOLACE       "Solace Area"
#define WAR_AREA_CENTRAL_ABANASINIA    "Central Abanasinian Plains"
#define WAR_AREA_NORTH_ABANASINIA      "North Abanasinian Plains"
#define WAR_AREA_NIGHLUND     "Nightlund Plains"
#define WAR_AREA_GUARDLUND    "Guardlund Plains"
#define WAR_AREA_THROTYL      "Throtyl Pass"
#define WAR_AREA_ICEWALL       "Icewall Plains"
#define WAR_AREA_TRELGORN     "Trelgorn Forest"
/* Old warfare area names (should not be used) */
#define WAR_AREA_ABANASINIAN  "Abanasinian Plains"
#define WAR_AREA_EASTSOL      "Eastern Solamnian Plains"

#ifndef ONE_OF(x)
#define ONE_OF(x)     ((x)[random(sizeof(x))])
#endif 

/* Army names */
#define FREE_ARMY   "Free People"

#define KNIGHT_ARMY "Knights"
#define NEIDAR_ARMY "Neidar Clan"

#define RED_ARMY    "Red Dragon Army"
#define BLUE_ARMY   "Blue Dragon Army"
#define BLACK_ARMY  "Black Dragon Army"
#define GREEN_ARMY  "Green Dragon Army"
#define WHITE_ARMY  "White Dragon Army"


/* Guild names */
#define NEIDAR_GUILD      "Dwarven Warriors of the Neidar Clan"
#define SOLAMNIAN_KNIGHTS "Solamnian Knights"

/* Peace year (no war in or before this year) */
#define PEACE_YEAR  353

/*
 * Default recruit amount and tax amount
 */
#define DEFAULT_TAX_BASE      1010
#define DEFAULT_RECRUIT_BASE  6

/* The price of the unit is calculated with this
 * price - the base unit price
 * units - number of units in the area
 */
#define UNIT_PRICE(price, units)  ((price) * pow((units) + 1.0, 1.4) / \
                                   ((units) + 1.0))

/*
 * The recruit rate drops as the number of recruits increase, this gives
 * an absolute max of 400 but the real one is probably around 200. 
 */
#define RECRUIT_RATE(base, recruits) ((base) * pow((recruits), \
                                                   -((recruits) / 400.0)))

#define WARFARE_DEBUG(x)      find_player("arman")->catch_msg("[War] " + x + "\n")
#define WARFARE_ARMOUR_PROP   "_krynn_warfare_special_mitigation_prop"

#define WARFARE_MAP     (WAR_PATH + "warfare_map")

#define W_LOG           ("warfare/war.log")
#define C_LOG           ("warfare/war_conq.log")
//#define DEBUG(x)	find_player("cotillion")->catch_tell(x)

// Logs can be found in /d/Krynn/log/warfare/
#define WAR_LOG(x)      log_file(W_LOG, ctime(time()) + ": " + (x) + "\n", 1048576)
#define CONQ_LOG(x)     log_file(C_LOG, ctime(time()) + ": " + (x) + "\n", 1048576)

#ifndef WARFARE_AREAS
#define WARFARE_AREAS      ({ "Newports Area", \
                              "Solace Area", \
                              "Central Abanasinian Plains", \
                              "North Abanasinian Plains", \
                              "Nightlund Plains", \
                              "Guardlund Plains", \
                              "Western Solamnian Plains", \
                              "Estwilde Plains", \
                              "Throtyl Pass", \
                              "Icewall Plains", \
                              "Trelgorn Forest" })
#endif 

#define TOP_TIER_AREAS     ({ "North Abanasinian Plains", \
                              "Nightlund Plains", \
                              "Western Solamnian Plains", \
                              "Estwilde Plains", \
                              "Icewall Plains" })

#ifndef WARFARE_ARMIES
#define WARFARE_ARMIES      ({ "Knights", \
                               "Neidar Clan", \
                               "Free People", \
                               "Red Dragon Army", \
                               "Blue Dragon Army", \
                               "Black Dragon Army", \
                               "Green Dragon Army", \
                               "White Dragon Army" })
#endif

#ifndef WARFARE_ARMIES_NAMES
#define WARFARE_ARMIES_NAMES ([ \
   "Knights" : "Knights of Solamnia", \
   "Neidar Clan" : "Neidar Clan", \
   "Free People" : "Free People of Krynn", \
   "Red Dragon Army" : "Red Dragonarmy", \
   "Blue Dragon Army" : "Blue Dragonarmy", \
   "Black Dragon Army" : "Black Dragonarmy", \
   "Green Dragon Army" : "Green Dragonarmy", \
   "White Dragon Army" : "White Dragonarmy" ])
#endif

// Some rooms such as standard room files are added that are 
// inaccessible to players. Add to this list.
#define EXCLUDED_ROOMS ({ \
    "/d/Krynn/solamn/splains/room/on_rock", \
    "/d/Krynn/solamn/splains/room/in_water", \
    "/d/Krynn/solamn/splains/room/in_water1", \
    "/d/Krynn/solamn/splains/room/in_water2", \
    "/d/Krynn/solamn/splains/room/in_water3", \
    "/d/Krynn/solamn/splains/room/in_water4", \
    "/d/Krynn/solamn/splains/room/in_water5", \
    "/d/Krynn/solamn/splains/room/in_water6", \
    "/d/Krynn/solamn/splains/room/changeroom", \
    "/d/Krynn/solamn/splains/room/outside_room_base", \
    "/d/Krynn/trelgorn/fields/field_base", \
    "/d/Krynn/solace/guild/maze_base", \
    "/d/Krynn/solace/guild/maze1", \
    "/d/Krynn/solace/guild/maze2", \
    "/d/Krynn/solace/guild/maze3", \
    "/d/Krynn/solace/guild/maze4", \
    "/d/Krynn/solace/guild/maze5", \
    "/d/Krynn/solace/guild/maze6", \
    "/d/Krynn/solace/guild/maze7", \
    "/d/Krynn/solace/graves/grave_std", \
    "/d/Krynn/solace/std/forest_outbase", \
    "/d/Krynn/solace/new_village/town_square/rooms/square_base", \
    "/d/Krynn/que/camp/camp_base", \
    "/d/Krynn/solace/std/solace_outbase2", \
    "/d/Krynn/solace/std/outside_base", \
    "/d/Krynn/que/camp/camp_base", \
    "/d/Krynn/que/newports/village20141014", \
    "/d/Krynn/que/newports/village1", \
    "/d/Krynn/que/newports/newport_recruitment", \
    "/d/Krynn/neraka/dragon/landing1", \
    "/d/Krynn/que/newports/newport_base" })

// Reward defines
#define MASTERWORK_PROP       "_krynn_warfare_masterwork_armour"

#define MASTERWORK_STEEL_PRICES ([ \
    "steel longsword" : 80, \
    "steel greatsword" : 100, \
    "ironwood staff" : 100, \
    "ironwood hoopak" : 100, \
    "one-handed spear" : 80, \
    "steel long-spear" : 100, \
    "steel battleaxe" : 80, \
    "steel greataxe" : 100, \
    "fine steel dagger" : 50, \
    "steel battle mace" : 80, \
    "steel warhammer" : 100, \
    "red cedar greatbow" : 150, \
    "engraved ironwood wand" : 60, \
    "masterwork platemail" : 100, \
    "masterwork chainmail" : 80, \
    "leather breastplate" : 60, \
    "fine tunic" : 40, \
    "steel helm" : 60, \
    "chain hood" : 50, \
    "studded coif" : 40, \
    "tower shield" : 80, \
    "circular reinforced buckler" : 50, \
    "pair of plate gauntlets" : 50, \
    "pair of chain gloves" : 40, \
    "pair of leather gloves" : 30, \
    "pair of plate greaves" : 50, \
    "pair of chain leggings" : 40, \
    "pair of leather leggings" : 30 ])

#define KRYNN_WAR_GEM   "/d/Genesis/gems/obj/krynn/"

#define KRYNN_WAR_GEM_TIER1_SPAWN ([ \
    "ellipse" : ({ \
        KRYNN_WAR_GEM + "ellipse_azure_diamond", \
        KRYNN_WAR_GEM + "ellipse_blue_diamond", \
        KRYNN_WAR_GEM + "ellipse_white_diamond", \
        KRYNN_WAR_GEM + "ellipse_black_tourmaline", \
        KRYNN_WAR_GEM + "ellipse_blue_tourmaline", \
        KRYNN_WAR_GEM + "ellipse_brown_tourmaline", \
        KRYNN_WAR_GEM + "ellipse_red_tourmaline", \
        KRYNN_WAR_GEM + "ellipse_violet_tourmaline", \
        KRYNN_WAR_GEM + "ellipse_yellow_tourmaline" \
        }), \
    "tear" : ({ \
        KRYNN_WAR_GEM + "teardrop_beryl", \
        KRYNN_WAR_GEM + "teardrop_bloodstone", \
        KRYNN_WAR_GEM + "teardrop_carnelian", \
        KRYNN_WAR_GEM + "teardrop_diamond", \
        KRYNN_WAR_GEM + "teardrop_jade", \
        KRYNN_WAR_GEM + "teardrop_opal", \
        KRYNN_WAR_GEM + "teardrop_pyrite", \
        KRYNN_WAR_GEM + "teardrop_spinel", \
        KRYNN_WAR_GEM + "teardrop_topaz" \
        }), \
    "triangular" : ({ \
        KRYNN_WAR_GEM + "triangular_sea_agate" \
        }), \
    "oval" : ({ \
        KRYNN_WAR_GEM + "oval_azure_sapphire", \
        KRYNN_WAR_GEM + "oval_black_sapphire", \
        KRYNN_WAR_GEM + "oval_blue_sapphire", \
        KRYNN_WAR_GEM + "oval_brown_agate", \
        KRYNN_WAR_GEM + "oval_green_sapphire", \
        KRYNN_WAR_GEM + "oval_magenta_sapphire", \
        KRYNN_WAR_GEM + "oval_mauve_sapphire", \
        KRYNN_WAR_GEM + "oval_milky_quartz", \
        KRYNN_WAR_GEM + "oval_moonstone", \
        KRYNN_WAR_GEM + "oval_purple_amethyst", \
        KRYNN_WAR_GEM + "oval_rose_quartz", \
        KRYNN_WAR_GEM + "oval_smoky_quartz", \
        KRYNN_WAR_GEM + "oval_striped_chalcedony", \
        KRYNN_WAR_GEM + "oval_violet_sapphire", \
        KRYNN_WAR_GEM + "oval_amber_aragonite" \
        }) \
])

// The chance of an augmentation crystal spawning. 
//
// 1 in x chance, where x is reduced by (gLevel * 2) 
// of the spawn, where gLevel is between 0 and 5.
// So with GEM_SPAWN_CHANCE of 50 chance of spawning
// an augmentation crystal is between 2% and 2.5%

#define GEM_SPAWN_CHANCE  50

#define KRYNN_WAR_GEM_TIER2_SPAWN ([ \
    "ellipse" : ({ \
        KRYNN_WAR_GEM + "ellipse_azure_diamond", \
        KRYNN_WAR_GEM + "ellipse_blue_diamond", \
        KRYNN_WAR_GEM + "ellipse_white_diamond", \
        KRYNN_WAR_GEM + "ellipse_black_tourmaline", \
        KRYNN_WAR_GEM + "ellipse_blue_tourmaline", \
        KRYNN_WAR_GEM + "ellipse_brown_tourmaline", \
        KRYNN_WAR_GEM + "ellipse_red_tourmaline", \
        KRYNN_WAR_GEM + "ellipse_violet_tourmaline", \
        KRYNN_WAR_GEM + "ellipse_yellow_tourmaline" \
        }), \
    "tear" : ({ \
        KRYNN_WAR_GEM + "glowing_teardrop_beryl", \
        KRYNN_WAR_GEM + "glowing_teardrop_bloodstone", \
        KRYNN_WAR_GEM + "glowing_teardrop_carnelian", \
        KRYNN_WAR_GEM + "glowing_teardrop_diamond", \
        KRYNN_WAR_GEM + "glowing_teardrop_jade", \
        KRYNN_WAR_GEM + "glowing_teardrop_opal", \
        KRYNN_WAR_GEM + "glowing_teardrop_pyrite", \
        KRYNN_WAR_GEM + "glowing_teardrop_spinel", \
        KRYNN_WAR_GEM + "glowing_teardrop_topaz" \
        }), \
    "triangular" : ({ \
        KRYNN_WAR_GEM + "triangular_amber", \
        KRYNN_WAR_GEM + "triangular_garnet", \
        KRYNN_WAR_GEM + "triangular_peridot", \
        KRYNN_WAR_GEM + "triangular_topaz" \
        }), \
    "oval" : ({ \
        KRYNN_WAR_GEM + "oval_azure_sapphire", \
        KRYNN_WAR_GEM + "oval_black_sapphire", \
        KRYNN_WAR_GEM + "oval_blue_sapphire", \
        KRYNN_WAR_GEM + "oval_brown_agate", \
        KRYNN_WAR_GEM + "oval_green_sapphire", \
        KRYNN_WAR_GEM + "oval_magenta_sapphire", \
        KRYNN_WAR_GEM + "oval_mauve_sapphire", \
        KRYNN_WAR_GEM + "oval_milky_quartz", \
        KRYNN_WAR_GEM + "glowing_oval_moonstone", \
        KRYNN_WAR_GEM + "oval_purple_amethyst", \
        KRYNN_WAR_GEM + "oval_rose_quartz", \
        KRYNN_WAR_GEM + "oval_smoky_quartz", \
        KRYNN_WAR_GEM + "oval_striped_chalcedony", \
        KRYNN_WAR_GEM + "oval_violet_sapphire" \
        }) \
])

#define WARFARE_GEM_CUT  ({ "ellipse", "tear", "triangular", "oval" })

#define MASTERWORK_SKILL_BONUS       5
#define BASIC_RESIST_BONUS           3
#define SUPERIOR_RESIST_BONUS        6

#define SEE_INVIS_ABILITY   (REWARDS_PATH + "magic_effects/see_invis_ability.c")
#define SCRY_PROT_ABILITY   (REWARDS_PATH + "magic_effects/prot_scry_ability.c")
#define BREATHE_WATER_ABILITY   (REWARDS_PATH + "magic_effects/underwater_breath_ability.c")
#define QUICK_REFLEX_ABILITY   (REWARDS_PATH + "magic_effects/quick_reflex_ability.c")
#define SEE_DARK_ABILITY   (REWARDS_PATH + "magic_effects/see_dark_ability.c")

//   Gem name, gem slot type, benefit type, benefit bonus, gem description
#define MASTERWORK_GEM_PROPS ([ \
    "_crystal_of_striking" : ({ "ellipse", "hit", 10, "ellipse-shaped white diamond" }), \
    "_crystal_of_demolition" : ({ "ellipse", "pen", 10, "ellipse-shaped blue diamond" }), \
    "_crystal_of_weaponry" : ({ "ellipse", "hit-pen", 5, "ellipse-shaped blue-white diamond" }), \
    "_crystal_of_fire" : ({ "ellipse", "skill", SS_ELEMENT_FIRE, "ellipse-shaped red tourmaline" }), \
    "_crystal_of_water" : ({ "ellipse", "skill", SS_ELEMENT_WATER, "ellipse-shaped blue tourmaline" }), \
    "_crystal_of_air" : ({ "ellipse", "skill", SS_ELEMENT_AIR, "ellipse-shaped yellow tourmaline" }), \
    "_crystal_of_earth" : ({ "ellipse", "skill", SS_ELEMENT_EARTH, "ellipse-shaped brown tourmaline" }), \
    "_crystal_of_death" : ({ "ellipse", "skill", SS_ELEMENT_DEATH, "ellipse-shaped black tourmaline" }), \
    "_crystal_of_life" : ({ "ellipse", "skill", SS_ELEMENT_LIFE, "ellipse-shaped violet tourmaline" }), \
    "_iron_ward_diamond" : ({ "tear", "ac", 2, "teardrop-shaped diamond" }), \
    "_greater_iron_ward_diamond" : ({ "tear", "ac", 5, "glowing teardrop-shaped diamond" }), \
    "_fire_resistance_crystal" : ({ "tear", "lesser_resist", "fire", "teardrop-shaped carnelian" }), \
    "_greater_fire_resistance_crystal" : ({ "tear", "greater_resist", "fire", "glowing teardrop-shaped carnelian" }), \
    "_water_resistance_crystal" : ({ "tear", "lesser_resist", "water", "teardrop-shaped blue topaz" }), \
    "_greater_water_resistance_crystal" : ({ "tear", "greater_resist", "water", "glowing teardrop-shaped blue topaz" }), \
    "_death_resistance_crystal" : ({ "tear", "lesser_resist", "death", "teardrop-shaped bloodstone" }), \
    "_greater_death_resistance_crystal" : ({ "tear", "greater_resist", "death", "glowing teardrop-shaped bloodstone" }), \
    "_life_resistance_crystal" : ({ "tear", "lesser_resist", "life", "teardrop-shaped opal" }), \
    "_greater_life_resistance_crystal" : ({ "tear", "greater_resist", "life", "glowing teardrop-shaped opal" }), \
    "_air_resistance_crystal" : ({ "tear", "lesser_resist", "air", "teardrop-shaped blue spinel" }), \
    "_greater_air_resistance_crystal" : ({ "tear", "greater_resist", "air", "glowing teardrop-shaped blue spinel" }), \
    "_earth_resistance_crystal" : ({ "tear", "lesser_resist", "earth", "teardrop-shaped golden pyrite" }), \
    "_greater_earth_resistance_crystal" : ({ "tear", "greater_resist", "earth", "glowing teardrop-shaped pyrite" }), \
    "_poison_resistance_crystal" : ({ "tear", "lesser_resist", "poison", "teardrop-shaped green jade" }), \
    "_greater_poison_resistance_crystal" : ({ "tear", "greater_resist", "poison", "glowing teardrop-shaped green jade" }), \
    "_cold_resistance_crystal" : ({ "tear", "lesser_resist", "cold", "teardrop-shaped colourless beryl" }), \
    "_greater_cold_resistance_crystal" : ({ "tear", "greater_resist", "cold", "glowing teardrop-shaped beryl" }), \
    "_scry_protection_crystal" : ({ "triangular", "special", "scry_prot", "triangular-shaped yellow topaz" }), \
    "_see_invisible_crystal" : ({ "triangular", "special", "see_invis", "triangular-shaped green peridot" }), \
    "_watermere_crystal" : ({ "triangular", "special", "breath_water", "triangular-shaped blue agate" }), \
    "_reflex_crystal" : ({ "triangular", "special", "speed", "triangular-shaped orange garnet" }), \
    "_see_dark_crystal" : ({ "triangular", "special", "see_dark", "triangular-shaped yellow amber" }), \
    "_crystal_of_defence" : ({ "oval", "skill", SS_DEFENCE, "oval-shaped blue sapphire" }), \
    "_crystal_of_deflection" : ({ "oval", "skill", SS_PARRY, "oval-shaped green sapphire" }), \
    "_crystal_of_ambidexterity" : ({ "oval", "skill", SS_2H_COMBAT, "oval-shaped azure sapphire" }), \
    "_crystal_of_shrouding" : ({ "oval", "skill", SS_HIDE, "oval-shaped black sapphire" }), \
    "_crystal_of_stealth" : ({ "oval", "skill", SS_SNEAK, "oval-shaped violet sapphire" }), \
    "_crystal_of_opening" : ({ "oval", "skill", SS_OPEN_LOCK, "oval-shaped mauve sapphire" }), \
    "_crystal_of_disarming" : ({ "oval", "skill", SS_FR_TRAP, "oval-shaped magenta sapphire" }), \
    "_crystal_of_transmutation" : ({ "oval", "skill", SS_FORM_TRANSMUTATION, "oval-shaped rose quartz" }), \
    "_crystal_of_illusion" : ({ "oval", "skill", SS_FORM_ILLUSION, "oval-shaped milky quartz" }), \
    "_crystal_of_divination" : ({ "oval", "skill", SS_FORM_DIVINATION, "oval-shaped smoky quartz" }), \
    "_crystal_of_enchantment" : ({ "oval", "skill", SS_FORM_ENCHANTMENT, "oval-shaped striped chalcedony" }), \
    "_crystal_of_conjuration" : ({ "oval", "skill", SS_FORM_CONJURATION, "oval-shaped purple amethyst" }), \
    "_crystal_of_abjuration" : ({ "oval", "skill", SS_FORM_ABJURATION, "oval-shaped brown agate" }), \
    "_crystal_of_hunting" : ({ "oval", "skill", SS_HUNTING, "oval-shaped amber aragonite" }), \
    "_featherweight_crystal" : ({ "oval", "weight", 1, "oval-shaped moonstone" }), \
    "_greater_featherweight_crystal" : ({ "oval", "weight", 3, "glowing oval-shaped moonstone" }) \
])


#endif

