/*
 *	/d/Gondor/ithilien/road/nr7.c
 *
 *	Coded by Olorin, 1993
 *
 *	Modification log:
 *	 1-Feb-1997, Olorin:	Changed inheritance.
 */
#pragma strict_types

inherit "/d/Gondor/ithilien/road/road.c";

#include "/d/Gondor/defs.h"

public void
create_area_room()
{
    set_areatype(8);
    set_areadesc("forest");
    set_area("northern");
    set_areaname("Ithilien");
    set_land("Gondor");
    set_extraline("The road runs north towards Morannon, south to the crossroads " +
        "where this road meets the road from Osgiliath to Minas Morgul. Large " +
        "thickets and a tumbled land of rocky ghylls and crags lie to the east. " +
        "Behind them the long grim slopes of the Ephel Duath clamber up. To the " +
        "west, the forests of central Ithilien accompany the road. Sometimes the " +
        "Anduin can be seen through the top of the trees.\n");
    add_mountains(1, "more than a mile");
    add_road(3);
    add_forest(2);

    add_exit(ITH_DIR + "road/nr8", "north", test_exit, 3);
    add_exit(ITH_DIR + "road/nr6", "south", test_exit, 3);
}

