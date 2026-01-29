#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/rohan/horn/hd_defs.h"

public void
create_area_room()
{
    set_areadesc("wide valley");
    set_areatype(AREATYPE_ROAD);
    set_area("lower");
    set_areaname("the Deeping-Coomb");
    set_land("Rohan");
    set_mountain("");
    set_grass("long green grass");
    set_extraline("The Vale is green and rich-looking. Many homesteads can "+
    "be seen in the distance. A stream gently flows down beside the road. "+
    "The road leads south further into the valley, and northeast towards "+
    "the mouth of it.");

    COOMB_MOUNTAINS;
    PEAKS;
    COOMB_STREAM;
    GULLY;
    add_item("road","The road is in good shape.\n");
    add_item("ground","You see nothing special.\n");
    add_item(({ "homesteads", "homestead" }),
    "In the distance you can see what looks like peaceful homesteads.\n");

    add_exit(ROH_DIR+"horn/coomb/high_vale","south",0,3);
    add_exit(ROH_DIR+"road/helmsroad","northeast",0,3);
}

