/*
 * Defs file for NMG
 * Finwe, January 2006
 */

#include "../../sys/defs.h"

// Root Dir
#define NMG_DIR             "/d/Sparkle/guilds/arcane/"
#define FAERIE_DIR          "/d/Sparkle/area/faerie/"

// Misc Dirs
#define CAVE_DIR            (NMG_DIR + "rooms/")
#define LIB_DIR             (NMG_DIR + "lib/")
#define LOG_DIR             (NMG_DIR + "log/")
#define OBJ_DIR             (NMG_DIR + "obj/")
#define SPELLS_DIR          (NMG_DIR + "spells/")
#define PRI_BOARD           (NMG_DIR + "board_priv")
#define PUB_BOARD           (NMG_DIR + "board_pub")
#define FRUIT_DIR           (NMG_DIR + "fruit/")
#define NPC_DIR             (NMG_DIR + "npcs/")

// Base files
#define INDOOR_ROOM         (LIB_DIR + "base_indoors.c")
#define DR_RACKS            (LIB_DIR + "base_racks.c")
#define COMMON_BASE         (FAERIE_DIR + "lib/base_common.c")
#define HERB_SEARCH         (FAERIE_DIR + "lib/herbsearch.c")

#define ORCHARD_BASE        (LIB_DIR + "base_orchard.c")

// Guild definitions
#define GUILD_TAX           12
#define GUILD_NAME          "Seeker of the Arcane Arts"
#define GUILD_NAME_SHORT    "Seeker"
#define GUILD_STYLE         "magic"
#define GUILD_TYPE          "layman"
#define GUILD_TITLE_GRAD    "Master"
#define GUILD_STAT_MAX      86      
#define GUILD_TITLES        \
    ({  "Fresh", "Hopeful", "Aspiring", "Capable", "Skilled", "Practiced", \
        "Experienced", "Talented", "Accomplished", "Dedicated",  GUILD_TITLE_GRAD })
#define GUILD_SPELL_LVLS    \
    ({  "New", "Partial", "Halfway", "Close", "Mastered" })
#define GUILD_TRAINER       (NPC_DIR + "train")
#define GUILD_SHADOW        (NMG_DIR + "seeker_shadow")
#define GUILD_SOUL          (NMG_DIR + "seeker_soul")
#define GUILD_OBJ           (OBJ_DIR + "pendant")
#define GUILD_SPELLS        (OBJ_DIR + "prayerbook")
#define GUILD_LOG           "/d/Sparkle/log/arcane"
#define GUILD_LOGS          (LOG_DIR)
#define GUILD_SAVE          (LOG_DIR + "arcane_save")
#define GUILD_MASTER        ({"finwe"})
#define IS_MEMBER(p)        ((p)->query_guild_name_lay() == GUILD_NAME)
#define PENDANT_SUBLOC      "_seeker_pendant_"
#define LOG_SIZE            25000
#define START               (CAVE_DIR + "start")

//#define MEMBER_TRACKER      "/d/Shire/herald/tracker.c"
#define MEMBER_SAVE         (NMG_DIR + "members")
#define GUILD_HELP          (NMG_DIR + "help/")
#define GUILD_NEWS          (GUILD_HELP + "news")


// Other general defines
#define PO                  previous_object()
#define QSW                 query_shadow_who()
#define HE_SHE(o)           (o)->query_pronoun()
#define HIS_HER(o)          (o)->query_possessive()
#define HIM_HER(o)          (o)->query_objective()
#define QRACE(o)            (o)->query_race_name()
#define QTRACE(o)           (o)->query_race()
#define ENV(o)              environment(o)
#define E(o)                environment(o)
#define WRITE(s)            TP->catch_msg(s) 
#define WRITEN(s)           TP->catch_msg(s + "\n")
#define CAP(s)              capitalize(s)
#define LOW(s)              lower_case(s)
#define NF(s)               notify_fail(s)
#define NFN(s)              notify_fail(s + "\n")
#define NFN0(x)             { NFN(x); return 0; }

// fruits for spells: apple, apricot, fig, lemon, lime, peach, pear 
#define FRUIT    ({ "apple", "apricot", "fig", "gooseberry", "grapefruit", \
    "kumquat", "lemon", "lime", "mango", "orange", "peach", "pear", "starfruit", })                   
#define MAX_FRUIT     5         /* maximum num of fruits in each room */

