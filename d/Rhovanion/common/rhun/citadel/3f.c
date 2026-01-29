
inherit "/d/Rhovanion/lib/room";

#include <stdproperties.h>
#include "/d/Rhovanion/farlong.h"

reset_room()
{
    reset_euid();

    if(!find_living("_citadel_guard_3f"))
    {
        object guard;
        guard=clone_object(RHUN+"npc/citadel_guard");
        guard->set_living_name("_citadel_guard_3f");
        guard->move(TO);
    }
}
        

create_room()
{
    set_short("Hall");
	set_long(
        "The dark stone hallway heads north to south here.  You "+
        "have a funny feeling, for some reason, and for a "+
        "minute ponder leaving this citadel and never returning.  Then "+
        "it passes, & you continue on your way.\n");

    AE(RHUN+"citadel/3g","north");
    AE(RHUN+"citadel/3e","south");

    IN;

    reset_room();

}

