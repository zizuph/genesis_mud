
inherit "/d/Rhovanion/lib/room";

#include <stdproperties.h>
#include "/d/Rhovanion/farlong.h"

reset_room()
{
    reset_euid();

    if(!find_living("_citadel_guard_4a"))
    {
        object guard;
        guard=clone_object(RHUN+"npc/citadel_guard");
        guard->set_living_name("_citadel_guard_4a");
        guard->move(TO);
    }
}
        

create_room()
{
    set_short("Top of narrow steps");
	set_long(
        "This is the top of a set of very narrow stone steps.  You "+
        "follow them downward from here, or head south "+
        "into a large, very dark chamber.  For some reason "+
        "the latter frightens you somewhat.\n");

    AE(RHUN+"citadel/3a","down");
    AE(RHUN+"citadel/4b","south");

    IN;

    reset_room();

}

