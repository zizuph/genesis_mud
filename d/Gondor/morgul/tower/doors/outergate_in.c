inherit "/std/door";
#include "/d/Gondor/defs.h"

void
create_door()
{
    ::create_door();

    set_door_id("Morgul_Tower_Outer_Gate");
    set_pass_command(({"ne","northeast"}));
    set_door_name(({"iron gate","gate", "outer gate"}));
    set_door_desc(BSN(
        "A massive iron gate. This is the outer gate of the Morgul Tower, " +
        "leading out onto the streets of Minas Morgul."));
    set_other_room(MORGUL_DIR + "city/mmr3");

    set_open(0);
    set_locked(0);
    set_key("_Morgul_Tower_Key");

    set_no_pick();
    
    set_lock_command("lock");
    set_unlock_command("unlock");
    set_lock_name(({"lock", "keyhole", }));
    set_lock_desc("All that is visible of the lock is a gaping keyhole.\n");
}

