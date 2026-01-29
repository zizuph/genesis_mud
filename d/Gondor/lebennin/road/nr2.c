/*
 *	/d/Gondor/lebennin/road/nr2.c
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

    add_exit(LEB_DIR + "road/nr1", "northeast", 0, 3);
    add_exit(LEB_DIR + "road/nr3", "southwest", 0, 3);
   
    set_extraline("The road continues towards Pelargir to the " +
        "southwest and to the Harlond and Minas Tirith to the " +
        "northeast. Beyond the docks of the Harlond, a great " +
	"wall is rising. To the north are the White Mountains.");

    add_rammas();
    add_road(1, "Northeast, the road leads to the Harlond and " +
	"on to Minas Tirith, while southwest it leads over the " +
	"plains of Lebennin and finally to Pelargir.");
    add_ground();
    add_white_mountains("north");
    add_harlond();
    add_anduin("harlond");
}


