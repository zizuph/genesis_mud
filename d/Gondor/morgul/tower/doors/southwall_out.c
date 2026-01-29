inherit "/std/door";
#include "/d/Gondor/defs.h"

void create_door()
{
    ::create_door();
    set_door_id("Morgul_Tower_South_Wall_Gate");
    set_pass_command(({"n","north"}));
    set_door_name(({"iron gate", "gate", "tower gate"}));
    set_door_desc(BSN(
        "A massive iron gate leading into the Morgul Tower."));
    set_other_room(MORGUL_DIR + "tower/tower_1s");
    set_open(0);
    set_locked(1);

    set_no_pick();
    
    set_lock_name(({"lock", "keyhole", }));
    set_lock_desc("There is neither a lock nor a keyhole visible on this side of the gate.\n");
}
