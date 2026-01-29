/*
 *	/d/Gondor/rohan/road/wr4.c
 *
 *	Coded by Gus (?), 1992
 *
 *	Modification log:
 *	 4-Feb-1997, Olorin:	Changed inheritance,
 *				general revision.
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include "/d/Gondor/defs.h"

static object  Guard;

public void
create_area_room()
{
    set_areatype(8);
    set_areadesc("grassy plain");
    set_area("western");
    set_areaname("Westfold");
    set_land("Rohan");
    set_extraline("The Great West Road continues unabated through the open " +
        "plains of Rohan. To the northwest the road draws closer to the "+
        "northmost peaks of the White Mountains, while going the other "+
        "way, towards the east, will lead you to Edoras, the capital of Rohan. "+
        "The plains of the Westfold stretch out to the north and south.");
    add_exit(ROH_DIR + "plains/j04",      "north",     0, 5);
    add_exit(ROH_DIR + "road/wr3",        "east",      0, 3);
    add_exit(ROH_DIR + "farm/road/road1", "south",     0, 2);
    add_exit(ROH_DIR + "road/wr5",        "northwest", 0, 3);
    reset_room();
}

public void
reset_room()
{
    Guard = clone_npc(Guard, ROH_DIR + "npc/roadguard");
}

