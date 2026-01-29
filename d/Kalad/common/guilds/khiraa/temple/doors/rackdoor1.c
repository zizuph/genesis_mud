#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/guilds/khiraa/khiraa_defs.h"

inherit "/std/door.c";

void
create_door()
{
    set_door_name(({"black steel door","door","north door"}));
    set_door_desc("This is a strong and sturdy steel door. "+
    "Written upon it you see the ancient runes meaning "+
    "'Equipment'.\n");
    set_pass_command(({"n","north"}));
    set_door_id("rackdoor");
    set_other_room(KHIRAA_DIR(temple/rooms/temple_rack));
    set_open(0);
}
    
