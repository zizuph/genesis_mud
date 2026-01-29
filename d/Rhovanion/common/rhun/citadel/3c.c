
inherit "/d/Rhovanion/lib/room";

#include <stdproperties.h>
#include "/d/Rhovanion/farlong.h"

reset_room()
{
    reset_euid();

    if(!find_living("_citadel_guard_3c"))
    {
        object guard;
        guard=clone_object(RHUN+"npc/citadel_guard");
        guard->set_living_name("_citadel_guard_3c");
        guard->move(TO);
    }
}
        

create_room()
{
    set_short("Top of stairwell");
	set_long(
        "You stand at the top of a dimly-lit stairwell which leads "+
        "down from here.  You may also exit into the hall to the "+
        "west or southwest.\n");

    AE(RHUN+"citadel/3b","west");
    AE(RHUN+"citadel/3d","southwest");
    AE(RHUN+"citadel/2a","down");

    IN;

    reset_room();

}

