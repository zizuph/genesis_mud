#include "/d/Calia/domain.h"

// Elementalist Guilds General Defines

#define GUILD_SHORT_NAME         "elementalist"
#define GUILD_STYLE              "cleric"

#define ELEMENTALIST_DIR         "/d/Calia/guilds/elementalists/"

#define ELEMENTALIST_DATA                   ELEMENTALIST_DIR + "data/"
#define ELEMENTALIST_HELP                   ELEMENTALIST_DIR + "help/"
#define ELEMENTALIST_CLERIC_HELP            ELEMENTALIST_DIR + "help/cleric/"
#define ELEMENTALIST_RACIAL_HELP            ELEMENTALIST_DIR + "help/racial/"
#define ELEMENTALIST_HELP_SPELLS            ELEMENTALIST_HELP + "spells/"
#define ELEMENTALIST_HELP_CLERIC_SPELLS     ELEMENTALIST_HELP + "spells/cleric/"
#define ELEMENTALIST_OBJS                   ELEMENTALIST_DIR + "objs/"
#define ELEMENTALIST_COMPONENTS             ELEMENTALIST_OBJS + "components/"
#define ELEMENTALIST_GEMSHARDS              ELEMENTALIST_OBJS + "gemshards/"
#define ELEMENTALIST_NPCS                   ELEMENTALIST_DIR + "npcs/"
#define ELEMENTALIST_LOGS                   ELEMENTALIST_DIR + "logs/"
#define ELEMENTALIST_LIBS                   ELEMENTALIST_DIR + "lib/"
#define ELEMENTALIST_SHADOWS                ELEMENTALIST_DIR + "shadows/"
#define ELEMENTALIST_SPECIALS               ELEMENTALIST_DIR + "specials/"
#define ELEMENTALIST_SPELLS                 ELEMENTALIST_DIR + "spells/"
#define ELEMENTALIST_SPELL_OBJS             ELEMENTALIST_SPELLS + "objs/"
#define ELEMENTALIST_SOULS                  ELEMENTALIST_DIR + "souls/"
#define ELEMENTALIST_BOARD_NOTES            ELEMENTALIST_DIR + "board_notes/"
#define ELEMENTALIST_TEXTS                  ELEMENTALIST_DIR + "texts/"

// Guild Locations
#define ELEMENTALIST_TEMPLE          ELEMENTALIST_DIR + "temple/"
#define ELEMENTALIST_GARDEN          ELEMENTALIST_TEMPLE + "garden/"

// Master Objects
#define GUILD_MANAGER            (ELEMENTALIST_LIBS + "guild_manager")

// Guild NPCS
#define ELEMENTALIST_GUILDMASTER (ELEMENTALIST_NPCS + "guildmaster")

// Log Files
#define COUNCIL_LOG (ELEMENTALIST_LOGS + "council_log")
#define CLERIC_COUNCIL_LOG (ELEMENTALIST_LOGS + "cleric_council_log")
#define CONSTRUCTION_LOG (ELEMENTALIST_LOGS + "construction_log")
#define COUNCIL_LOG_BOOK (ELEMENTALIST_OBJS + "council_log_book")
#define EVENTS_LOG (ELEMENTALIST_LOGS + "events")

// Cleric Guild Defines

#define GUILD_EC_NAME            "Elemental Clerics of Calia"
#define GUILD_RACE_TYPE          "racial"
#define GUILD_EC_TYPE            "occupational"
#define GUILD_EC_RACE_TAX        2
#define GUILD_EC_OCC_TAX         25
#define GUILD_EC_LAY_TAX         5
#define GUILD_EC_FIRE_LAY_TAX    9
#define GUILD_EC_AIR_LAY_TAX     9
#define GUILD_EC_WATER_LAY_TAX   10
#define GUILD_EC_EARTH_LAY_TAX   7
#define GUILD_EC_SPIRIT_LAY_TAX  10
#define EC_GURU_GROUP            2
#define EC_GURU_BIT              11
#define EC_GURU_EXP              250
#define EC_RACE_SOUL             (ELEMENTALIST_SOULS   + "race_cleric_soul")
#define EC_SOUL                  (ELEMENTALIST_SOULS   + "occ_cleric_soul")
#define EC_LAY_SOUL              (ELEMENTALIST_SOULS   + "lay_cleric_soul")
#define EC_RACE_SHADOW           (ELEMENTALIST_SHADOWS + "race_cleric_shadow")
#define EC_OCC_SHADOW            (ELEMENTALIST_SHADOWS + "occ_cleric_shadow")
#define EC_LAY_SHADOW            (ELEMENTALIST_SHADOWS + "lay_cleric_shadow")
#define EC_CHILD_MANDALA_TASK    "_ec_child_manadala_task"
#define TIHOSSKIAS_TIME          49
#define TEICHOS_TIME             12
#define SYNDYASMOS_MANA          60
#define SYNDYASMOS_CONDUIT_COST  100
#define ECTELEPORT_AIR           10
#define ECTELEPORT_OTHERS        5
#define CONDUIT_PENALTY          "_ec_conduit_penalty"
#define MAX_PERSONAL_CONDUIT     30000
#define MAX_PRACTICE_LEVEL       100000
#define CLERIC_GUILD_POST        ELEMENTALIST_TEMPLE + "postoffice"
#define BANNED_GUILDS            ( ({ "Morgul Mages",                    \
                                    "Necromancers Of Vile Darkness",\
                                   }) )

// Worshipper Guild Defines

#define GUILD_EW_NAME            "Elemental Worshippers of Calia"
#define GUILD_EW_TYPE            "layman"
#define GUILD_EW_TAX             14
#define EW_SOUL                  (ELEMENTALIST_SOULS   + "lay_worshipper_soul")
#define EW_SOUL2                 (ELEMENTALIST_SOULS   + "lay_worshipper_soul2")
#define EW_SHADOW                (ELEMENTALIST_SHADOWS + "lay_worshipper_shadow")

// Seeker Guild Defines

#define GUILD_ES_NAME            "Elemental Seekers of Calia"
#define GUILD_ES_TYPE            "layman"
#define GUILD_ES_TAX             6
#define ES_SOUL                  (ELEMENTALIST_SOULS   + "lay_seeker_soul")
#define ES_SHADOW                (ELEMENTALIST_SHADOWS + "lay_seeker_shadow")

// Shadows and Souls

#define SPELL_MANAGER_SOUL       ("/d/Genesis/specials/guilds/souls/spell_manager_soul")
#define MANA_SHADOW              ("/d/Genesis/specials/guilds/shadows/mana_shadow")

// Default stat weighting of spells for cleric guild style
#define STAT_WEIGHTING   ({ SKILL_WEIGHT, 60, TS_WIS, SKILL_WEIGHT, 20, TS_INT, SKILL_WEIGHT, 20, TS_DIS })


// Useful Macros
#define IS_GUILDMASTER(x)    IN_ARRAY(x->query_real_name(), SECURITY->query_guild_masters(GUILD_SHORT_NAME))
#define IS_CALIA_WIZ(x)      IN_ARRAY(x->query_real_name(), SECURITY->query_domain_members("calia"))
#define IS_CLERIC(x)         ((x)->is_elemental_cleric() || (x)->is_spirit_member())
#define IS_WORSHIPPER(x)     (x)->is_elemental_worshipper()
#define IS_SEEKER(x)         (x)->is_elemental_seeker()
#define IS_MEMBER(x)         (IS_CLERIC(x) || IS_WORSHIPPER(x) || IS_SEEKER(x))

// Other Defines
#define GARDENING_HOE           (ELEMENTALIST_OBJS + "hoe")
#define GARDENING_SECATEUR      (ELEMENTALIST_OBJS + "shears")
#define GARDENING_WATERINGCAN   ("/d/Calia/mountain/obj/watering_can")
#define GARDENING_BASKET        (ELEMENTALIST_OBJS + "basket")
#define GARDENING_SHED_SHELF    (ELEMENTALIST_OBJS + "garden_shelf")
#define MAX_GUILD_CONDUIT_SCORE 101250
#define OBJ_I_ELEMENTAL_STAFF         "_obj_i_elemental_staff"
#define LIVE_I_PURIFIED_CLERIC_ITEMS  "_live_i_purified_cleric_items"
#define LIVE_I_PLACED_CLERIC_CYLINDER "_live_i_placed_cleric_cylinder"
#define LIVE_I_PLACED_CLERIC_TRIANGLE "_live_i_placed_cleric_triangle"
#define LIVE_I_PLACED_CLERIC_SYMBOL   "_live_i_placed_cleric_symbol"
#define LIVE_I_ON_CLERIC_GURU_QUEST   "_live_i_on_cleric_guru_quest"
#define LIVE_I_SYNDYASMOS_CAST        "_live_i_syndyasmos_cast"
#define LIVE_I_LIVRA_CAST             "_live_i_livra_cast"
#define LIVE_I_TYFLOS_CAST            "_live_i_tyflos_cast"
#define LIVE_I_PERIKA_CAST            "_live_i_perika_cast"
#define LIVE_I_TEICHOS_CAST           "_live_i_teichos_cast"
#define LIVE_I_TIHOSSKIAS_CAST        "_live_i_tihosskias_cast"
#define LIVE_I_SYNDYASMOS_TARGETS     "_live_i_syndyasmos_targets"

// Flags
#define FIRE_FLAG 1
#define EARTH_FLAG 2
#define AIR_FLAG 4
#define WATER_FLAG 8
#define SPIRIT_FLAG 16
#define SEEKER_FLAG 32
#define ALL_FLAGS (AIR_FLAG | FIRE_FLAG | EARTH_FLAG | WATER_FLAG)

// CAID values for dynamic spells as outlined in tax doc
#define BASE_VILODA_AID    60.0
#define BASE_ASPIDA_AID    31.0
#define BASE_THALAMOS_AID  15.0
#define BASE_KATO_AID      31.0

#define WATER_ALEIPSO_AID  60.0
#define SPIRIT_ALEIPSO_AID 60.0
#define EARTH_ALEIPSO_AID  30.0
#define AIR_ALEIPSO_AID    30.0
#define FIRE_ALEIPSO_AID   20.0
#define CHILD_ALEIPSO_AID  20.0

#define ELEFRINISI_AID    5.0
#define SCHIRMO_AID      25.0
#define UNTERISTI_AID    10.0
#define DYNAMI_AID       15.0
#define EVIMERO_AID      20.0
#define APOFEVGO_AID     31.0
#define PERIKA_AID       40.0
#define AFOPLIZO_AID     30.0
#define REDUCED_BASE_AID  5.0

// Minimum Guild Stat to Learn Spell for Worshippers
#define SPELL_MINIMUM_GSTAT_ANEMOS              1
#define SPELL_MINIMUM_GSTAT_APODOSI             1
#define SPELL_MINIMUM_GSTAT_CHOMA               20
#define SPELL_MINIMUM_GSTAT_ELEFRINISI          1
#define SPELL_MINIMUM_GSTAT_PYROFOSTI           1
#define SPELL_MINIMUM_GSTAT_SCHIRMO             40
#define SPELL_MINIMUM_GSTAT_UNTERISTI           75
#define SPELL_MINIMUM_GSTAT_ALEIPSO             25
#define SPELL_MINIMUM_GSTAT_FLOGA               50
#define SPELL_MINIMUM_GSTAT_EVIMERO             75
#define SPELL_MINIMUM_GSTAT_DYNAMI              100

// Minimum Guild Stat to Learn Spell for Clerics
// Child Spells
#define SPELL_MINIMUM_GSTAT_CLERIC_ANEMOS         1
#define SPELL_MINIMUM_GSTAT_CLERIC_APODOSI        1
#define SPELL_MINIMUM_GSTAT_CLERIC_ENISCHYO       1
#define SPELL_MINIMUM_GSTAT_CLERIC_ELEFRINISI     1
#define SPELL_MINIMUM_GSTAT_CLERIC_PYROFOSTI      1
#define SPELL_MINIMUM_GSTAT_CLERIC_CHOMA          1
#define SPELL_MINIMUM_GSTAT_CLERIC_AITHERAS       1
#define SPELL_MINIMUM_GSTAT_CLERIC_SCHIRMO        1
#define SPELL_MINIMUM_GSTAT_CLERIC_UNTERISTI      1
#define SPELL_MINIMUM_GSTAT_CLERIC_ALEIPSO        1
#define SPELL_MINIMUM_GSTAT_CLERIC_DYNAMI         1
#define SPELL_MINIMUM_GSTAT_CLERIC_EVIMERO        1
#define SPELL_MINIMUM_GSTAT_CLERIC_THAFLOGA       1
#define SPELL_MINIMUM_GSTAT_CLERIC_MAGIKOS        20

// Master Spells
#define SPELL_MINIMUM_GSTAT_CLERIC_ENKAV          41
#define SPELL_MINIMUM_GSTAT_CLERIC_ASTRAPI        41
#define SPELL_MINIMUM_GSTAT_CLERIC_KRYO           41
#define SPELL_MINIMUM_GSTAT_CLERIC_OXY            41
#define SPELL_MINIMUM_GSTAT_CLERIC_OUSIA          41
#define SPELL_MINIMUM_GSTAT_CLERIC_ANAGNORIZO     50
#define SPELL_MINIMUM_GSTAT_CLERIC_SKIAMORFI      50
#define SPELL_MINIMUM_GSTAT_CLERIC_ZALISMA        50
#define SPELL_MINIMUM_GSTAT_CLERIC_VILODA         60
#define SPELL_MINIMUM_GSTAT_CLERIC_KAFSI          60
#define SPELL_MINIMUM_GSTAT_CLERIC_RIPI           60
#define SPELL_MINIMUM_GSTAT_CLERIC_KRYSTALLOS     60
#define SPELL_MINIMUM_GSTAT_CLERIC_ONKOLITHOS     60
#define SPELL_MINIMUM_GSTAT_CLERIC_DIOCHETEVO     60
#define SPELL_MINIMUM_GSTAT_CLERIC_ANAVO          60
#define SPELL_MINIMUM_GSTAT_CLERIC_ILITHIOS       60
#define SPELL_MINIMUM_GSTAT_CLERIC_AFOPLIZO       60
#define SPELL_MINIMUM_GSTAT_CLERIC_DILITIRIO      60
#define SPELL_MINIMUM_GSTAT_CLERIC_LIVRA          60
#define SPELL_MINIMUM_GSTAT_CLERIC_TIHOSSKIAS     60
#define SPELL_MINIMUM_GSTAT_CLERIC_TYFLOS         65
#define SPELL_MINIMUM_GSTAT_CLERIC_PERIKA         65
#define SPELL_MINIMUM_GSTAT_CLERIC_TROMAZO        70
#define SPELL_MINIMUM_GSTAT_CLERIC_PARADIDO       70
#define SPELL_MINIMUM_GSTAT_CLERIC_KINISI         70
#define SPELL_MINIMUM_GSTAT_CLERIC_DIAKOPI        70
#define SPELL_MINIMUM_GSTAT_CLERIC_THESI          70
#define SPELL_MINIMUM_GSTAT_CLERIC_TEICHOS        80
#define SPELL_MINIMUM_GSTAT_CLERIC_APOFEVGO       80
#define SPELL_MINIMUM_GSTAT_CLERIC_PANO           80
#define SPELL_MINIMUM_GSTAT_CLERIC_ASPIDA         80
#define SPELL_MINIMUM_GSTAT_CLERIC_KATO           80
#define SPELL_MINIMUM_GSTAT_CLERIC_THALAMOS       80
#define SPELL_MINIMUM_GSTAT_CLERIC_SAFI           85

// Guru Spells
#define SPELL_MINIMUM_GSTAT_CLERIC_GIATREOU       60
#define SPELL_MINIMUM_GSTAT_CLERIC_FRAGMOS        90
#define SPELL_MINIMUM_GSTAT_CLERIC_SEIRA          90
#define SPELL_MINIMUM_GSTAT_CLERIC_METAFORA       90
#define SPELL_MINIMUM_GSTAT_CLERIC_TREXIMO        90
#define SPELL_MINIMUM_GSTAT_CLERIC_DIASOSI        90
#define SPELL_MINIMUM_GSTAT_CLERIC_AORATO         90
#define SPELL_MINIMUM_GSTAT_CLERIC_PANIKOS        90
#define SPELL_MINIMUM_GSTAT_CLERIC_TREFO          90
#define SPELL_MINIMUM_GSTAT_CLERIC_ANTISTASI      90
#define SPELL_MINIMUM_GSTAT_CLERIC_KOURASI        90
#define SPELL_MINIMUM_GSTAT_CLERIC_VEKPOS         90
#define SPELL_MINIMUM_GSTAT_CLERIC_SIOPI          90

// Master Guru Spells
#define SPELL_MINIMUM_GSTAT_CLERIC_SYNDYASMOS    100

#ifndef TP
#define TP  this_player()
#endif
#ifndef HE
#define HE   TP->query_pronoun()
#endif
#ifndef HIS
#define HIS  TP->query_possessive()
#endif
#ifndef HIM
#define HIM  TP->query_objective()
#endif
