/*
 * upstairs.c
 *
 * Skippern 20(c)02
 *
 */
#include "../../defs.h"
inherit DOL_STD + "inside";

void
create_inside()
{
    set_short("on a gallery");
    set_long("You are in an arched corridor going round the main hall. " +
	     "Looking towards the center of the room you see a railing " +
	     "between each arch, and in the middle hangs a large lamp. " +
	     "The walls are decorated like a forest, with small trees " +
	     "and bushes. Somewhere between the bushes some animals is " +
	     "seen. There are three doors on the north wall, and three " +
	     "on the south wall, but only one is open, leading north.\n");

    add_item("roof", "The roof high up is doomed and bright white.\n");
    add_item( ({ "lamp", "large lamp" }), "A large lamp hangs down from the " +
              "middle of the roof. The lamp is made out from ornamented " +
	      "golden staves with oil burners.\n");

    add_exit(DOL_HILLS + "m-11/bedroom", "north", 0, 1);
    add_exit(DOL_HILLS + "m-11/hall1", "down", 0, 1);
}
