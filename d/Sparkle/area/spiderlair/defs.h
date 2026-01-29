/*
 *  /d/Sparkle/area/spiderlair/defs.h
 *
 *  This is the mail headerfile for the : spiderlair dungeon.
 *
 *  Created February 2009, by Nerull.
 */



// Change this directory if you move the dungeon to somewhere else.
#define    DUNGEON_DIR      ("/d/Sparkle/area/spiderlair/")

// Misc definitions
#define    TO this_object()
#define    TP this_player()
#define    HE(x)                x->query_pronoun()
#define    HIS(x)               x->query_possessive()

#define    MORTAL_CAN_USE_THIS     "_mortal_can_use_this"
#define    RANGER_M_NOT_DISARM     "_ranger_m_not_disarm"
#define    RANGER_I_NOT_DISARM     "_ranger_i_not_disarm"


// Dir-definitions
#define    DUNGEON_NAME     "spiderlair"
#define    ROOM_DIR         (DUNGEON_DIR + "rooms/")
#define    SUBLEVEL_1       (ROOM_DIR + "sub_1/")
#define    SUBLEVEL_2       (ROOM_DIR + "sub_2/")
#define    SUBLEVEL_3       (ROOM_DIR + "sub_3/")
#define    SUBLEVEL_4       (ROOM_DIR + "sub_4/")
#define    SUBLEVEL_5       (ROOM_DIR + "sub_5/")
#define    LOG_DIR          (DUNGEON_DIR + "log/")
#define    DROPS_DIR        (DUNGEON_DIR + "drops/")
#define    NPC_DIR          (DUNGEON_DIR + "npcs/")
#define    BOSS_DIR         (DUNGEON_DIR + "bosses/")
#define    IMB_SH_DIR       (DUNGEON_DIR + "imbuements/imb_shadows/")

#define 	 P_COMMON          DROPS_DIR + "common/"
#define  	 P_UNCOMMON        DROPS_DIR + "uncommon/"
#define    P_RARE            DROPS_DIR + "rare/"
#define    P_EPIC            DROPS_DIR + "epic/"
#define    P_LEGENDARY       DROPS_DIR + "legendary/"
#define    P_ARTIFACT        DROPS_DIR + "artifact/"
#define    P_TOKEN           DROPS_DIR + "token/"
#define    P_ROOM            DROPS_DIR + "room_items/"


// Dungeon variables
#define    DUNGEONTOKEN_DROPCHANCE  120

#define    COMMON_DROPCHANCE         15
#define    UNCOMMON_DROPCHANCE       50
#define    RARE_DROPCHANCE          100
#define    EPIC_DROPCHANCE          500
#define    LEGENDARY_DROPCHANCE    1000
#define    ARTIFACT_DROPCHANCE     3000

#define    EXP_PERCENTAGE           140
#define    GUARDIAN_HP            30000


//------------------ITEMS POWER PARAMETERS-----------------------

// The resistance parameter for spesific resistance items
#define    MAGIC_SP_RESIST           30

// The resistance parameter for MR resistance items
#define    MR_RESIST                 20



//------------------ITEM IMBUEMENT PROPERTIES--------------------

// The different properties for the effects
#define I_AM_IMBUED0  "i_am_imbued0"
#define I_AM_IMBUED1  "i_am_imbued1"
#define I_AM_IMBUED2  "i_am_imbued2"
#define I_AM_IMBUED3  "i_am_imbued3"



