/*
 *	/d/Gondor/olorin/farm/road/road2.c
 * 	Coded by Olorin, Nov 1992
 *
 *	Modification log:
 *	28-Jan-1997, Olorin:	Changed inheritance.
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

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
    set_treetype("beech");
    set_extraline("The small farm road runs from northwest to southeast "
      + "here. All around you are " + treetype + " trees.");
    add_exit(FARM_DIR + "road/road1", "northwest", 0, 1);
    add_exit(FARM_DIR + "road/road3", "southeast", 0, 1);
}

