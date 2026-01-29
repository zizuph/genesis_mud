#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/guilds/khiraa/khiraa_defs.h"

inherit "/std/door.c";

void
create_door()
{
    set_door_name(({"strange warm door","door","north door"}));
    set_door_desc("This door is made of solid iron, but it is "+
    "strangely warm to the touch.\n");
    set_pass_command(({"n","north"}));
    set_door_id("forgedoor");
    set_other_room(KHIRAA_DIR(temple/rooms/t17));
    set_open(0);
}
    
