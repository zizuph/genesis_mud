
inherit "/d/Rhovanion/lib/room";

#include <stdproperties.h>
#include "/d/Rhovanion/farlong.h"

reset_room()
{
	reset_euid();
    if(!find_living("_citadel_guard_2e"))
    {
        object guard;
		guard=clone_object(RHUN+"npc/citadel_guard");
        guard->set_living_name("_citadel_guard_2e");
        guard->move(TO);
    }
}

create_room()
{
    set_short("Citadel passage corner");
    set_long("The dark passage makes a right angle here, turning from "+
	"west to south.\n");

    AE(RHUN+"citadel/2f","west");
    AE(RHUN+"citadel/2d","south");

    IN;
    
    reset_room();

}

