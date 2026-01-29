inherit "/std/door";

#include "/d/Gondor/defs.h"
#include "/d/Gondor/morgul/cellar/cellar_defs.h"

void
create_door()
{
    ::create_door();

    set_door_id("Morgul_Cellar_Exit");
    set_pass_command(({"e","east"}));
    set_door_name(({"steel gate", "gate", "large steel gate", }));
    set_door_desc(BSN("The large gate is made from steel. The surface of "
      + "the gate is plain and smooth and without any ornaments, broken "
      + "only by the keyhole."));
    set_other_room(CELLAR_DIR + "pass_1e1");
    set_lock_name(({"lock", "keyhole", }));
    set_lock_desc("All that is visible of the lock is a gaping keyhole.\n");
    set_locked(0);
    set_open(0);

    set_no_pick();

    set_key("_Morgul_Tower_Key");
    set_lock_command("lock");
    set_unlock_command("unlock");
}

