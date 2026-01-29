/*
 *	/d/Gondor/lebennin/road/nr10.c
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
    set_area("central");
    set_areadesc("field");
    set_grass("green");
    set_treetype("oak");

    add_exit(LEB_DIR + "road/nr9",     "north",     0, 4);
    add_exit(LEB_DIR + "road/nr11",    "southwest", 0, 4);
    add_exit(LEB_DIR + "road/fieldr1", "southeast", 0, 2);
   
    set_extraline("The road runs north to Minas Tirith. To the southwest, " +
        "it runs through a band of trees that stretches across the plains " +
        "like a dark green wall.");

    add_white_mountains("north");
    add_anduin("central");
    add_ground(0, "Where there are cracks between the paved " +
	       "stones of the road, there is grass growing through " +
	       "them.");
    add_fields("To the south, a group of trees cuts through the " +
        "plains like a dark green wall.");
    add_road(2);

   add_item( ({ "wood", "forest", "band", "ring", "trees", }), BSN(
       "The forest is but a narrow band of trees which runs from west " +
       "to east. The trees are large and most of them are very old, but " +
       "it is obvious that they were planted by men and did not grow here " +
       "naturally. Perhaps they are meant to slow down the wet winds " +
       "that blow northwards from the Sea in the summer, catching some " +
       "of the water they carry as dew."));
}


