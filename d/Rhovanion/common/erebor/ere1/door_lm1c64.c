inherit "/std/door";

#include "/d/Rhovanion/defs.h"
#include <stdproperties.h>
#define CAVE_DIR ERE_DIR + "ere1/"                                

create_door()
{
    set_door_id("oakdoor");
    set_pass_command(({"w","west"}));
    set_door_name(({"oak door","oakdoor"}));
    set_other_room(CAVE_DIR + "lm1c63");

    set_lock_command("lock");
    set_lock_name("lock");
    set_unlock_command("unlock");

    set_open(0); 
}
