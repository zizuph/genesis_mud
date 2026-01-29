/*
 * tower2.c
 *
 * Skippern 20(c)02
 *
 * A large hall inside a noble house.
 *
 */
#include "../../defs.h"
inherit DOL_STD + "inside";

#include <stdproperties.h>

void
create_inside()
{
    set_short("the second level in a tower");
    set_long("This is the second level of a high tower. The walls " +
		"have an odd shape, as the base of the room is square, " +
		"while the ceiling is circular.\n");
	
	add_item("floor", "The floor is square. It looks like it " +
		"is made of one piece of stone.\n");
	add_item("ceiling", "The ceiling is circular. It looks " +
		"looks like it is made of one piece of stone. Spaced " +
		"along the edge is some bird figurines with its wings " +
		"touching the ceiling.\n");
	add_item( ({ "bird", "birds", "figurine", "figurines",
		"bird figurine", "bird figurines" }), "Spaced along " +
		"the edge of the ceiling is some bird figurines with its " +
		"wings touching the ceiling. They look like common crows, " +
		"nothing special about them.\n");

    add_exit(DOL_HILLS + "g-11/tower3", "up", 0, 1);
    add_exit(DOL_HILLS + "g-11/tower1", "down", 0, 1);

    add_prop(ROOM_I_NO_ALLOW_STEED, 1);
}


