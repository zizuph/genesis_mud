/*
 *	/d/Gondor/ithilien/road/nr3.c
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
    set_area("central");
    set_areaname("Ithilien");
    set_land("Gondor");
    set_extraline("The road runs north towards Morannon, south to the crossroads " +
      "where this road meets the road from Osgiliath to Minas Morgul. Large " +
      "thickets and a tumbled land of rocky ghylls and crags lie to the east. " +
      "Behind them the long grim slopes of the Ephel Duath clamber up.  " +
      "Something to the west catches your eye, where the forests " +
      "of central Ithilien accompany the road.\n");
    add_item("west","The forest to the west seems thin enough to pass through.\n");
    add_mountains(1, "only about a league");
    add_road(2);
    add_forest(1);
    add_exit(ITH_DIR + "road/nr4", "north", test_exit, 3);
    add_exit(ITH_DIR + "road/nr2", "south", test_exit, 3);
    add_exit(ITH_DIR + "camp/rms/fort1","west",test_exit,1,1);
}

