
inherit "/d/Rhovanion/lib/room";

#include <stdproperties.h>
#include "/d/Rhovanion/farlong.h"

reset_room()
{
	reset_euid();
    if(!find_living("_citadel_guard_2b"))
    {
        object guard;
		guard=clone_object(RHUN+"npc/citadel_guard");
        guard->set_living_name("_citadel_guard_2b");
        guard->move(TO);
    }
}

create_room()
{
    set_short("Citadel passage corner");
    set_long("The dark passage makes a right angle here, turning from "+
	"east to north, where it approaches a set of stone stairs.\n");

    AE(RHUN+"citadel/2c","east");
    AE(RHUN+"citadel/2a","north");

    IN;
    
    reset_room();

}

