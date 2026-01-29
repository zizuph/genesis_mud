/*
 *	/d/Gondor/rohan/road/wr5.c
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
    set_extraline("The Great West Road, as this road is called by the people "+
        "of Rohan, runs in a westwardly direction from the capital Edoras. "+
        "Right here, the road follows the skirts of the White Mountains though, "+
        "resulting in a stretch of the road running from the southeast to the "+
        "northwest. A smaller, less used road branches off to the west here, "+
        "going towards Helm's Deep and the Hornburg. The plains continue "+
        "to the north and the east.");
    add_exit(ROH_DIR + "plains/k03",     "north",     0, 5);
    add_exit(ROH_DIR + "plains/j04",     "east",      0, 5);
    add_exit(ROH_DIR + "road/wr4",       "southeast", 0, 3);
    add_exit(ROH_DIR + "road/helmsroad", "west",      0, 3);
    add_exit(ROH_DIR + "road/wr6",       "northwest", 0, 3);
}

