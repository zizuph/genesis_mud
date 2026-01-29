inherit "/std/door";

#include "/d/Rhovanion/defs.h"
#include <stdproperties.h>
#define CAVE_DIR ERE_DIR + "ere2/"
                                 
create_door()
{
    set_door_id("schooldoor");
    set_pass_command(({"w","west"}));
    set_door_name(({"wooden door","door"}));
    set_other_room(CAVE_DIR + "lm2c9");

    set_lock_name("lock");
          
    set_open(0); 
    set_locked(1);
    set_lock_command("lock");
    set_unlock_command("unlock");
    set_lock_command("lock");
    set_key("small key");
    set_door_desc(BS("It's a wooden door."));
 
 
}
