/*
 * Global defenitions for Path of Erech and Vale of Erech
 * 
 * Made by Skippern
 * February 2000 - January 2001
 */

/* GLOBAL INCLUDES */
#include "/d/Gondor/defs.h"  /* This will be needed in most of the rooms */

/* GLOBALS */
#define E_BASE "/d/Gondor/erech/"  /* The base directory */
#define E_LIB E_BASE + "lib/"
#define E_STD E_BASE + "std/"

/* GEOGRAPHICAL */
#define E_PATH E_BASE + "path/"
#define E_VALE E_BASE + "vale/"
#define E_FIELD E_BASE + "field/"
#define E_FARM E_BASE + "farm/"
#define TO_ROHAN "/w/skippern/ship/plat1.c"
#define TO_AMROTH "/d/Gondor/dol_amroth/other/outside/cross.c"

/* ITEMS */
#define E_OBJ E_BASE + "obj/"

/* NON-PLAYER CHARACTERS */
#define E_NPC E_BASE + "npc/"

/* QUEST */
#define E_QUEST E_BASE + "quest/"

#define ERECH_TASK_GROUP      0
#define ERECH_FIRST_BIT       0
#define ERECH_LAST_BIT        2
#define ERECH_NO_BITS         3

#define ERECH_FARM_GROUP      0
#define ERECH_FARM_BIT        0

#define REWARD_LITTLE         "You feel a little more experienced.\n"
#define REWARD_SOME           "You feel somewhat more experienced.\n"
#define REWARD_MORE           "You feel more experienced.\n"
#define REWARD_MUCH           "You feel much more experienced.\n"
#define REWARD_VMUCH          "You feel very much more experienced.\n"

/* TERRAIN TYPES */
#define TERRAIN_ERECH_TUNNEL (TERRAIN_UNDERGROUND|TERRAIN_NATURAL|TERRAIN_COOL|TERRAIN_HASDEAD|TERRAIN_SHADOWS)
#define TERRAIN_ERECH_VALE (TERRAIN_NATURAL|TERRAIN_OUTSIDE)
#define TERRAIN_ERECH_CAVE (TERRAIN_UNDERGROUND|TERRAIN_NATURAL|TERRAIN_COOL)

/* OTHER */
#define DARK_ROOM_LONG      "A dark room. You get a creepy feeling here.\n"
#define NO_DIS              "You don't dare to enter.\n"
#define PANIC               2
#define ANGRY_CRY           ({ "Die you scum!", "This is your doom!", "Die die die" })
#define STAIN_S_SUBLOC      "_a_stain_from_erech_"

/* PROPERTIES */
#define ERECH_I_PART          "_erech_i_part"
#define ERECH_S_TALE          "_erech_s_tale"
#define ERECH_I_TASK          "_erech_i_task"
#define ERECH_QUEST_ITEM      "_erech_quest_item"
#define I_ATTACKED_A_GHOST    "_i_attacked_a_ghost"

/* PROPERTI VALUES */
#define ERECH_EXP_TASK        100

/* FOR UTMIR */
#define HERBAL_SAVE         E_NPC + "herbalist/herbs"
#define STOCK_ME_UP         0      /* 1 = stock up, 0 = intelligent search */
#define MAX_INV             30
#define H_FILE              0
#define H_COUNT             1
#define H_VALUE             2
#define MAX_XFER            10
#define MAX_XFER_WORD       "ten"

#define LOG_BUG             "utmir.bug"

#define NUM                 sizeof(MONEY_TYPES)


