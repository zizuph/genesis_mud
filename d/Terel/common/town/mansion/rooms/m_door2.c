/*
    A wooden door for the master's room. Mortricia 920909
 */
inherit "/std/door";

#include "/d/Terel/common/terel_defs.h"

create_door() {
    ::create_door();

    set_door_id("master_door");
    set_pass_command(({"e", "east"}));
    set_door_name(({"door", "oak door"}));
    set_other_room(MANSION + "rooms/mast_room");
    set_lock_name("lock");
    set_lock_command("lock");
    set_unlock_command("unlock");

/* This door is closed and locked */
    set_open(0);
    set_locked(1);
}
