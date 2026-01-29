inherit "/std/door";

#include "/d/Gondor/defs.h"

void
create_door()
{
    set_other_room(ITH_DIR + "emyn-arnen/rrd1");
    set_door_id("Emyn-Arnen_Palace_Kitchen_Gate");
    set_door_name(({"wooden gate", "gate"}));
    set_door_desc(BSN("The wooden gate leads northeast out of " +
        "the kitchen and the building. It is well crafted, and " +
        "the wooden planks that make up the gate have been " +
        "reinforced by broad iron bands."));
    set_lock_name(({"lock", "iron lock"}));
    set_lock_desc(BSN("The gate can be locked by a large iron lock. " +
        "Judging from the size of the key hole, the key must be rather " +
        "large, too."));
    set_unlock_command("unlock");
    set_lock_command("lock");

    set_pass_command("northeast");

    set_open(0);
    set_locked(1);
    set_key("Emyn-Arnen_Kitchen_Gate");

    set_str(20);
}

void
reset_door()
{
    other_door->reset_door();
}
