/*
 * Northern side of the Haradrim camp
 * -- Finwe, July 2005
 */

#pragma strict_types

inherit "/d/Gondor/ithilien/forest/camp";

#include "/d/Gondor/defs.h"

static object	*Haradrim = allocate(1 + random(3));

public void
create_camp()
{
    set_short("In the northern part of the Haradrim camp");
    set_long("The camp extends north into the trees. The ground is trampled " +
        "down and full of boot prints. This appears to be a training area " +
        "of the camp.\n");
    add_item("forest", 
        "The forest extends in all directions, hiding all activity and " +
        "muffling the sounds.\n");
    add_item("path",
	    "The path leads east and south, and seems to have been made by " +
        "humans.\n");

    add_exit(ITH_DIR+"forest/ncamp2", "south", 0);
    add_exit(ITH_DIR+"forest/haradcamp6n", "east", 0);

    reset_room();
}

public void
reset_room()
{
    ::reset_room();
    clone_npcs(Haradrim, NPC_DIR+"haradrim", -1.0);
}
