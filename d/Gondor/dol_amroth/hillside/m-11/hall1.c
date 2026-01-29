/*
 * hall1.c
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
    set_short("a large hall");
    set_long("This is inside a large hall. The walls are high and " +
	     "decorated with beatifully decorated figurines and " +
	     "paintings of people sitting in gardens. All the paintings " +
	     "are framed with golden collums reaching from the floor " +
	     "to the roof. From each of the corners on the east wall " +
	     "stair leads up, and where they meet the goes together and " +
	     "continues upwards. On each of the walls a huge arched door " +
	     "is placed.\n");

   add_item( ({ "hall", "large hall" }),
	      "This is inside a large hall. The walls are high and " +
	      "decorated with beatifully decorated figurines and " +
	      "paintings of people sitting in gardens. All the paintings " +
	      "are framed with golden collums reaching from the floor " +
	      "to the roof. From each of the corners on the east wall " +
	      "stair leads up, and where they meet the goes together and " +
	      "continues upwards. On each of the walls a huge arched door " +
	      "is placed.\n");
    add_item( ({ "walls" , "high walls" }), "The walls are decorated with " +
	      "beautifully decorated figurines and paintings paintings of " +
	      "people sitting in gardens.\n");
    add_item( ({ "figurines", "decorated figurines", 
		     "beautifully decorated figurines" }),
	      "Beautifully decorated figurines symbolising valar are " +
	      "put up on the wall, framed by golden collumns.\n");
    add_item( ({ "paintings", "people", "gardens" }), "some description\n");
    add_item("collumns", "Golden collumns are framing the pictures on the " +
	     "walls. The collumns are round with ornaments on the top and " +
	     "base.\n");
    add_item( ({ "floor", "stones", "tiles" }), 
	      "The floor is tiled with black and white stones.\n");
    add_item("roof", "The roof high up is doomed and bright white. In the " +
	     "the middle of the room hangs a large lamp.\n");
    add_item( ({ "lamp", "large lamp" }), "A large lamp hangs down from the " +
	      "middle of the roof. The lamp is made out from ornamented " +
	      "golden staves with oil burners.\n");
    add_item("corners", "The corners are clean. From both the corners on " +
	     "the east wall stairs leads up to the upper floor.\n");
    add_item("stairs", "From both corners on the east wall wide stairs " +
	     "leads up to the upper floor. A red carpet covers the steps.\n");
    add_item( ({ "steps", "carpet", "red carpet" }), "A red carpet is " +
	      "coverint the steps in the stairs.\n");
    add_item("doors", "Large arched doors leads from this hall in all " +
	     "directions. The doors are sturdy and make out of oak.\n");

    add_exit(DOL_HILLS + "m-11/garden1", "west", 0, 1);
    add_exit(DOL_HILLS + "m-11/hall2", "north", 0, 1);
    add_exit(DOL_HILLS + "m-11/hall3", "east", 0, 1);
    add_exit(DOL_HILLS + "m-11/hall4", "south", 0, 1);
    add_exit(DOL_HILLS + "m-11/upstairs", "up", 0, 1);

    add_prop(ROOM_I_NO_ALLOW_STEED, 1);

    FIREMASTER->fire_north();
    FIREMASTER->extinguish_south();
}


