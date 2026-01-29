#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/guilds/khiraa/khiraa_defs.h"

inherit "/std/door.c";

void
create_door()
{
    set_door_name(({"solid black oak door","door","east door"}));
    set_door_desc("It is an old door made of black oak. There "+
    "is a large symbol on the door, that of a circle around "+
    "a grim skull.\n");
    set_pass_command(({"e","east"}));
    set_door_id("circledoor");
    set_other_room(KHIRAA_DIR(temple/rooms/t12));
    set_open(0);
}
    
