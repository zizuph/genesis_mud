/*
 * local.h - For the Wayreth forest and Wizard of High Sorcery.
 *
 * 950510 by Rastlin
 */

#ifndef WAYRETH_DEF
#define WAYRETH_DEF

#include <files.h>
#include "/d/Krynn/common/defs.h"

#define HAVEN                       "/d/Krynn/haven/"
#define WAYRETH                     "/d/Krynn/wayreth/"
#define WSTD                        WAYRETH + "std/"
#define WNPC                        WAYRETH + "npc/"
#define WOBJ                        WAYRETH + "obj/"
#define WTOWER                      WAYRETH + "tower/"
#define TOBJ                        WTOWER + "obj/"
#define WFOREST                     WAYRETH + "forest/"
#define WGUILD                      WAYRETH + "guild/"
#define WLOG                        WAYRETH + "log/"
#define WMAGIC                      WAYRETH + "magic/"
#define WDOC                        WAYRETH + "doc/"

#define HELP_DIR                    WDOC + "help/"
#define WBOOKPAGES                  WDOC + "book/"
#define NORMAL_BOARD                WLOG + "boards/normal"
#define CONCLAVE_BOARD              WLOG + "boards/conclave"
#define POLICY_BOARD                WLOG + "boards/policy"
#define MAGIC_BOARD                 WLOG + "boards/magic"

/* Base files */

#define WAYINROOM         "/d/Krynn/wayreth/std/in_room"
#define WAYOUTROOM        "/d/Krynn/wayreth/std/out_room"
#define FORESTROOM        "/d/Krynn/wayreth/std/forest_base"
#define TOWERROOM         "/d/Krynn/wayreth/std/tower_base"
#define WORKROOM          "/d/Krynn/wayreth/std/workroom"

#define SPELLCASTING      "/d/Krynn/wayreth/std/spellcasting"
#define NORMAL_SKILLS     WTOWER + "norm_skills"
#define MAGE_SKILLS       WTOWER + "mage_skills"
#define START_ROOM        WTOWER + "magic_void"
#define DEFAULT_START_LOC WTOWER + "study"
#define MORTAR            "/d/Genesis/std/potions/mortar"
#define VIAL              POTION_VIAL_OBJECT
#define GLOVES            KRARMOUR + "herb_gloves"
#define JAR               KROBJECT + "herb_jar"

/* Guild defines */

#define ADMINDIR                    WGUILD + "admin/"
#define GOBJ                        WGUILD + "obj/"
#define TESTROOM		    WTOWER + "testcontrol"

/* Properties */

#define LIVE_I_AM_INVITED "_live_i_am_invited"

/* Some other useful defines */
#define LOG(x, y)       (/*log_file(WLOG + x, ctime(time()) + " " + y + "\n",10000)*/)
#define RNAME(x)        (x->query_real_name())
#define AI              add_item
#define ACI             add_cmd_item
#endif WAYRETH_DEF
