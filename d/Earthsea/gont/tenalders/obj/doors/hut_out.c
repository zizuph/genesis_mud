inherit "/std/door";

#include "defs.h"

public void
create_door()
{
    set_door_id("_hut_");
    set_pass_command(({"n", "north"}));
    set_door_name(({"wooden door","door"}));
    set_lock_desc("A brass lock in the shape of a skull "+
      "with an open mouth for the keyhole.\n");
    set_open(0);
    set_lock_command("lock");
    set_unlock_command("unlock");
    set_lock_name("lock");
    set_locked(1);
    set_key(BRASS_KEY);
    set_other_room("/d/Earthsea/gont/tenalders/high_fall/hut");
}
