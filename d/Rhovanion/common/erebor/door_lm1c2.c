inherit "/std/door";

#include "/d/Rhovanion/defs.h"
#include <stdproperties.h>
                                 
create_door()
{
    set_door_id("guarddoorw");
    set_pass_command(({"w","west"}));
    set_door_name(({"iron door","door"}));
    set_other_room(ERE_DIR + "lm1c3");

    set_lock_command("lock");
    set_lock_name("lock");
    set_unlock_command("unlock");

    set_open(0); 
    set_door_desc(BS("It's a massive iron door. In the centre " +
            "there is bronze plaque.\n"));
}
