#pragma strict_types

inherit "/d/Gondor/common/lib/roads.c";

#include "/d/Gondor/defs.h"

public void
create_roads() 
{
   set_street("decrepit stone paved road");
   set_where("north");
   set_county("Dunland");
   set_land("old Gondor");
   set_mountain("Misty Mountains");
   set_vegetation("scrubby lowland forest");
   set_extraline("You are on a fertile slope falling to the north and "
     + "rising to the south. All around, the "+Vegetation+" covers "
     + "the slopes of "+County+". An old road is descending to the "
     + "north and vanishing upwards to the south.");

    add_exit(DUN_DIR + "road/r25", "north", 0, 5);
    add_exit(DUN_DIR + "road/r23", "south", 0, 5);
}

