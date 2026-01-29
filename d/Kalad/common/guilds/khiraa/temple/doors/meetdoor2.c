#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/guilds/khiraa/khiraa_defs.h"

inherit "/std/door.c";

void
create_door()
{
    set_door_name(({"reddish oak door","door","south door"}));
    set_door_desc("This door is made of reddish black wood. Its "+
    "hinges are made of solid gold, and you can see a grim "+
    "looking skull painted on it in green.\n");
    set_pass_command(({"s","south"}));
    set_door_id("meetdoor");
    set_other_room(KHIRAA_DIR(temple/rooms/t12));
    set_open(0);
    set_lock_name("lock");
    set_lock_command("lock");
    set_unlock_command("unlock");
    set_key("_khiraa_master_key_");
    set_lock_desc("A skull-shaped hole.\n");
}
    
