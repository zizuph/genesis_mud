/*
 *	/d/Gondor/ithilien/road/sr7.c
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
    set_areadesc("forest");
    set_area("southern");
    set_areaname("Ithilien");
    set_land("Gondor");
    set_extraline("The road runs south towards Harad west of the slopes of the " +
        "Ephel Duath. To the west, the green hills of Emyn Arnen are rising.");

    add_mountains(1, "about a mile");
    add_road(-3);
    add_forest(-2);

    add_emyn_arnen();

    add_exit(ITH_DIR + "road/sr6", "north", test_exit, 4);
    add_exit(ITH_DIR + "road/sr8", "south", test_exit, 4);
}
