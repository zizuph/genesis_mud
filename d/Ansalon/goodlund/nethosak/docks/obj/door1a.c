
#include "/d/Ansalon/goodlund/nethosak/local.h"
inherit STDDOOR;

create_door()
{
    ::create_door();
    set_door_id("door1");
    set_pass_command("fore");
    set_door_name(({"large wooden door","large door","wooden door","door"}));
    set_other_room("/d/Ansalon/goodlund/nethosak/docks/room/kitchen01");
    set_door_desc("This is a sturdy wooden door, keeping the harsh winds " +
       "of the sea out of the kitchen.\n");
    set_open(0);
}

