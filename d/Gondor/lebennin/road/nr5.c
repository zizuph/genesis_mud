/*
 *	/d/Gondor/lebennin/road/nr5.c
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
    set_area("northeast");
    set_areadesc("field");
    set_grass("light green");
    
    add_exit(LEB_DIR + "road/nr4",   "northeast", 0, 3);
    add_exit(LEB_DIR + "road/ghop1", "south",     0, 1);
    add_exit(LEB_DIR + "road/nr6",   "southwest", 0, 3);
   
    set_extraline("The road leads northeast to Minas Tirith and " +
        "southwest it crosses a river on its way to Pelargir. " +
        "South of it lies a bushy field.");
    add_road(1, "The road runs northeast to Minas Tirith and southwest " +
	"across the plains of Lebennin towards Pelargir upon Anduin " +
        "in the south.");
    add_ground();
    add_white_mountains("north");

   add_item( ({ "river", "erui", }), BSN(
       "The river Erui is one of the tributaries of the Anduin. " +
       "It comes down from the White Mountains and joins the Anduin " +
       "southeast of here. The road crosses the river on a stone " +
       "bridge."));
}

