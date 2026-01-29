inherit "/std/door";

#include "defs.h"

public void
create_door()
{
    set_door_id("_crystal_");
    set_pass_command(({"d", "down"}));
    set_door_name(({"crystal door", "door"}));
    set_lock_desc("You see a keyhole set into the hard crystal.\n");
    set_door_desc("This is a beautiful yet strange door made "+
        "of solid rock crystal.\n");
    set_open(0);
    set_lock_command("lock");
    set_unlock_command("unlock");
    set_lock_name("lock");
    set_locked(1);
    set_key(CRYSTAL_KEY);
    set_other_room("/d/Earthsea/gont/tenalders/high_fall/caves/cave2");
}
