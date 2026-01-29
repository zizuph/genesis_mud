/*
 *	/d/Gondor/lebennin/road/nr7.c
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
    set_area("east");
    set_areadesc("field");
    set_grass("green");

    add_exit(LEB_DIR + "road/nr6", "northeast", 0, 3);
    add_exit(LEB_DIR + "road/nr8", "south",     0, 3);
   
    set_extraline("The road continues northeast, where it crosses " +
        "a river on a stone bridge, and southwards towards Pelargir " +
        "upon Anduin.");

    add_white_mountains("north");
    add_anduin("central");
    add_ground(0, "In some places on the road, there are " +
	       "cracks between the stones and there grass is " +
	       "growing, too.");
    add_road(2);
    add_item( ({ "erui", "river", }), BSN("The river to the northeast " +
	"is the Erui, which coming out of the White Mountains will " +
        "flow into the Anduin eventually."));
}


