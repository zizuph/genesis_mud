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
    set_vegetation("reeds and cattails");

    set_extraline("You are in a fecund marsh extending north as far "
      + "as the eye can see. All around, the "+Vegetation+" spread "
      + "over the fens of "+County+". The crumbling towers of an "
      + "ancient city are rising over the marshes to the northwest. "
      + "Here the old road climbs to the south.");

    add_exit(DUN_DIR + "road/r24", "south",         0, 5);
    add_exit(THARBAD_DIR + "road/r26", "northwest", 0, 5);

}

