/* 
 * Xak Tsaroth - Hall of the Ancestors
 * Originally coded by Percy
 * Revamped by Rastlin
 */
#pragma strict_types

#include "../../local.h"

inherit INROOM;

public void
create_xak_room()
{    
    set_short("In the Hall of the Ancestors");
    set_long("You have entered the Hall of the Ancestors beneath the temple " +
	     "of Mishakal. The hall is lit by a pale gray light, showing " +
	     "the three roughly octagonal rooms, each crowned by a raised " +
	     "portion in the ceiling, that forms the hall. Although the " +
	     "ceiling is intact, the floor has collapsed in several places. " +
	     "A big hole in the floor from which a foul-smelling white " +
	     "mist boils up, makes it impossible to go further east in the " +
	     "hall. Through the mist you can faintly distinguish a dark " +
	     "doorway on the south wall and another on the north. " +
	     "A strange screeching sound comes from south.\n");

    LIGHT;

    add_exit(HALL + "northcrypt1", "north");
    add_exit(HALL + "southcrypt1", "south");
    add_exit(HALL + "stairs", "west");

    add_item("ceiling", "It looks intact.\n");
    add_item("floor", "The floor has collapsed on several places, revealing " +
	     "deep holes.\n");
    add_item(({"hole", "holes"}), "A sound of rushing water can be heard " +
	     "below.\n");

}








