/*
 * Written by Quis for the goblin start area 920518
 */

#define GOBLIN_DIR        "/d/Genesis/start/goblin/"
#define GOBLIN_CAVERN_DIR GOBLIN_DIR + "caverns/"
#define GOBLIN_OBJ_DIR    GOBLIN_DIR + "obj/"
#define GOBLIN_NPC_DIR    GOBLIN_DIR + "npc/"
#define GOBLIN_GUILD_DIR  GOBLIN_DIR + "guild/"

/*
 * define a standard breakstring macro for the goblin area.
 */

#define BS(s) (break_string((s),70))
#define BSN(s) (break_string((s) + "\n",70))
#define BSNN(s) (break_string((s) + "\n\n",70))
