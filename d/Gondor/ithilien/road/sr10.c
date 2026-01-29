/*
 *	/d/Gondor/ithilien/road/sr10.c
 *
 *	Coded by Olorin.
 *
 *	Modification log:
 *	 3-Feb-1997, Olorin:	Changed inheritance.
 */
#pragma strict_types

inherit "/d/Gondor/ithilien/road/road.c";

#include "/d/Gondor/defs.h"

public void
create_area_room()
{
    set_areatype(8);
    set_areadesc("plain");
    set_area("southern");
    set_areaname("Ithilien");
    set_land("Gondor");

    add_mountains(2);
    add_road(-3);

    set_extraline("The road runs south towards Harad west of the "
      + "slopes of the Ephel Duath.");

    add_exit(ITH_DIR + "road/sr9",         "north", test_exit, 3);
    add_exit(ITH_DIR + "poros/ford_north", "south", test_exit, 3);
}

