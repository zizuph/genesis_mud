/*
 *	/d/Gondor/lebennin/road/nr8.c
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

    add_exit(LEB_DIR + "road/nr7", "north", 0, 3);
    add_exit(LEB_DIR + "road/nr9", "south", 0, 3);
   
    set_extraline("The road runs north and south, a few miles west " +
	"of the Anduin, over the green fields of Lebennin. The mighty " +
        "river is visible as a wide blue band far to the east.");

    add_white_mountains("north");
    add_anduin("central");
    add_ground(0, "Where there are cracks between the paved " +
	       "stones of the road, there is grass growing through " +
	       "them.");
    add_fields();
    add_road(2);
}
