
inherit "/d/Rhovanion/lib/room";

#include <stdproperties.h>
#include "/d/Rhovanion/farlong.h"


create_room()
{
    set_short("Citadel hallway");
	set_long(
        "The dark stone hallway forms a corner here.  You may follow it "+
        "back to the southeast or south.  There are signs that "+
        "something humanoid has been here, and a chilly feeling "+
        "suddenly haunts you.  You wonder what it could be from.\n");

    AE(RHUN+"citadel/3b","southeast");
    AE(RHUN+"citadel/3f","south");

    IN;
}

