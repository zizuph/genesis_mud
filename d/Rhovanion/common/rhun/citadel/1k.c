
inherit "/d/Rhovanion/lib/room";

#include <stdproperties.h>
#include "/d/Rhovanion/farlong.h"

create_room()
{
    set_short("Citadel stairs");
    set_long("This is a round tower, perhaps two meters across, near the "+
        "center of this citadel of dark stone.  Stairs circle around a "+
        "central post, heading up from here to the next floor.  You may "+
        "also head back out into the hallway.\n");

    AE(RHUN+"citadel/1j","south");
    AE(RHUN+"citadel/2k","up");

    add_item(({"stair","stairs","stairwell"}),"The stairs are made of "+
        "dark stone, are quite narrow, and head upward here.\n");

    IN;

}

