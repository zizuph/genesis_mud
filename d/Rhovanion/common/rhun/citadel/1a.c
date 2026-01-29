
inherit "/d/Rhovanion/lib/room";
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/farlong.h"

reset_room()
{
	reset_euid();

    if (!find_living("_citadel_guard_1a"))
    {
        object guard;
	    guard = clone_object(RHUN+"npc/citadel_guard");
        guard->set_living_name("_citadel_guard_1a");
        guard->move(TO);
    }
}

create_room()
{
	set_short("Citadel courtyard");
	set_long(
	"You stand in the courtyard of the dark citadel.  It rises "+
	"up, black and menacing, to the west.  You may enter through "+
	"it's great front doors in that direction, or flee the "+
	"area by heading out the gate to the east.\n");

	AE(RHUN+"citadel/gate","east");
	AE(RHUN+"citadel/1b","west");

	IN;

    reset_room();
}

