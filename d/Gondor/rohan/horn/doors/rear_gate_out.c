inherit "/std/door";
#include "/d/Gondor/defs.h"

create_door()
{
    ::create_door();
    set_door_id("reargate");
    set_pass_command(({"s","south"}));
    set_door_name(({"rear-gate","gate","rear gate"}));
    set_other_room(ROH_DIR+"horn/gorge/stairs");
    set_door_desc("The rear gate of the keep. It's made of timber.\n");
    set_lock_command("lock");
    set_lock_name("lock");
    set_lock_desc("A sturdy lock.\n");
    set_unlock_command("unlock");
    set_open(0);
    set_locked(0);
    set_key(8000348);
}
