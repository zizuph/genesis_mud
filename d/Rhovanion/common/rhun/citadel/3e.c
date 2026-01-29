
inherit "/d/Rhovanion/lib/room";

#include <stdproperties.h>
#include "/d/Rhovanion/farlong.h"


create_room()
{
    set_short("Citadel hallway");
	set_long(
        "The dark stone hallway forms a corner here.  You may follow it "+
        "back to the east or north.  There are signs that "+
        "something humanoid has been here, and a chilly feeling "+
        "suddenly haunts you.  You wonder what it could be from.\n");

    AE(RHUN+"citadel/3d","east");
    AE(RHUN+"citadel/3f","north");

    IN;
}

