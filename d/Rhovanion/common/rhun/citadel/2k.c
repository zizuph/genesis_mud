
inherit "/d/Rhovanion/lib/room";

#include <stdproperties.h>
#include "/d/Rhovanion/farlong.h"

reset_room()
{
	reset_euid();
    if(!find_living("_citadel_guard_2k"))
    {
        object guard;
		guard=clone_object(RHUN+"npc/citadel_guard");
        guard->set_living_name("_citadel_guard_2k");
        guard->move(TO);
    }
}

create_room()
{
    set_short("Citadel stairs");
    set_long("This is a round tower, perhaps two meters across, near the "+
        "center of this citadel of dark stone.  You stand near to the short "+
        "tower's ceiling.  Stairs circle around a "+
        "central post, heading down from here to the next floor.  You may "+
        "also head out into the hallway to the northwest or south.\n");

    AE(RHUN+"citadel/2j","southwest");
    AE(RHUN+"citadel/1k","down");

    add_item(({"stair","stairs","stairwell"}),"The stairs are made of "+
        "dark stone, are quite narrow, and head downward here.\n");

    IN;
    
    reset_room();

}

