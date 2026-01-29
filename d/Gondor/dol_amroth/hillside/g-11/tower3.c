/*
 * tower3.c
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
    set_short("the third level in a tower");
    set_long("This is the third level of a high tower. The circular " +
		"walls echoes with strange sounds from upstairs. This room " +
		"itself is naked, as if it is unused.\n");
	
	add_item( ({ "wall", "walls" }), "The walls are barren and naked.\n");

    add_exit(DOL_HILLS + "g-11/tower4", "up", 0, 1);
    add_exit(DOL_HILLS + "g-11/tower2", "down", 0, 1);

    add_prop(ROOM_I_NO_ALLOW_STEED, 1);
}


