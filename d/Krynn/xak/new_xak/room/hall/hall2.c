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
    set_short("In the Hall of the Ancestors");
    set_long("You are standing between two huge holes in the floor from " +
	     "which a white foul-smelling mist boils up. The sound of " +
	     "rushing water can be heard from below. Through the " +
	     "mist you distinguish two big rooms, one to the east " +
	     "and another to the west. The two rooms are lit by a pale " +
	     "grey light.\n");

    LIGHT;

    add_exit(HALL + "hall3", "east");
    add_exit(HALL + "hall1", "west");

    add_item("ceiling", "It looks intact.\n");
    add_item("floor", "The floor has collapsed on several places, revealing " +
	     "deep holes.\n");
    add_item(({"hole", "holes"}), "A sound of rushing water can be heard " +
	     "below.\n");

}








