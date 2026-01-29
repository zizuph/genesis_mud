/*
 * Door inside Cair Andros
 * /d/Gondor/anorien/cairandros/obj/fort_door_in_ne.c
 *
 * Varian 2016
 */

#pragma strict_types

inherit "/std/door";

#include "../../defs.h"

void
create_door()
{
    set_other_room(CAIRANDROS_DIR + "bar2");
    set_door_id("cairadros_fort_ne");
    set_door_name(({"oak door", "sturdy oak door", "door", "sturdy door",
        "wood door", "sturdy wood door"}));
    set_door_desc("This is a heavy looking door, made entirely out of " +
        "sturdy oak planks. The door appears to be in very good condition, " +
        "and a strong iron lock on the door means it can be locked " +
        "for security.\n");
    set_lock_name(({"lock", "iron lock"}));
    set_lock_desc("This iron lock looks like it is very strong and in " +
        "good condition. You would certainly need the matching key to " +
        "lock or unlock this door.\n");
    set_unlock_command("unlock");
    set_lock_command("lock");
    set_pass_command("south");
    set_open(0);
    set_locked(1);
    set_key("cairandros_fort");
    set_str(50);
}

void
reset_door()
{
    other_door->reset_door();
}