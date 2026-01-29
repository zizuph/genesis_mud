
inherit "/d/Rhovanion/lib/room";

#include <stdproperties.h>
#include "/d/Rhovanion/farlong.h"

reset_room()
{
	reset_euid();

    if(!find_living("_citadel_guard_1l"))
    {
        object guard;
		guard=clone_object(RHUN+"npc/citadel_guard");
        guard->set_living_name("_citadel_guard_1l");
        guard->move(TO);
    }
}

create_room()
{
    set_short("Guest bedchamber");
    set_long("This is a large bedchamber, perhaps once a guest suite.  "+
        "It is arranged nicely with desk, chair, bed, and other articles "+
        "of fine furniture, though a heavy layer of dust lays upon much of "+
        "it.  The only exit is back into the hallway to the west.\n");

    AE(RHUN+"citadel/1m","west");

    add_item(({"bed","chair","chairs","desk","furniture","articles"}),
        "The furniture is quite old, and quite dusty.  It is of no "+
        "interest to you.\n");

    IN;

	reset_room();

}

