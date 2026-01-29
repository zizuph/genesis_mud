#pragma strict_types

inherit "/std/door.c";

#include "/d/Gondor/defs.h"

public void
create_door()
{
    ::create_door();
    set_door_id("edoras_inn");
    set_pass_command(({"e","east"}));
    set_door_name(({"wooden door","door"}));
    set_door_desc("A heavy wooden door leading into the inn with a large sign upon it.\n");
    set_other_room(EDORAS_DIR + "DBGstallion");
    set_lock_command("lock");
    set_lock_name("lock");
    set_unlock_command("unlock");
    set_open(0);
    set_locked(0);
    set_pick(40);
    set_key("_sleeping_stallion_key");
}
