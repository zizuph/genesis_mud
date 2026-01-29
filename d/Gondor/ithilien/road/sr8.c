/*
 *	/d/Gondor/ithilien/road/sr8.c
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
    set_extraline("The forests west of the road are much thinner "
      + "here than further north and not far south of here they "
      + "finally come to an end.");

    add_mountains(2);
    add_road(-3);
    add_forest(-2);

    add_exit(ITH_DIR + "road/sr7", "north", test_exit, 3);
    add_exit(ITH_DIR + "road/sr9", "south", test_exit, 3);
}

