/*
 *	/d/Gondor/lebennin/road/nr1.c
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
    set_areadesc("harbour-area");
    set_grass("light green");
   
    add_exit(PEL_DIR + "lebennin", "east",      0, 2);
    add_exit(LEB_DIR + "road/nr2", "southwest", 0, 3);

    set_extraline("To the east you see the Harlond, the harbour " +
        "of Minas Tirith. A well-built ancient road leads southwest.");

    add_harlond();
    add_anduin("harlond");
    add_rammas();
    add_road(1, "The road enters the Harlond to the east, and " +
	     "starts on its way through Lebennin to the southwest.");
    add_ground();
    add_white_mountains("northwest");
}
