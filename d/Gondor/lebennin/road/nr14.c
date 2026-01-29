/*
 *	/d/Gondor/lebennin/road/nr14.c
 *
 *	This version:
 *	Copyright (c) 1997 by Christian Markus
 *
 *	Modification log:
 *	 2-Feb-1997, Olorin:	General revision,
 *				changed inheritance.
 */
#pragma strict_types

inherit "/d/Gondor/lebennin/road/road.c";

#include "/d/Gondor/defs.h"

public void
create_road()
{
    set_area("southern");
    set_areaname("Lebennin");
    set_land("Gondor");
    set_areatype(8);
    set_areadesc("great plain");
    set_grass("green");

    add_exit(LEB_DIR + "road/nr13", "north",     0, 4);
    add_exit(LEB_DIR + "road/nr15", "southwest", 0, 4);

    set_extraline("From the forest to the north, the road crosses the " +
        "plains of Lebennin, running towards Pelargir upon Anduin.");

    add_plain("forest");
    add_item( ({ "wood", "forest", "band", "ring", "trees", }), BSN(
        "The forest is but a narrow band of trees which runs from west " +
        "to east. The trees are large and most of them are very old, but " +
        "it is obvious that they were planted by men and did not grow here " +
        "naturally. Perhaps they are meant to slow down the wet winds " +
        "that blow northwards from the Sea in the summer, catching some " +
        "of the water they carry as dew."));
    add_pelargir("far");
    add_road(1);
    add_ground();
    add_anduin("south");
    add_plain("forest");
}
