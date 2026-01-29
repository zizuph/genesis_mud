inherit "/std/door";
#include "/d/Gondor/defs.h"

create_door()
{
    ::create_door();
    set_door_id("walldoor");
    set_pass_command(({"se","southeast"}));
    set_door_name(({"iron door","door"}));
    set_other_room(ROH_DIR+"horn/on_walls/h_wall1");
    set_door_desc("An iron door in the outer wall of the keep.\n");
    set_lock_command("lock");
    set_lock_name("lock");
    set_unlock_command("unlock");
    set_open(0);
    set_locked(0);
    set_key(8000350);
}
