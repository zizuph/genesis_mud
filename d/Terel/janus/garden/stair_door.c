/*
    The silver gate to my manor
    Janus 930305
 */
inherit "/std/door";

#include "/d/Terel/common/terel_defs.h"

#define BS(message)    break_string(message, 70)
#define TP             this_player()
#define TO             this_object()
#define GARDENDIR JANUSDIR + "garden/"

create_door() {
    ::create_door();

    set_key(999000999);
    set_door_id("stair_door");
    set_pass_command(({"n", "north"}));
    set_door_name(({"silver gate", "gate"}));
    set_other_room(GARDENDIR + "garden15");

    set_lock_name("silverlock");
    set_lock_command("lock");
    set_unlock_command("unlock");

/* This door is closed but locked */
    set_open(0);
    set_locked(1);
}

