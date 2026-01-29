#pragma strict_types

inherit "/d/Gondor/common/lib/roads.c";

#include "/d/Gondor/defs.h"

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#define BLACK_RIDER_ROOM	(MORGUL_DIR + "blackrider")

public void
create_roads() 
{
    set_street("grass-covered road");
    set_where("central");
    set_county("Cardolan");
    set_land("the lost realm of Arnor");
    set_mountain("South Downs");
    set_vegetation("evergreen bushes and undergrowth");
    set_extraline("You are on a treelined road which is overgrown with "
      + "tall grass. Looking around you see the "+Vegetation+" covering "
      + "the land of "+County+". The road runs down from central plains "
      + "towards the horizon.");
    add_exit("/d/Gondor/common/shirelink","northwest", 0, 5);
    add_exit(CARD_DIR + "road/r29","southeast",        0, 5);

    FIX_EUID
    BLACK_RIDER_ROOM->load_me();
}

