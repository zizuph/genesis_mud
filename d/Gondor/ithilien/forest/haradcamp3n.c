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
    set_long("Tracks lead in all directions, following the path that " +
        "leads through the forest. The camp is neater here then in other " +
        "parts, but still looks dirty.\n");
    add_item("forest", 
        "The forest extends in all directions, hiding all activity and " +
        "muffling the sounds.\n");
    add_item(({"tents", "tent"}),
        "They are square shaped and nicer than most. They line the paths " +
        "and appear in better condition than most.\n");
    add_item("path",
	    "The path leads north, south, east and west, and seems to be well " +
        "used.\n");

    add_exit(ITH_DIR+"forest/haradcamp7n", "north", 0);
    add_exit(ITH_DIR+"forest/haradcamp1b", "south", 0);
    add_exit(ITH_DIR+"forest/haradcamp4n", "east", 0);
    add_exit(ITH_DIR+"forest/haradcamp2n", "west", 0);

    reset_room();
}

public void
reset_room()
{
    ::reset_room();
    clone_npcs(Haradrim, NPC_DIR+"haradrim", -1.0);
}
