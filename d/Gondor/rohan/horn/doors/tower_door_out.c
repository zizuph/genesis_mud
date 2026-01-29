inherit "/std/door";
#include "/d/Gondor/defs.h"

create_door()
{
    ::create_door();
    set_door_id("towerdoor");
    set_pass_command(({"w","west"}));
    set_door_name(({"iron door","door","tower door"}));
    set_other_room(ROH_DIR+"horn/burg/inner_court3");
    set_door_desc("A sturdy iron door.\n");
    set_lock_command("lock");
    set_lock_name("lock");
    set_unlock_command("unlock");
    set_open(0);
    set_locked(1);
    set_key(8000349);
}
