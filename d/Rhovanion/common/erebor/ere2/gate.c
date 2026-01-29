inherit "/std/door";

#include "/d/Rhovanion/defs.h"
#include <stdproperties.h>
#define CAVE_DIR ERE_DIR + "ere2/"
                                 
create_door()
{
    set_door_id("irongate");
    set_pass_command(({"e","east"}));
    set_door_name(({"iron gate","gate"}));
    set_other_room(CAVE_DIR + "lm2c34");

    set_lock_name("lock");
          
    set_open(0); 
    set_locked(1);
    set_unlock_command("unlock");
    set_key("big key");
    set_door_desc(BS("Its the gate to an indoor castle.\n"));
 
 
}
