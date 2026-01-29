/* -*- Mode: C -*-
 * defs.h
 * Standard definitions for Dol Amroth.
 *
 * By Skippern April 2001
 */
#ifndef DOL_AMROTH_BASE
#define DOL_AMROTH_BASE

#include "/d/Gondor/defs.h"
/*
 * Base definitions for the directory tree
 */
#define GEM_DIR             "/d/Genesis/gems/obj/"

#define DOL_BASE            "/d/Gondor/dol_amroth/"

#define DOL_OBJ             (DOL_BASE + "obj/")
#define DOL_TG              (DOL_OBJ  + "TradeGoods/")
#define DOL_LEFTOVER        (DOL_OBJ  + "leftover/")
#define DOL_WEP             (DOL_OBJ  + "wep/")
#define DOL_ARM             (DOL_OBJ  + "arm/")
#define DOL_NPC             (DOL_BASE + "npc/")

#define DOL_HILLS           (DOL_BASE + "hillside/")
#define DOL_TRADE           (DOL_BASE + "trade/")
#define DOL_COMMON          (DOL_BASE + "common/")
#define DOL_CRAFT           (DOL_BASE + "craft/")
#define DOL_OTHER           (DOL_BASE + "other/")
#define DOL_SEWER           (DOL_BASE + "sewer/")

#define DOL_BOARD           (DOL_BASE + "board/")
#define DOL_STD             (DOL_BASE + "std/")
#define DOL_LIB             (DOL_BASE + "lib/")

#define TO_BELFALAS         "/w/skippern/projects_new/dor-en-ernil/road/wr1"

#define FIREMASTER          (DOL_LIB + "fire_master.c")

/*
 * Debugging, switch to 0 before opening
 */
#define DEBUG              1 /* For debug messages, turn to 0 before opening */

/*
 * Properties
 */
#define DOL_I_FOUND_SEWER_DOOR        "_dol_i_found_sewer_door_"
#define I_HAVE_JUST_ASKED_FOR_A_TASK  "_dol_i_have_asked_for_task_"
#define DOL_I_ASKED_WINER             "_dol_i_asked_winer_"
#define DOL_I_WINER_QUEST             "_dol_i_winer_quest_"
#define DOL_S_ASSASSIN_FOE            "_dol_s_assassin_foe_"

/*
 * Experience values for texts in quest-token
 */
#define LITE                    250
#define SOME                    500
#define MUCH                   1000

/*
 * Quests
 */
#define DOL_Q_GROUP             999
#define DOL_FIRST_BIT             1
#define DOL_NO_BITS              20
#define DOL_NO_TASKS              9

#define DOL_Q_M_EXPLORE_TOWN      1
#define DOL_Q_M_MAKE_BED          2
#define DOL_Q_M_UNCOVER_SPY       3
#define DOL_Q_M_CHECK_SEWER       4

#define DOL_Q_M_LAST              9  /* Used in quest token for logging */

#define DOL_Q_MAGE_QUEST         10
#define DOL_Q_JEWELER            11
#define DOL_Q_WINE               12
#define DOL_Q_ALCHEMIST          13
#define DOL_Q_LOST_SHIP          14

#define DOL_Q_TORMIR_CAHRM       15
#define DOL_Q_ASSASSIN           16

#endif
