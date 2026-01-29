inherit "/std/door";

#include "/d/Rhovanion/defs.h"
#include <stdproperties.h>
#define CAVE_DIR ERE_DIR + "ere1/"                                

create_door()
{
    set_door_id("pubdoor");
    set_pass_command(({"s","south"}));
    set_door_name(({"wooden door","door"}));
    set_other_room(CAVE_DIR + "lm1c65");

    set_lock_command("lock");
    set_lock_name("lock");
    set_unlock_command("unlock");

    set_open(0); 
}
