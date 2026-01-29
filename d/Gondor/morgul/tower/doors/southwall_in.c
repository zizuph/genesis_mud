inherit "/std/door";
#include "/d/Gondor/defs.h"

void
create_door()
{
    ::create_door();
    set_door_id("Morgul_Tower_South_Wall_Gate");
    set_pass_command(({"s","south"}));
    set_door_name(({"iron gate", "gate", "tower gate"}));
    set_door_desc(BSN(
        "A massive iron gate leading out onto the walls of Minas Morgul."));
    set_other_room(MORGUL_DIR + "city/wall/wall14");

    set_open(0);
    set_locked(1);

    set_no_pick();
    
    set_key("_Morgul_Tower_Key");
    set_lock_command("lock");
    set_unlock_command("unlock");
    set_lock_name(({"lock", "keyhole", }));
    set_lock_desc("All that is visible of the lock is a gaping keyhole.\n");
}

