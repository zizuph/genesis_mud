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
    set_extraline("You are on a grassy plateau. The land slopes down "
      + "somewhat to the southeast. In all directions, the "+Vegetation
      + " covers the land of "+County+". A road is running from the "
      + "west and turning down to the southeast.");

    add_item(({"grass", "green grass", "sparse grass", "sparse blue green grass"}),
        "The grass flows away in all directions, blowing gently in the wind.\n");

    add_exit(DUN_DIR+"road/r03", "west",      0, 5);
    add_exit(DUN_DIR+"road/r01", "southeast", 0, 5);
}

