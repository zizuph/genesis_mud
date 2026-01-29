#pragma strict_types

inherit "/d/Gondor/common/lib/roads.c";

#include "/d/Gondor/defs.h"

public void
create_roads() 
{
    set_street("overgrown, stone paved road");
    set_where("southeast");
    set_county("Dunland");
    set_land("old Gondor");
    set_mountain("Misty Mountains");
    set_vegetation("sparse blue green grass");

    set_extraline("You are on a grassy plateau extending as far as "
      + "the eye can see. In all directions, the "+Vegetation
      + " covers the land of " +County+ ". An old road is running in "
      + "from the northwest and turning to the east.");

   add_exit(DUN_DIR+"road/r04", "northwest", 0, 5);
   add_exit(DUN_DIR+"road/r02", "east",      0, 5);
}

