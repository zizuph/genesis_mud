/*
 *	/d/Gondor/ithilien/road/sr9.c
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

    add_mountains(2);
    add_road(-3);
    add_forest(-2);

    set_extraline("The road has reached the southern limits of the "
      + "forests of Ithilien here. South of here stretches a large "
      + "plain over which the road flies in the straight line towards "
      + "South Gondor and Harad.");

    add_exit(ITH_DIR + "road/sr8",  "north", test_exit, 4);
    add_exit(ITH_DIR + "road/sr10", "south", test_exit, 4);

}

