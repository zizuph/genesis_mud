/*
 *  /d/Gondor/guilds/morgulmage/morgulmage.h
 *
 *  Global definition file for the Society of Morgul Mages.
 *
 *  Created by Eowul, Februari 2009
 */

#ifndef __MORGULMAGE_DEFINITIONS__
#define __MORGULMAGE_DEFINITIONS__

// Directories
#define MORGUL_GUILD_DIR        "/d/Gondor/guilds/morgulmage/"
#define MORGUL_ROOM_DIR         (MORGUL_GUILD_DIR + "rooms/")
#define MORGUL_OBJ_DIR          (MORGUL_GUILD_DIR + "obj/")
#define MORGUL_NPC_DIR          (MORGUL_GUILD_DIR + "npc/")
#define MORGUL_HELP_DIR         (MORGUL_GUILD_DIR + "help/")
#define MORGUL_LIBRARY_DIR      (MORGUL_GUILD_DIR + "library/")
#define MORGUL_SPELL_DIR        (MORGUL_GUILD_DIR + "spells/")
#define MORGUL_SPELL_OBJ_DIR    (MORGUL_SPELL_DIR + "obj/")
#define MORGUL_POTION_DIR       (MORGUL_GUILD_DIR + "potions/")

#define OLD_MORGUL_GUILD_DIR    "/d/Gondor/common/guild2/"

// Specific files
#define MORGUL_DEATH_ROOM       (MORGUL_ROOM_DIR + "death_room")
#define MORGUL_NAZUL_THRONE_ROOM (OLD_MORGUL_GUILD_DIR + "throne_room")
#define MORGUL_MASTER           (MORGUL_GUILD_DIR + "master/master")
#define MORGUL_LOW_TRAINING     (MORGUL_ROOM_DIR + "train_low")
#define MORGUL_HIGH_TRAINING    (MORGUL_ROOM_DIR + "train_high")
#define MORGUL_POST_OFFICE      (MORGUL_ROOM_DIR + "post")
#define MORGUL_COMMAND_SOUL     (MORGUL_GUILD_DIR + "morgul_soul")
#define MORGUL_SHADOW           (MORGUL_GUILD_DIR + "morgul_shadow")
#define MORGUL_LAY_SHADOW       (MORGUL_GUILD_DIR + "morgul_shadow_lay")
#define GLOBAL_UNDEAD_SHADOW    ("/d/Genesis/specials/std/undead_shadow")
#define MORGUL_MASTER_SAVE      (MORGUL_GUILD_DIR + "master/master_save")
#define MORGUL_WINGED_STEED_ROOM (MORGUL_SPELL_OBJ_DIR + "winged_steed_room")

#define MORGUL_WIZARD_NAZGUL_LOG    (OLD_MORGUL_GUILD_DIR + "log/nazgul")
#define MORGUL_NAZGUL_RECORDS   (OLD_MORGUL_GUILD_DIR + "log/nazgul_records")
#define MORGUL_REGULAR_RECORDS  (OLD_MORGUL_GUILD_DIR + "log/morgul")
#define MORGUL_WARDEN_RECORDS   (OLD_MORGUL_GUILD_DIR + "log/complaints")

#define ANGHOTH_MANAGER         ("/d/Gondor/clubs/anghoth/manager")

// Guild shadow defines
#define GUILD_NAME              "Morgul Mages"
#define GUILD_TYPE              "occupational"
#define GUILD_STYLE             "magic"

#define GUILD_TAX_APPRENTICE    23
#define GUILD_TAX_FULL_MAGE     40
#define GUILD_TAX_LAYMAN        0

// Guru quest group and bit for Gondor
#define MORGUL_GURU_GROUP       2
#define MORGUL_GURU_BIT         1

// Level boundaries
#define TUVALE_LEVEL            0
#define APPRENTICE_LEVEL        12
#define LT_LEVEL                24
#define ARCHMAGE_LEVEL          25
#define MAX_NORMAL_LEVELS       24

// Alignment requirements
#define MORGUL_I_ALIGN_JOIN      -250
#define MORGUL_I_ALIGN_WARN         0
#define MORGUL_I_ALIGN_REMOVE     150

// Activity counter
#define ACTIVITY_APPOINT            600
#define ACTIVITY_SACRIFICE         1000
#define ACTIVITY_RAKASUL            800
#define ACTIVITY_TALK                10
#define ACTIVITY_SMALL_SPELL         15
#define ACTIVITY_COMBAT_SPELL        46
#define ACTIVITY_RARE_SPELL         220
#define ACTIVITY_EMOTION             53
#define ACTIVITY_NAZ_LIB_READ        80
#define ACTIVITY_NAZ_LIB_WRITE      300
#define ACTIVITY_NAZ_LIB_CREATE     600
#define ACTIVITY_NAZ_LIB_MOVE       400
#define ACTIVITY_READ_NOTE           50
#define ACTIVITY_REMOVE_NOTE        150
#define ACTIVITY_BOARD_NOTE         200
#define ACTIVITY_PUNISH             300
#define ACTIVITY_REWARD             501
#define ACTIVITY_EXPEL             1001
#define ACTIVITY_RELEGATE          1200
#define ACTIVITY_MINOR               10
#define ACTIVITY_TYPICAL            100
#define ACTIVITY_MAJOR              250
#define ACTIVITY_OTHER_LIB_READ      50
#define ACTIVITY_OTHER_LIB_MOVE     301
#define ACTIVITY_OTHER_LIB_CREATE   501
#define ACTIVITY_PUBLIC_LIB_READ     50
#define ACTIVITY_PUBLIC_LIB_MOVE    301
#define ACTIVITY_PUBLIC_LIB_CREATE  501
#define ACTIVITY_PROMOTE_TO_NAZGUL 1000
#define ACTIVITY_SELL_HERB            5
#define ACTIVITY_SELL_MAGE_HERB      50
#define ACTIVITY_SELL_FOCUS_HERB    100

// Properties used in players or objects
#define MORGUL_S_THRONE_GRANT   "_King_granted_this_Mage_Access"
#define MORGUL_S_SPELL_OBJECT   "Morgul_Spell_Object"
#define MORGUL_S_GUILD_OBJECT   "morgul_guild_object"
#define MORGUL_S_SUBLOC         "Morgul_Mage_SubLoc"
#define MORGUL_MORGUL_CROWN     "Morgul_Morgul_Crown"
#define MORGUL_MORGUL_RING      "Morgul_Morgul_Ring"
#define MORGUL_I_SULAMBAR_RES   "_morgul_i_sulambar_res"
#define MORGUL_M_MAGIC_INGREDIENT    "_Morgul_m_magic_ingredient"
#define MORGUL_I_NARUSSE_ENHANCED   "_morul_i_narusse_enhanced"
#define MORGUL_I_NO_SUMMON_STEED  "_morgul_i_no_summon_steed"
#define MORGUL_M_GOROTHNATHA_DATA "_morgul_m_gorothnatha_data"
#define MORGUL_I_SUPPRESS_AUTOIGNITE "_morgul_i_suppress_autoignite"
 
// ID's used in objects
#define MORGUL_ID_SULAMBAR_POISON   "_Morgul_Sulambar_Poison"
#define MORGUL_ID_DAGGER        "_morgul_dagger"
#define MORGUL_ID_BLADE_WOUND   "_morgul_blade_wound"

// Other defines
#define IS_MEMBER(player)       (player->query_guild_name_occ() == GUILD_NAME)
#define IS_TUVALE(player)       (player->query_morgul_level() <= TUVALE_LEVEL)
#define IS_APPRENTICE(player)   (player->query_morgul_level() <= APPRENTICE_LEVEL)
#define IS_ARCHMAGE(player)     (player->query_morgul_level() == ARCHMAGE_LEVEL)
#define IS_LIEUTENANT(player)   (player->query_morgul_level() == LT_LEVEL)

#define MORGUL_EMISSARIES       ({ "gorboth", "toby", "eowul", "arman" })

#define MORGUL_AS_ILLEGAL_RACE_ON_JOIN ({ \
    "dwarf", "elf", "hobbit", "half-elf", "minotaur", "kender" })
#define MORGUL_AS_ILLEGAL_RACE ({ "dwarf", "hobbit" })

#define ALLOWED_MORGUL_EMOTIONS ({ \
    "mamuse", "mgrab", "msmile", "hail", "mlook", "mordor", \
    "mremember", "withdraw", "aware", "gaze", "hgaze", \
    "marm", "mdismiss", "mhood", "minspect", "mleer", \
    "mnarrow", "msniff", "mturn", "torture", \
    "bnlist", "frown", "point", "smile", "grin", \
    })
    
#include "morgulmage_titles.h"

// Spell defines

// Sulambar limitation values, the regen time is in player age expired
// which means you need to multiply it with 2 to get the time in seconds.
#define MAX_SULAMBAR_CHARGES	10
#define SULAMBAR_REGEN_TIME		5400

// Stat weighting influencing spell effectiveness
#define STAT_WEIGHTING   ({ SKILL_WEIGHT, 60, TS_INT, SKILL_WEIGHT, 20, TS_WIS, SKILL_WEIGHT, 20, TS_DIS })

// Options
#define OPTION_TITLE_INTRO      "title_intro"
#define OPTION_TITLE_NORMAL     "title_normal"
#define OPTION_TITLE_MLIST      "title_mlist"
#define OPTION_NARUSSE_IGNITE   "narusse_ignite"
#define OPTION_NIFARIST         "nifarist"

#define NIFARIST_FULL_MAGES     1
#define NIFARIST_APPRENTICES    2
#define NIFARIST_TEAM           4

#define DEFAULT_OPTIONS ([ \
    OPTION_TITLE_INTRO : 0,\
    OPTION_TITLE_NORMAL : 0,\
    OPTION_TITLE_MLIST : 0,\
    OPTION_NARUSSE_IGNITE : 1, \
    OPTION_NIFARIST : 0 \
])

#define LEFTOVER_KEEP_PERCENTAGE  50

// Assignable positions
#define ASSIGNABLE_POSITIONS    ([ \
    "lieutenant" : "Lieutenant of Morgul", \
    "librarian"  : "Librarian of the Society", \
    "herbalist"  : "Herbalist of the Society", \
    ])
    
#endif