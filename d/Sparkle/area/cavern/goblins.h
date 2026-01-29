/*
 * Written by Quis for the goblin start area 920518
 */
#include "/d/Sparkle/sys/defs.h"

#define GOBLIN_STARTLOC (S_DOMAIN_START_DIR+"goblin/start")
#define GOBLIN_DIR        "/d/Sparkle/area/cavern/"
#define GOBLIN_CAVERN_DIR GOBLIN_DIR + "room/"
#define GOBLIN_OBJ_DIR    GOBLIN_DIR + "obj/"
#define GOBLIN_NPC_DIR    GOBLIN_DIR + "npc/"
#define GOBLIN_GUILD_DIR  GOBLIN_DIR + "guild/"

/*
 * define a standard breakstring macro for the goblin area.
 */

#define BS(s) (break_string((s),70))
#define BSN(s) (break_string((s) + "\n",70))
#define BSNN(s) (break_string((s) + "\n\n",70))
