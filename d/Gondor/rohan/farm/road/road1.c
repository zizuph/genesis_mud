/*
 * 	/d/Gondor/rohan/farm/road/road1.c
 *	It belongs to a small farm in the Ered Nimrais
 *	Olorin, Nov 1992
 *	Modification log:
 *	Olorin, July 1995, general update
 *	30-Jan-1997, Olorin:	Changed inheritance.
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public void
create_area_room() 
{
    set_areadesc("farm road");
    set_areatype(7);
    set_area("west");
    set_areaname("the White Mountains");
    set_land("Gondor");
    set_grass("dark green");
    set_treetype("birch");
    set_extraline("To the north, you can see a road through the "+treetype
      + " trees surrounding you. The small farm road continues to the "
      + "southeast, leading into a small valley of "+areaname+".");
    add_exit(ROH_DIR + "road/wr4",    "north",     0, 1);
    add_exit(FARM_DIR + "road/road2", "southeast", 0, 1);
    add_exit(FARM_DIR + "entrance",   "south",     0, 1);
}
