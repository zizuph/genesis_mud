
inherit "/d/Rhovanion/lib/room";

#include <stdproperties.h>
#include "/d/Rhovanion/farlong.h"

reset_room()
{
    reset_euid();

    if(!find_living("_citadel_guard_3a"))
    {
        object guard;
        guard=clone_object(RHUN+"npc/citadel_guard");
        guard->set_living_name("_citadel_guard_3a");
        guard->move(TO);
    }
}
        

create_room()
{
    set_short("Bottom of narrow steps");
	set_long(
        "This is the bottom of a set of narrow steps.  They lead upward "+
        "from here, though you can't tell what lies at the top.  The "+
        "steps are fashioned of that same shiny dark stone as the "+
        "rest of this citadel-- they, however, look little-travelled, "+
        "with a thin layer of dust covering them.  You may also head back "+
        "out into the hall to the southwest.\n");

    AE(RHUN+"citadel/4a","up");
    AE(RHUN+"citadel/3b","southwest");

    IN;

    reset_room();

}

