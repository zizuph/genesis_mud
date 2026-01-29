inherit "/std/door";

#include "/d/Rhovanion/defs.h"
#include <stdproperties.h>
#define CAVE_DIR ERE_DIR + "ere3/"
                                 
create_door()
{
    set_door_id("stone_door");
    set_pass_command(({"w","west"}));
    set_door_name(({"gate","stone door","door"}));
    set_other_room(CAVE_DIR + "lm3c3");

    set_lock_name("lock");
          
    set_open(0); 
    set_locked(1);
    set_unlock_command("unlock");
    set_lock_command("lock");
    set_key("small gold key");
    set_door_desc(BS("Its the stone door to this grave chamber.\n"));
 
 
}
