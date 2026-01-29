/* /d/Gondor/tharbad/road/r26.c */

inherit "/d/Gondor/common/lib/roads.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public void
create_roads() 
{
    set_street("decrepit stone paved road");
    set_where("north");
    set_county("Dunland");
    set_land("Enedwaith");
    set_mountain("Greyflood Valley");
    set_vegetation("reeds and cattails");
    set_extraline("You are in a fecund marsh extending north as far as the"
           + " eye can see. All around you, the " +Vegetation
           + " spread over the fens of " +County+ ". You see the"
           + " crumbling towers of an ancient city rising over the marshes"
           + " to the northwest. Here the old road climbs to the southeast.");

    add_exit(THARBAD_DIR+"road/r27", "northwest", 0, 2);
    add_exit(DUN_DIR+"road/r25" ,    "southeast", 0, 2);
}

