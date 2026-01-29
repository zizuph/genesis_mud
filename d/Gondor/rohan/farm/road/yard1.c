/* This file is /d/Gondor/olorin/farm/road/yard1.c         */
/* It belongs to a small farm in the Ered Nimrais          */	
/* Olorin, Nov 1992                                        */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public void
create_area_room() 
{
    set_areadesc("clearing");
    set_areatype(7);
    set_area("west");
    set_areaname("the White Mountains");
    set_land("Gondor");
    set_grass("dark green");
    set_treetype("birch");
    set_extraline("You are on a small yard between a cottage to the south "
        + "and a stable to the east. To the north, a small farm road "
        + "disappears into the forest. A path to the southeast runs to "
        + "a meadow. It looks as if it has been used a lot by cattle. The "
        + "farm looks deserted.");
    add_exit(FARM_DIR + "road/road3",   "north", 0, 1);
    add_exit(FARM_DIR + "road/stable1", "east",  0, 1);
    add_exit(FARM_DIR + "road/meadow3", "southeast", 0);
    add_exit(FARM_DIR + "road/garden1", "southwest", 0);
 
    clone_object(FARM_DIR + "road/yarddoor")->move(TO);
}
