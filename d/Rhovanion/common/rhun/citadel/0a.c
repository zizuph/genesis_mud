
inherit "/d/Rhovanion/lib/room";

#include <stdproperties.h>
#include "/d/Rhovanion/farlong.h"

create_room()
{
    set_short("Bottom of stairs");
    set_long("You stand at the bottom of a set of straight stone stairs, "+
        "deep, shiny black in color.  No light pushed down from "+
        "above to pervade this darkened cellar.  The floor here, "+
        "unlike the marble of the above building, is dirt, and thick "+
        "webs hang from the ceiling and walls.  You may exit back "+
        "up the stairs, or head through a low, cobweb-strewn arch"+
        "way to the west.\n");

    AE(RHUN+"citadel/0b","west");
    AE(RHUN+"citadel/1p","up");

    IN;

    add_item(({"web","webs","cobweb","cobwebs"}),
        "The cobwebs hang thick here, dangling from ceiling and walls and "+
        "constantly in your face.\n");
    add_item(({"wall","walls"}),"The walls here are still made "+
        "from that same black stone as the citadel above.  Cobwebs "+
        "are strewn all about them.\n");
    add_item("floor","The floor here is simple "+
        "dirt, cold and hard-packed.\n");
    add_item(({"stair","stairs","set","staircase","stairwell",
        "steps"}),"The stairs are carved from that shiny black stone "+
        "from which the rest of this citadel is formed.  They lead "+
        "up from here.\n");
    add_item(({"arch","west"}),"A low-hanging arch, covered in "+
        "cobwebs, stands just west of here.  Beyond it lies "+
        "another dark part of this cellar.\n");

}

