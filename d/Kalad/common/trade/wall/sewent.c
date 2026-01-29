inherit "/d/Kalad/room_std";
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Kalad/defs.h"

void
create_room()
{
set_short("An Empty Room");
set_long("This is a poorly lit room, almost void of everything "
        +"but dirt and a rusty ladder.\n");
/*
add_cmd_item(({"north","shadows"}),"enter");
add_cmd_item("shadows","enter");
add_item(({"shadows","shadow"}),"The shadows seem to take up the "
                               +"entire north wall.\n");
*/
add_exit(TRADE(wall/house1),"south");
add_exit(TRADE(sewers/s1),"down");

add_prop(ROOM_I_INSIDE,1);
add_prop(ROOM_NO_TIME_DESC,1);
}
