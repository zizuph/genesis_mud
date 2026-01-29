inherit "/std/door";

#include "/d/Rhovanion/defs.h"
#include <stdproperties.h>
#define CAVE_DIR ERE_DIR + "ere1/"                                

create_door()
{
    set_door_id("gate");
    set_pass_command(({"e","east"}));
    set_door_name(({"iron gate","gate"}));
    set_other_room(CAVE_DIR + "lm1c77");

    set_lock_command("lock");
    set_lock_name("lock");
    set_unlock_command("unlock");

    set_open(0); 
}
