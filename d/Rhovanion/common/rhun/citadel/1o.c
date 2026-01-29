
inherit "/d/Rhovanion/lib/room";

#include <stdproperties.h>
#include "/d/Rhovanion/farlong.h"

reset_room()
{
    object guard;
	reset_euid();

    if(!find_living("_citadel_guard_1o"))
    {
        guard=clone_object(RHUN+"npc/citadel_guard");
        guard->set_living_name("_citadel_guard_1o");
        guard->move(TO);
    }
}

create_room()
{
    set_short("Narrowing hallway");
    set_long("The hallway is quite narrow and low here, having lost the "+
        "high arches and magnificent size that distinguishes it in sections "+
        "back to the east.  To the southwest, the passage shrinks down "+
        "and grows quite dim.\n");

    AE(RHUN+"citadel/1p","southwest");
    AE(RHUN+"citadel/1n","east");

    IN;

    reset_room();

}

