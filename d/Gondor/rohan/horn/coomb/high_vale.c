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
    set_area("higher");
    set_areaname("the Westfold Vale");
    set_land("Rohan");
    set_mountain("");
    set_grass("long green grass");
    set_extraline("The Vale is green and rich-looking. Many homesteads are "+
    "further down in the valley, they are fewer up here. "+ 
    "A stream gently flows down beside the road. "+
    "Tall snow-covered peaks rise towards the sky high above you. "+
    "To the south is the mouth of the Coomb, and to the "+
    "north is the lower part of the Westfold Vale.");

    ROAD;
    COOMB_MOUNTAINS;
    PEAKS;
    COOMB_STREAM;
    GULLY;
    add_item("ground", "You see nothing special.\n");
    add_item("coomb","You can't see anything but the entrance to "+
    "the Deeping-Coomb from here.\n");
    add_item(({ "homesteads", "homestead" }),
    "In the distance you can see what looks like peaceful homesteads.\n");

    add_exit(ROH_DIR+"horn/coomb/ne_coomb","south",0,3);
    add_exit(ROH_DIR+"horn/coomb/low_vale","north",0,3);
}

