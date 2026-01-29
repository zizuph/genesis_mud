/* 
 * Xak Tsaroth - Hall of the Ancestors
 * Originaly coded by Percy
 * Revamped by Rastlin
 */
#pragma strict_types

#include "../../local.h"

inherit INROOM;

public void
create_xak_room()
{    
    set_short("Southern crypts");
    set_long("You are standing in a long, narrow corridor that " +
	     "extends to the east. The corridor is lit by " +
	     "torches that flickers and smokes in the stifling air. " +
	     "The light reflects off the walls wet with condensed " +
	     "moisture. To the north the Hall of the " +
	     "Ancestors can be seen. A strange screeching sound seems " +
	     "to come from the other end of the corridor.\n");

    LIGHT;

    add_exit(HALL + "entry", "north");
    add_exit(HALL + "southcrypt2", "east");

    add_item(({"torch", "torches"}), "The torches flickers and smokes. " +
	     "They are attached to the walls, you wonder what they do " +
	     "with them when they are burnt down.\n");
    add_cmd_parse("[the] 'torch' / 'torches'", ({"take", "get"}),
		  "The torches can't be taken.\n");
}









