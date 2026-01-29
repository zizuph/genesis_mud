/*
 *	/d/Gondor/rohan/road/wr2.c
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
    set_areadesc("grassy plain");
    set_area("western");
    set_areaname("Westfold");
    set_land("Rohan");
    set_extraline("The Great West Road continues northwest across the grassy "+
        "plains of the Westfold, and southeast towards Edoras, the capital. "+
        "The plains stretch out in all directions.");
    add_exit(ROH_DIR + "plains/i06", "north",     0, 5);
    add_exit(ROH_DIR + "plains/h07", "east",      0, 5);
    add_exit(ROH_DIR + "road/wr1",   "southeast", 0, 3);
    add_exit(ROH_DIR + "road/wr3",   "northwest", 0, 3);
}

