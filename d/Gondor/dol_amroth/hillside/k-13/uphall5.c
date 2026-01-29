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

    add_exit(DOL_HILLS + "k-13/uphall1", "east", 0, 1);
}
