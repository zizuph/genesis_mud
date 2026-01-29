/*
 *	/d/Gondor/rohan/road/wr3.c
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

public void
create_area_room()
{
    set_areatype(8);
    set_areadesc("green, grassy plain");
    set_area("western");
    set_areaname("Westfold");
    set_land("Rohan");
    set_extraline("The Great West Road continues west and southeast across "+
        "the endless plains of the Westfold in Rohan. The grassy plains "+
        "stretch out in all directions.");
    add_exit(ROH_DIR + "plains/j05", "north",     0, 5);
    add_exit(ROH_DIR + "plains/i06", "east",      0, 5);
    add_exit(ROH_DIR + "road/wr2",   "southeast", 0, 3);
    add_exit(ROH_DIR + "road/wr4",   "west",      0, 3);
}
