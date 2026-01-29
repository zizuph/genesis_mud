#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/guilds/khiraa/khiraa_defs.h"

inherit "/std/door.c";

void
create_door()
{
    set_door_name(({"eerie glowing door","door","south door"}));
    set_door_desc("This door has an eerie greenish glow to it. "+
    "Upon it, you see a large S symbol on it.\n");
    set_pass_command(({"s","south"}));
    set_door_id("studydoor");
    set_other_room(KHIRAA_DIR(temple/rooms/t13));
    set_open(0);
}
    
