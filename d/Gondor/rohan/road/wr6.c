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
    set_areadesc("rocky field");
    set_area("western");
    set_areaname("West Emnet");
    set_land("Rohan");
    set_extraline("The Great West Road crosses the Deeping-stream right here, "+
        "and continues southeast and northwest along the skirts of the White "+
        "Mountains. A smaller and less used road branches off towards the "+
        "south here, leading to Helm's Deep. To the northwest the road "+
        "continues towards the Fords of Isen.");
    add_exit(ROH_DIR + "plains/k03",     "east",      0, 5);
    add_exit(ROH_DIR + "road/wr5",       "southeast", 0, 3);
    add_exit(ROH_DIR + "road/helmsroad", "south",     0, 3);
    add_exit(ROH_DIR + "road/wr7",       "northwest", 0, 3);
}

