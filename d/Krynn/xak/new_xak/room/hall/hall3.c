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
    set_short("In the Hall of the Ancestors");
    set_long("This is the third octagonal room that makes the " +
	     "Hall of the Ancestors. Through the mist, and by the " +
	     "help of the pale grey light, you make out " +
	     "two former exists to the north and east, they have now " +
	     "been blocked by holes in the floor. A foul-smelling " +
	     "white mist boils up from those holes. You can see the " +
	     "second room of the Hall of the Ancestors to the west. " +
	     "A strange screeching sound seems to come from a dark doorway " +
	     "to the south.\n");

    LIGHT;

    add_exit(HALL + "southcrypt6", "south");
    add_exit(HALL + "hall2", "west");

    add_item("ceiling", "It looks intact.\n");
    add_item("floor", "The floor has collapsed on several places, revealing " +
	     "deep holes.\n");
    add_item(({"hole", "holes"}), "A sound of rushing water can be heard " +
	     "below.\n");

    seteuid(getuid());

    reset_xak_room();
}








