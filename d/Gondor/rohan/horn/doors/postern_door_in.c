inherit "/std/door";
#include "/d/Gondor/defs.h"

create_door()
{
    ::create_door();
    set_door_id("posterndoor");
    set_pass_command(({"s","south"}));
    set_door_name(({"iron door","door"}));
    set_other_room(ROH_DIR+"horn/burg/outer_court6");
    set_door_desc("A small postern door made of iron.\n");
    set_lock_name("lock");
    set_lock_command("lock");
    set_unlock_command("unlock");
    set_open(0);
    set_locked(1);
    set_key(8000345);
}

