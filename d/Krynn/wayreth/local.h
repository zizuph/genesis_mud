/*
 * local.h - For the Wayreth forest and Wizard of High Sorcery.
 *
 * 950510 by Rastlin
 */

#ifndef WAYRETH_DEF
#define WAYRETH_DEF

#include "/d/Krynn/common/defs.h"

#define HAVEN                       "/d/Krynn/haven/"
#define WAYRETH                     "/d/Krynn/wayreth/"
#define WOHS                        "/d/Krynn/guilds/wohs/"
#define WSTD                        (WAYRETH + "std/")
#define WNPC                        (WAYRETH + "npc/")
#define WOBJ                        (WAYRETH + "obj/")
#define WFOREST                     (WAYRETH + "forest/")
#define WTOWER                      (WAYRETH + "tower/")
#define TOBJ                        (WTOWER + "obj/")
#define WLOG                        (WAYRETH + "log/")
#define NORMAL_BOARD                WLOG + "boards/normal"
#define CONCLAVE_BOARD              WLOG + "boards/conclave"
#define POLICY_BOARD                WLOG + "boards/policy"
#define MAGIC_BOARD                 WLOG + "boards/magic"
#define GUEST_BOARD                 WLOG + "boards/guest"

/* Base files */
#define WAYINROOM         (WSTD + "in_room")
#define WAYOUTROOM        (WSTD + "out_room")
#define FORESTROOM        (WSTD + "forest_base")
#define WORKROOM          (WSTD + "workroom")
#define TOWERROOM         (WSTD + "tower_base")

/* Some other useful defines */
#define AI              add_item
#define ACI             add_cmd_item
#define RNAME(x)        (x->query_real_name())

#define MORTAR            "/d/Genesis/std/potions/mortar"
#define VIAL              "/d/Genesis/std/potions/vial"
#define GLOVES            KRARMOUR + "herb_gloves"
#define JAR               KROBJECT + "herb_jar"

#endif WAYRETH_DEF
