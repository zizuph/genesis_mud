/*
    A wooden closet door. Mortrica 920909
 */
inherit "/std/door";

#include "/d/Terel/common/terel_defs.h"

create_door() {
    ::create_door();

    set_door_id("clos_door");
    set_pass_command(({"n", "north"}));
    set_door_name(({"closet door", "north door"}));
    set_other_room(MANSION + "chapel/wall_room");
    set_lock_name("lock");
    set_lock_command("lock");
    set_unlock_command("unlock");

/* This door is closed and unlocked */
    set_open(0);
    set_locked(0);
}
