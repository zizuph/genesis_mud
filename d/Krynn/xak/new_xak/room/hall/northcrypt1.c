/* 
 * Xak Tsaroth - Hall of the Ancestors
 * Originaly coded by Percy
 * Revamped by Rastlin
 */
#pragma strict_types

#include "../../local.h"

inherit INROOM;

object gDrac1, gDrac2;

public void
reset_xak_room()
{
    MOVE(gDrac1, GET_NPC_HA)
    MOVE(gDrac2, GET_NPC_HA)
}

public void
create_xak_room()
{    
    set_short("Northern crypts");
    set_long("You are standing in a long, narrow corridor that " +
	     "extends to the east. To the south the Hall of the " +
	     "Ancestors can be seen. The corridor is lit by " +
	     "torches that flickers and smokes in the stifling air. " +
	     "The light reflects off the walls wet with condensed " +
	     "moisture.\n");

    LIGHT;

    add_exit(HALL + "northcrypt2", "east");
    add_exit(HALL + "entry", "south");

    add_item(({"torch", "torches"}), "The torches flickers and smokes. " +
	     "They are attached to the walls, you wonder what they do " +
	     "with them when they are burnt down.\n");
    add_cmd_parse("[the] 'torch' / 'torches'", ({"take", "get"}),
		  "The torches can't be taken.\n");

    reset_xak_room();
}


