#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/guilds/khiraa/khiraa_defs.h"

inherit "/std/door.c";

void
create_door()
{
    set_door_name(({"solid black oak door","door","west door"}));
    set_door_desc("It is an old door made of black oak. There "+
    "is a large symbol on the door, that of a circle around "+
    "a grim skull.\n");
    set_pass_command(({"w","west"}));
    set_door_id("circledoor");
    set_other_room(KHIRAA_DIR(temple/rooms/temple_circle));
    set_open(0);
}
    
