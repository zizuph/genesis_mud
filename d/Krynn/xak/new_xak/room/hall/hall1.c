/* 
 * Xak Tsaroth - Hall of the Ancestors
 * Originaly coded by Percy
 * Revamped by Rastlin
 */
#pragma strict_types

#include "../../local.h"

inherit INROOM;

object gDrac1, gDrac2, gDrac3;

public void
reset_xak_room()
{
    MOVE(gDrac1, GET_NPC_HA)
    MOVE(gDrac2, GET_NPC_HA)
    MOVE(gDrac3, GET_NPC_HA)
}

public void
create_xak_room()
{    
    set_short("In the Hall of the Ancestors");
    set_long("This is the second octagonal room that makes the " +
	     "Hall of the Ancestors. The floor has " +
	     "collapsed in several places making big holes from which " +
	     "a foul-smelling white mist boils up. A huge hole in the " +
	     "floor the west makes it impossible to go west in the Hall. " +
	     "The hall is lit by a gray pale light. There are doorways " +
	     "leading north and south into corridors. To the east you " +
	     "can see the third room in the Hall.\n");

    LIGHT;

    add_exit(HALL + "northcrypt4", "north");
    add_exit(HALL + "hall2", "east");
    add_exit(HALL + "southcrypt4", "south");

    add_item("ceiling", "It looks intact.\n");
    add_item("floor", "The floor has collapsed on several places, revealing " +
	     "deep holes.\n");
    add_item(({"hole", "holes"}), "A sound of rushing water can be heard " +
	     "below.\n");
    
    seteuid(getuid());

    reset_xak_room();
}








