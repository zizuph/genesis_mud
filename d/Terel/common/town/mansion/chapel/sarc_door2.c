/*
    A marble sarcophagus door. Mortricia 920906
 */
inherit "/std/door";

#include "/d/Terel/common/terel_defs.h"

create_door() {
    ::create_door();

    set_door_id("sarc_door");
    set_pass_command(({"u", "up"}));
    set_door_name(({"sarcophagus lid", "marble lid", "lid"}));
    set_other_room(MANSION + "chapel/chapel");

    set_lock_name("lock");
    set_lock_command("lock");
    set_unlock_command("unlock");

/* This door is closed and unlocked */
    set_open(0);
    set_locked(0);
}
