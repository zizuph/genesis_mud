inherit "/std/door";
#include "/d/Gondor/defs.h"

create_door()
{
    ::create_door();
    set_door_id("posterndoor");
    set_pass_command(({"n","north"}));
    set_door_name(({"iron door","door","postern door"}));
    set_other_room(ROH_DIR+"horn/gorge/n_path4");
    set_door_desc("A small postern door made of iron.\n");
    set_lock_command("lock");
    set_lock_name("lock");
    set_unlock_command("unlock");
    set_open(0);
    set_locked(1);
    set_pick(80);
    set_key(8000345);
}
