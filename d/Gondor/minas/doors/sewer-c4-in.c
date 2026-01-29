inherit "/std/door";

#include "/d/Gondor/defs.h"

void
create_door()
{
    set_other_room(MINAS_DIR + "tcrc4");
    set_door_id("MT_sewer_crc4");
    set_door_name(({"metal gate leading east", 
        "metal gate", "gate", "door", }));
    set_door_desc(BSN(
        "The door is set into the rock of the east wall. It is a "
      + "simple metal gate, only the keyhole interrupting the smooth "
      + "surface."));

    set_open(0);

    set_pass_command(({"east", "e"}));

    set_locked(1);
    set_key("MT_sewer_crc4");
    set_lock_command("lock");
    set_unlock_command("unlock");
    set_lock_name(({"lock", "keyhole", }));
    set_lock_desc("All that is visible of the lock is a small keyhole.\n");
}

