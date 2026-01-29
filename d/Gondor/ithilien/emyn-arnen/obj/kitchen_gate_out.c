inherit "/std/door";

#include "/d/Gondor/defs.h"

void
create_door()
{
    set_other_room(ITH_DIR + "emyn-arnen/palace/kitchen");
    set_door_id("Emyn-Arnen_Palace_Kitchen_Gate");
    set_door_name(({"wooden gate", "gate"}));
    set_door_desc(BSN("The wooden gate leads southwest into " +
        "the large building. It is well crafted, and the wooden " +
        "planks that make up the gate have been reinforced by broad " +
        "iron bands."));
    set_lock_name(({"lock", "iron lock", "key hole"}));
    set_lock_desc(BSN("The lock must be on the other side of the gate. " +
        "All one can see from here is a large key hole. " +
        "Judging from ts size, the key must be rather large, too."));
    set_unlock_command("unlock");
    set_lock_command("lock");

    set_pass_command("southwest");

    set_open(0);
    set_locked(1);
    set_pick(60);
    set_key("Emyn-Arnen_Kitchen_Gate");

    set_str(20);
}

void
reset_door()
{
    if (open_status)
    {
        do_close_door("The door closes.\n");
        other_door->do_close_door("The door closes.\n");
    }
    do_lock_door("");
    other_door->do_lock_door("");
}

