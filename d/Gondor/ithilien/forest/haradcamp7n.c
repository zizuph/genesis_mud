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
    set_long("The area is well trampled and dirty from all the activity " +
        "that occurs here. The forest surrounds the area, and hides " +
        "prying eyes from the north.\n");
    add_item("forest", 
        "The forest extends in all directions, hiding all activity and " +
        "muffling the sounds.\n");
    add_item("path",
	    "The path leads east, west, and south, and seems to be well used.\n");

    add_exit(ITH_DIR+"forest/haradcamp3n", "south", 0);
    add_exit(ITH_DIR+"forest/haradcamp8n", "east", 0);
    add_exit(ITH_DIR+"forest/haradcamp6n", "west", 0);

    reset_room();
}

public void
reset_room()
{
    ::reset_room();
    clone_npcs(Haradrim, NPC_DIR+"haradrim", -1.0);
}
