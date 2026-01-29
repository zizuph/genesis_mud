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
    set_vegetation("tall yellow-brown grass");
    set_extraline("You are on a dry plateau extending as far as the "
      + "eye can see. All around you, the "+Vegetation+" covers the "
      + "high plains of "+County+". An old road is running in from "
      + "the north and turning to the southeast.");

   add_exit(DUN_DIR + "road/r23", "north",     0, 5);
   add_exit(DUN_DIR + "road/r04", "southeast", 0, 5);

}

