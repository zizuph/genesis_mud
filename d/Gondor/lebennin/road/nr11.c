/*
 *	/d/Gondor/lebennin/road/nr11.c
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
    set_area("south");
    set_areadesc("road");
    set_areatype(7);
    set_grass("green");
    set_treetype("cypress");

    add_exit(LEB_DIR + "road/nr10", "northeast", 0, 2);
    add_exit(LEB_DIR + "road/nr12", "south",     0, 2);
   
    set_extraline("The road cuts here through a narrow band of trees " +
        "that runs from west to east. A little further to the south " +
        "the road continues its journey across the plains of Lebennin.");

    add_ground(0, "Where there are cracks between the paved " +
	       "stones of the road, there is grass growing through " +
	       "them.");
    add_road(2);

    add_item( ({ "wood", "forest", "band", "ring", "trees", }), BSN(
        "The forest is but a narrow band of trees which runs from west " +
        "to east. The trees are large and most of them are very old, but " +
        "it is obvious that they were planted by men and did not grow here " +
        "naturally. Perhaps they are meant to slow down the wet winds " +
        "that blow northwards from the Sea in the summer, catching some " +
        "of the water they carry as dew."));
    add_item( ({ "plains", "fields", }), BSN("The green fields of Lebennin " +
        "stretch north and south of the forest, which cuts through them " +
        "like a dark green wall."));
}
