
inherit "/d/Rhovanion/lib/room";

#include <stdproperties.h>
#include "/d/Rhovanion/farlong.h"

reset_room()
{
	reset_euid();
    if(!find_living("_citadel_guard_2a"))
    {
        object guard;
		guard=clone_object(RHUN+"npc/citadel_guard");
        guard->set_living_name("_citadel_guard_2a");
        guard->move(TO);
    }
}

create_room()
{
    set_short("Citadel stairs");
    set_long("You stand at the bottom of a narrow stairwell.  The "+
	"steps of black stone lead upward from here.  You can also "+
	"exit to the south or northwest.\n");

    AE(RHUN+"citadel/2b","south");
    AE(RHUN+"citadel/3c","up");
    AE(RHUN+"citadel/2g", "northwest");

    add_item(({"stair","stairs","stairwell"}),"The stairs are made of "+
        "dark stone, are quite narrow, and head upward here.\n");

    IN;
    
    reset_room();

}

