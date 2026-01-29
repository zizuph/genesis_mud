/*
 * Definitions for the domain Gondor.
 *
 * The definitions are finally neat and clean. Please keep them clean, for
 * instance by using the proper spacing. /Mercade
 */
 
#ifndef GONDORIAN_DEFINITIONS
#define GONDORIAN_DEFINITIONS
 
/* To guard against redefinitions, do not add definitions before this line.
 */

#include <std.h>   /* required for SECURITY definition. */

/*
 * Definitions to disable code under development.
 * GONDORMUD will be 1 on GondorMud, 0 on Genesis.
 * Use it to test code on GondorMud.
 */
#define GONDORMUD       (query_host_name() == "opalr1")
#define PELARGIR_OPEN   1

/* Directories.
 */
 
#define GONDOR_DIR       "/d/Gondor/"
 
#define COMMON_DIR       (GONDOR_DIR + "common/")

#define ARM_DIR          (COMMON_DIR + "arm/")
#define DUNEDAIN_DIR     (COMMON_DIR + "dunedain/")
#define DWARF_DIR        (COMMON_DIR + "dwarf_guild/")
#define MAGES_DIR        (COMMON_DIR + "guild2/")
#define HERB_DIR         (COMMON_DIR + "herbs/")
#define FOOD_DIR         (COMMON_DIR + "food/")
#define LIB_DIR          (COMMON_DIR + "lib/")
#define LIBRARY_DIR      (COMMON_DIR + "library/")
#define NPC_DIR          (COMMON_DIR + "npc/")
#define OBJ_DIR          (COMMON_DIR + "obj/")
#define POISON_DIR       (COMMON_DIR + "poison/")
#define POTION_DIR       (COMMON_DIR + "potions/")
#define RIDERS_DIR       (COMMON_DIR + "riders/")
#define SHIP_DIR         (COMMON_DIR + "ship/")
#define WEP_DIR          (COMMON_DIR + "wep/")
 
#define STD_DIR          GONDOR_DIR + "std/"
#define BOAT_DIR         STD_DIR + "boat/"
#define STEED_DIR        STD_DIR + "steed/"

#define SHIRE_DIR        "/d/Shire/common/"
#define SHIRE_HERB_DIR   (SHIRE_DIR + "herbs/")

#define KRYNN_DIR        "/d/Krynn/common/"
#define KRYNN_HERB_DIR   (KRYNN_DIR + "herbs/")


#define EARTHSEA_DIR        "/d/Earthsea/"
#define EARTHSEA_HERB_DIR   (EARTHSEA_DIR + "herbs/herb_files/")

#define AVENIR_DIR          "/d/Avenir/"
#define AVENIR_HERB_DIR     (AVENIR_DIR + "common/herbs/")

#define RHO_DIR          "/d/Rhovanion/"
#define MORDOR_DOM       "/d/Gondor/"
#define RQ_DIR           (MORDOR_DOM + "ringquest/")
 
#define ANDUIN_DIR       (GONDOR_DIR + "anduin/")
 
#define ANO_DIR          (GONDOR_DIR + "anorien/")
#define DRUEDAIN_DIR     (ANO_DIR + "druedain/")
#define AMON_DIR         (DRUEDAIN_DIR + "amon-din/")
#define NIMRAIS_DIR      (ANO_DIR + "nimrais/")
#define OSG_DIR          (ANO_DIR + "osgiliath/")
#define PEL_DIR          (ANO_DIR + "pelennor/")

#define ARNOR_DIR        (GONDOR_DIR + "arnor/")
#define FORNOST_DIR      (ARNOR_DIR + "fornost/")
#define NORTH_DOWNS_DIR  (ARNOR_DIR + "north_downs/")
 
#define BAY_DIR          (GONDOR_DIR + "bay/")

#define CARD_DIR         (GONDOR_DIR + "cardolan/")

#define CLUBS_DIR        (GONDOR_DIR + "clubs/")
#define STORYT_DIR       (CLUBS_DIR + "storyteller/")

#define DUN_DIR          (GONDOR_DIR + "dunland/")

#define GONDOR_GUILDS_DIR (GONDOR_DIR + "guilds/")
#define MILITIA_DIR       (GONDOR_GUILDS_DIR + "militia/")

#define GWATHLO_DIR      (GONDOR_DIR + "gwathlo/")

#define HAR_DIR          (GONDOR_DIR + "harondor/")
#define HAR_OBJ_DIR      (HAR_DIR + "obj/")       
#define HAR_WEP_DIR      (HAR_OBJ_DIR + "wep/")
#define HAR_ARM_DIR      (HAR_OBJ_DIR + "arm/")
#define HAR_NPC_DIR      (HAR_DIR + "npc/")
#define SCRUB_DIR        (HAR_DIR + "rooms/scrubland/")

#define ITH_DIR          (GONDOR_DIR + "ithilien/")
#define EMYN_ARNEN_DIR   (ITH_DIR + "emyn-arnen/")
#define POROS_DIR        (ITH_DIR + "poros/")

#define LEB_DIR          (GONDOR_DIR + "lebennin/")
#define THORN_DIR        (LEB_DIR + "thornlin/")
#define SIRITH_DIR       (LEB_DIR + "sirith/")

#define MINAS_DIR        (GONDOR_DIR + "minas/")
#define WT_DIR           (MINAS_DIR + "citadel/tower/")
#define SHADES_DIR       (MINAS_DIR + "shades/")
#define HOH_DIR          (MINAS_DIR + "houses/healing/")

#define MORDOR_DIR       (GONDOR_DIR + "mordor/")
#define UNGOL_DIR        (MORDOR_DIR + "ungol/")
#define CIRITH_DIR       (UNGOL_DIR + "tower/")
#define LAIR_DIR         (UNGOL_DIR + "lair/")
#define STAIRS_DIR       (UNGOL_DIR + "stairs/")
 
#define MORGUL_DIR       (GONDOR_DIR + "morgul/")
#define BSW_QUEST_DIR    (MORGUL_DIR + "quest/bsw/")

#define PELAR_DIR        (GONDOR_DIR + "pelargir/")

#define ROH_DIR          (GONDOR_DIR + "rohan/")
#define EDORAS_DIR       (ROH_DIR + "edoras/")
#define ENTWASH_DIR      (ROH_DIR + "entwash/")
#define FARM_DIR         (ROH_DIR + "farm/")
#define ISEN_DIR         (ROH_DIR + "isengard/")
#define ISEN_BOWL        (ISEN_DIR + "isen_rooms/")
#define ISEN_DUNG        (ISEN_DIR + "dungeons/")
#define ORTHANC_DIR      (ISEN_DIR + "orthanc/")
#define ORTHANC_LVL1     (ORTHANC_DIR + "1/")
#define ORTHANC_LVL2     (ORTHANC_DIR + "2/")
#define ORTHANC_LVLG     (ORTHANC_DIR + "g/")

#define THARBAD_DIR      (GONDOR_DIR + "tharbad/")

//Toggle switch for Ranger recode, June 2004
/* 
#define NEW_RANGERS_OPEN 1
*/
#ifndef RANGERS_DIR
#define RANGERS_DIR      (GONDOR_GUILDS_DIR + "rangers/")
#endif

//for old guild path references
#ifndef NEW_RANGERS_OPEN
#define RANGER_DIR       (COMMON_DIR + "guild/")
#define RANGER_GON_DIR   (RANGER_DIR + "gondor/")
#define RANGER_ITH_DIR   (RANGER_DIR + "ithilien/")
#define RANGER_NORTH_DIR (RANGER_DIR + "north/")
#define RANGER_HELP_DIR  (RANGER_DIR + "txt/")
#define RANGER_NORTH_HELP_DIR (RANGER_NORTH_DIR + "help/")
#define BOARD_DIR        (RANGER_DIR + "boards/")
#define SOUL_FILE        (RANGER_DIR + "ranger_soul")
#define NRANGER_SOUL     (RANGER_NORTH_DIR + "ranger_soul")
#define RANGER_GUILD     (RANGER_DIR + "recruithall")
#define R_COUNCIL        (RANGER_DIR + "council")
#define R_OUTLAW         (RANGER_DIR + "outlaw")
#define R_SPONSORS       (RANGER_DIR + "sponsors")
#endif

#ifdef NEW_RANGERS_OPEN
#define RANGER_DIR       RANGERS_DIR
#define SOUL_FILE        (RANGERS_DIR + "soul/rangers_soul")
#define R_OUTLAW         (RANGERS_DIR + "manager/manager")
#define R_SPONSORS       (RANGERS_DIR + "manager/manager")
#endif

#define LOG_DIR          (GONDOR_DIR + "log/")
#define QUEST_LOG        (LOG_DIR + "quest")
#define REWARD_LOG       (LOG_DIR + "rewards")
#define RANGER_LOG       (LOG_DIR + "guild")
/*#define MORGUL_LOG       (LOG_DIR + "morgul")*/
#define MORGUL_LOG       (MAGES_DIR + "log/morgul")
/*#define NAZGUL_LOG       (LOG_DIR + "nazgul")*/
#define NAZGUL_LOG       (MAGES_DIR + "log/nazgul")
 
#define OPEN_DIR         (GONDOR_DIR + "open/")
#define PROJECT_DIR      (OPEN_DIR + "project/")

#define GONDOR_MASTER    (GONDOR_DIR + "workroom") 
#define CLOCK            (OBJ_DIR + "clock")

#define TERRAIN_TYPES    "/d/Gondor/sys/terrain_types.h"

#define TELL_FUNCS       (LIB_DIR + "tell_funcs")
#define ISEN_MASTER      (ISEN_DIR + "master")
#define ME_WEATHER       (COMMON_DIR + "lib/weather_master")
#define HERB_MASTER      (HERB_DIR + "herb_master")
#define RING_QUEST_MASTER    (GONDOR_DIR + "ringquest/rq_master")

#define M_TIRITH_MASTER     (MINAS_DIR + "rooms/adoffice")
#define M_TIRITH_PW_MASTER  (MINAS_DIR + "lib/pw_master")

#define EDORAS_MASTER           (EDORAS_DIR + "rooms/boffice2")
#define ROHAN_FRIEND_FOE        (ROH_DIR + "friend_foe")
#define VOID             (COMMON_DIR + "void") 
#define DEFS_FILE        (GONDOR_DIR + "defs")
#define GONDOR_FOLLOW_SHADOW    (COMMON_DIR + "lib/follow_shadow")
#define CHESS_GAME       ("/d/Gondor/common/obj/chess")
#define STEED_OBJECT     STEED_DIR + "steed"

/*
 * Definitions for the Ring Quest:
 */
#define RINGQ_DIR        RQ_DIR
#define RQ_MASTER        (RINGQ_DIR + "rq_master")

/* 
 * Macros:
 */
#define TP               this_player()
#define TI               this_interactive()
#define TO               this_object()
#define TPQN             this_player()->query_name()
#define TPQRN            this_player()->query_real_name()
#define QVB              query_verb()
#define BS(x)            break_string((x), 75)
#define BSN(x)           (BS(x) + "\n")
#define NF(x)            notify_fail(x)
#define NF0(x)           { NF(x); return 0; }
#define NFN(x)           NF(BSN(x))
#define NFN0(x)          { NFN(x); return 0; }
#define ENV              environment
#define CAP(x)           capitalize(x)
#define LOW(x)           lower_case(x)
#define WRITE(x)         write(BSN(x))

#define POSSESSIVE(x)    ((x)->query_possessive())
#define OBJECTIVE(x)     ((x)->query_objective())
#define PRONOUN(x)       ((x)->query_pronoun())
 
#define SET_MAX_HP       set_hp(query_max_hp());
#define SET_MAX_MANA     set_mana(query_max_mana());
#define SET_MAX_FATIGUE  set_fatigue(query_max_fatigue());
#define REFRESH          refresh_mobile();
 
#define QRACE(x)         ((x)->query_race())
#define QRACENAME(x)     ((x)->query_race_name())
 
#define ONE_OF_LIST(array) one_of_list(array)
#define ONE_OF_LIST_WITH_SEED(array, seed) one_of_list((array), (seed))

/* return v if v is an array; otherwise return array containing v.
 * v must be of type mixed.
 */
#define ARRAY(v)         (pointerp(v) ? (v) : ({ (v) }))

/* this does the same thing as the exclude_array() efun, in 1/3 the time */
#define EXCLUDE_ARRAY(a, i, j) \
  ((j) ? ((i) ? (a[..((i)-1)]+a[((j)+1)..]) : a[((j)+1)..]) : a[1..])

/* return number within specified range */
#define CHECK_RANGE(x, min, max) \
    ((x) <= (min) ? (min) : ((x) >= (max) ? (max) : (x)))

/* check if ob can see in specified room */
#define CAN_SEE_IN_OTHER_ROOM(ob, room) \
    ((room)->query_prop(OBJ_I_LIGHT) > -((ob)->query_prop(LIVE_I_SEE_DARK)))

#ifndef NEW_RANGERS_OPEN 
#define RANGER_S_GUILD_NAME "Gondorian Rangers Guild"
#define RANGER_N_GUILD_NAME "Rangers of the North"
#endif

#ifdef NEW_RANGERS_OPEN
#define RANGER_S_GUILD_NAME "Rangers of the Westlands"
//obsolete definition:
#define RANGER_N_GUILD_NAME "Rangers of the Westlands"
#endif

#define MILITIA_S_GUILD_NAME "Thornlin Militia"
#define MORGUL_S_GUILD_NAME "Morgul Mages"
#define VAMPYR_S_GUILD_NAME "Vampyr guild"
#define DUNEDAIN_S_GUILD_NAME "Dunedain"
#define ROCKFRIEND_S_GUILD_NAME "Rockfriend guild"
#define SINDAR_S_GUILD_NAME     "Sindar of Lorien"
#define MORDOR_ARMY_S_GUILD_NAME "Army of Mordor"
 
#define IS_GONDOR_WIZARD(x) (SECURITY->query_wiz_dom((x)->query_real_name()) \
                             == "Gondor")
#define IS_SHIRE_WIZARD(x) (SECURITY->query_wiz_dom((x)->query_real_name()) \
                             == "Shire")

#define IS_RANGER(x)      ((x)->query_guild_name_occ() == RANGER_S_GUILD_NAME)
#define IS_NRANGER(x)   ((x)->query_guild_name_occ() == RANGER_N_GUILD_NAME)
#define IS_CAPTAIN(x)     ((x)->test_bit("Gondor", 1, 19))
 
#define IS_MORGUL_MAGE(x) ((x)->query_guild_name_occ() == MORGUL_S_GUILD_NAME)
#define IS_MILITIA(x)   ((x)->query_guild_name_occ() == \
                         MILITIA_S_GUILD_NAME || (x)->query_guild_name_lay() \
                         == MILITIA_S_GUILD_NAME) 
#define IS_MORDOR_ARMY(x)      ((x)->query_guild_name_occ() == \
                         MORDOR_ARMY_S_GUILD_NAME || (x)->query_guild_name_lay() \
                         == MORDOR_ARMY_S_GUILD_NAME)
#define IS_DUNADAN(x)   ((x)->query_guild_name_race() == DUNEDAIN_S_GUILD_NAME)
#define IS_SINDAR(x)    ((x)->query_guild_name_race() == SINDAR_S_GUILD_NAME)
#define IS_VAMPYR(x)      ((x)->query_guild_name_occ() == VAMPYR_S_GUILD_NAME)
 
#define IS_IN_ME(x)     ((environment(x))->query_domain() == "Gondor" || \
                         (environment(x))->query_domain() == "Shire")
#define IS_IN_SHIRE(x)  ((environment(x))->query_domain() == "Shire")
#define IS_IN_GONDOR(x) ((environment(x))->query_domain() == "Gondor")

#define MIN_EVIL_ALIGN   (-250)
#define IS_EVIL(x)       ((QRACE(x) == "goblin") || \
              ((x)->query_alignment() < MIN_EVIL_ALIGN))
#define MIN_GOOD_ALIGN   250
#define IS_GOOD(x)       ((!(QRACE(x) == "goblin")) && \
              ((x)->query_alignment() > MIN_GOOD_ALIGN))
 
#define FIX_EUID         { setuid(); seteuid(getuid()); }
#define UNIQUE_CLONE(file, num, alt) \
        "/d/Gondor/std/clones"->unique_clone(file, num, alt)

/*
 * area type definitions used in /d/Gondor/common/lib/area_room.c:
 */
#define AREATYPE_NONE            0
#define AREATYPE_GRASS           1
#define AREATYPE_BUSHES          2
#define AREATYPE_TREES           3
#define AREATYPE_FARMLAND        4
#define AREATYPE_ROCKY           5
#define AREATYPE_SNOW            6
#define AREATYPE_FOREST          7
#define AREATYPE_ROAD            8
#define AREATYPE_BARREN          9
#define AREATYPE_RUINS          10
#define AREATYPE_MARSH          11
#define AREATYPE_HILLS          12
 
/*
 * LOG_QUEST
 *
 * This define should be used to log something in the quest-log. The
 * quest log should never be written to directly. The following
 * parameters should always be added:
 *
 * p - objectpointer to the player solving the quest
 * x - experience gained
 * n - name of the quest (max 25 characters)
 */
#define LOG_QUEST(p, x, n)  DEFS_FILE->log_quest(p, x, n);
#define START_QUEST(p, q) DEFS_FILE->start_quest(p, q);
 

/*  Gondor skills
 *
 * please add any domain skills here, not in individual header files.
 * that will make it much easier to keep track of which numbers have
 * been used.
 */

/* The special ranger skills.
 */
#define OLD_BRAWLING             81200
#define OLD_HEARING              81209
#define SS_BRAWLING             118200
#define SS_MASTER_TASK          118205
#define SS_HEARING              118209
/* Skill-numbers used for ranger punishment/reward handling */
#define OLD_REWARDED             81211
#define OLD_PUNISHED             81210
#define SS_PUNISHED             118210
#define SS_REWARDED             118211
#define SS_PUNISHMENT           118212
#define SS_NRANGER_RANK         118213
#ifndef SS_RANGER_SPELL_LIST
#define SS_RANGER_SPELL_LIST    118214
#endif
#ifndef SS_RANGER_DISFAVOUR
#define SS_RANGER_DISFAVOUR     118215
#endif
 
/* reserved for Dunedain: 118010 .. 118019
 */
#define SS_DUNEDAIN_LEVEL       118011

/* reserved for Sindar: 118020 .. 118029
 */
#define    SS_SINDAR_LEVEL      118020
#define    SS_MEDITATE          118021
/* The special mage skills
 */
#define SS_MORGUL_PENALTY       118001
#define SS_MORGUL_SKILL1        118002

/* Special Militia Skills */
#define SS_MILITIA              118300
#define SS_MILITIA_IMPALE       118301
#define SS_MILITIA_RACK         118302

/* Special Army Skills */
#define SS_MORDOR_TACTICS       118400
#define SS_MORDOR_SMASH         118401
#define SS_MORDOR_RACK          118402

/* Other skill-numbers used.
 */
#define SS_AFFECTED_BY_RING     118101
#define SS_BOAT_HANDL           118102
#define SS_PROTECT_TEAM_MEMBER  118103

/* XXX some code is using SS_BOATING -- define both until can
 * get it all updated
 */
#define SS_BOATING              SS_BOAT_HANDL

/*  end Gondor skills*/


/* Restoral item definitions */
#define SCABBARD_ID             "Gondor_Golden_Scabbard"
#define SCABBARD_RESTORE        (EMYN_ARNEN_DIR + "obj/scabbard_master.c")
#define MILITIA_BOOTS_ID        "Militia_Boots_ID"

/* Easy met/nonmet descriptions.
 */
 
#include "/d/Gondor/met_defs.h"
 
/* Properties.
 */
 
#define ROOM_I_NO_ME_SUN         "_room_i_no_me_sun"
#define BEACH                    add_prop(ROOM_I_TYPE, ROOM_BEACH);
#define GONDOR_M_LOG_RANGER_KILL "_gondor_m_log_ranger_kill"
#define LOG_RANGER_KILL          add_prop(GONDOR_M_LOG_RANGER_KILL, 1);
#define LORIEN_S_ELFFRIEND      "_lorien_s_elffriend"
/* LIVE_I_DONT_CLING used to prevent morgul monsters from following victims */
#define LIVE_I_DONT_CLING "_live_i_dont_follow"
#define LIVE_I_RANGER_NO_BRAWL  "_ranger_i_not_brawl"
#define LIVE_M_RANGER_NO_BRAWL  "_ranger_i_not_brawl"
#define ROOM_M_NO_FIREWOOD       "_room_m_no_firewood"
 
#define GONDOR_M_ROHIRRIM_NO_SELL "_Gondor_m_rohirrim_no_sell"
#define GONDOR_M_MORGUL_NO_SELL "_Gondor_m_morgul_no_sell"
#define GONDOR_M_TIRITH_NO_SELL "_Gondor_m_tirith_no_sell"
#define GONDOR_M_RANGERS_NO_SELL "_Gondor_m_rangers_no_sell"

#define LIVE_I_KILLED_ROHIRRIM   "_live_i_killed_rohirrim"

/* Example for use of the prop. This example outdated by more
 * comprehensive check for Captains.
#define LOG_RANGER_KILL_CAPTAIN  add_prop(GONDOR_M_LOG_RANGER_KILL, "Captain");
 */


/* max ac of armour purchased in shop */
#define MAX_BOUGHT_AC  35


/*
 * verbs that are allowed in all gondor post offices.
 * this includes the list-active-members commands for all gondor guilds.
 */
#define ALLOWED_PO_VERBS \
    ({ "hire", "time", "magelist", "mlist", "rlist", "list",  \
       "dlist", "dunedain", "who",  })
 
/* To guard against redefinition, put all defs above this line.
 */
#endif GONDORIAN_DEFINITIONS
