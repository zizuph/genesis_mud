/*
 * Lucius May 2009: Cleaned and updated, moved from /d/Terel/dark/
 */
#pragma strict_types

inherit "/std/room";
#include "../dark.h"

public void
create_room(void)
{
    set_short("Dark Cave");
    set_long("This black and dismal cavern smells of rotting flesh and "+
	"fecal matter. The cavern walls are coated with a layer of "+
	"slime and mold. The floor is covered with loose rocks, "+
	"bones and water. Toward the back, where the floor slopes "+
	"upward to meet the cavern wall, there is a hole leading "+
	"down into impenetrable darkness.\n");

    add_item("bones", "They are many and of various types, " +
	"gnawed clean and broken.\n");
    add_item("slime", "It is deep and foul, an almost luminous green.\n");
    add_item("mold", "A natural consequence of the rot.\n");
    add_item(({"hole", "back", "floor"}), "There is a hole in the "+
	    "floor near the back of the cavern. The darkness is too deep "+
        "to see where it goes.\n");		

    IN; BLACK;

    add_exit(L1 + "e4", "north");
    add_exit(L2 + "add/t30", "down");
}
