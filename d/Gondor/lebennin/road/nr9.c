/*
 *	/d/Gondor/lebennin/road/nr9.c
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

    add_exit(LEB_DIR + "road/nr8",  "north", 0, 3);
    add_exit(LEB_DIR + "road/nr10", "south", 0, 3);
   
    set_extraline("The road runs north to Minas Tirith and south " +
	"to Pelargir upon Anduin, following the course of the Anduin " +
        "but a few miles west of the river, crossing the green " +
        "fields of Lebennin. The mighty " +
        "river is visible as a wide blue band far to the east.");

    add_white_mountains("north");
    add_anduin("central");
    add_ground(0, "Where there are cracks between the paved " +
	       "stones of the road, there is grass growing through " +
	       "them.");
    add_fields("To the south, a group of trees cuts through the " +
        "plains like a dark green wall.");
    add_road(3);

    add_item( ({ "tree", "trees", "oaks", }), 
         "The trees around here are few and far between, but they are oaks.\n");
}

