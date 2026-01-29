/* 
 * Xak Tsaroth - Hall of the Ancestors
 * Originaly coded by Percy
 * Revamped by Rastlin
 */
#pragma strict_types

#include "../../local.h"
#include <macros.h>

inherit INROOM;

static object gGully1, gGully2, gBupu;

public void
reset_xak_room()
{
    MOVE(gGully1, NPC + "gully")
    MOVE(gGully2, NPC + "gully")
    MOVE(gBupu, NPC + "bupu")
}

public void
create_xak_room()
{    
    set_short("Southern crypts");
    set_long("You are standing in a long, narrow corridor " +
	     "that extends to the east and west. To the north " +
	     "the Hall of the Ancestors can be seen. Coffins line " +
	     "the walls here and the stench of death assails your " +
	     "nostrils. A strange screeching sound can be heard " +
	     "close by from the east end of the corridor. The corridor " +
	     "is lit by torches that flickers and smokes in the stifling " +
	     "air. The light reflects off the walls wet with condensed " +
	     "moisture.\n");

    LIGHT;

    add_exit(HALL + "southcrypt5", "east");
    add_exit(HALL + "hall1", "north");
    add_exit(HALL + "southcrypt3", "west");

    add_item(({"torch", "torches"}), "The torches flickers and smokes. " +
	     "They are attached to the walls, you wonder what they do " +
	     "with them when they are burnt down.\n");
    add_cmd_parse("[the] 'torch' / 'torches'", ({"take", "get"}),
		  "The torches can't be taken.\n");

    add_item(({"coffin", "normal coffin", "normal coffins", "coffins"}), 
	     "The coffins are made of stone and they all " +
	     "looks very heavy to lift.\n");

    reset_xak_room();
}



