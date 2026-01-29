/*
 *	/d/Gondor/ithilien/dagorlad/path4.c
 *
 *	Coded by Olorin.
 *
 *	Modification log:
 *	 5-Feb-1997, Olorin:	Changed inheritance.
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include "/d/Gondor/defs.h"

public void
create_area_room()
{
    set_areatype(9);
    set_areadesc("marshes");
    set_area("northern");
    set_areaname("Ithilien");
    set_land("Gondor");
    set_extraline("Dead grasses and rotting reeds cover the ground " +
        "between an endless network of pools, and soft mires, and " +
        "winding half-strangled water-courses. It needs a cunning " +
        "eye and a sure foot to thread a wandering path through all this.\n");
    add_item(({"marsh", "marshes", "pools", "mires"}), 
        "What from far might look like one vast fen is really an " +
        "endless network of of pools, and soft mires, and winding " +
        "half-strangled water-courses. The only green is the scum " +
        "of livid weed on the greasy surfaces of sullen waters. " +
        "Dead grasses and rotting reeds loom up like ragged shadows " +
        "of long-forgotten summers.\n");
    add_item(({"path"}), 
        "A path is winding through the endless network of pools, " +
        "soft mires and water-courses, but it needs a cunning eye " +
        "and foot to find it.\n");
    add_exit(ITH_DIR + "dagorlad/path5", "northwest", 0, 5);
    add_exit(ITH_DIR + "dagorlad/path3", "south",     0, 5);
}

string
short_desc()
{
    if (areatype != 9)
        return ::short_desc();

    return "Barren "+areadesc+" in the "+area+" parts of "+areaname+" in "+land;
}
