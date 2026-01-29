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
    set_vegetation("scrubby deciduous forest");
    set_extraline("You are on a fertile plateau extending south as far "
      + "as the eye can see. All around, the "+Vegetation+" covers the "
      + "high plateau of "+County+". An old road is running in from "
      + "the north and vanishing to the south.");

    add_exit(DUN_DIR + "road/r24", "north", 0, 5);
    add_exit(DUN_DIR + "road/r22", "south", 0, 5);

}

