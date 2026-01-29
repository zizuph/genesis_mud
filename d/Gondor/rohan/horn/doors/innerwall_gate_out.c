inherit "/std/door";
#include "/d/Gondor/defs.h"

create_door()
{
    ::create_door();
    set_door_id("innerwallgate");
    set_pass_command(({"s","south"}));
    set_door_name(({"sturdy gate","gate"}));
    set_other_room(ROH_DIR+"horn/burg/outer_court4");
    set_door_desc("The gate between the inner and outer courtyard. It looks "+
                  "sturdy.\n");
    set_lock_command("lock");
    set_lock_name("lock");
    set_unlock_command("unlock");
    set_open(0);
    set_locked(0);
    set_key(8000347);
}
