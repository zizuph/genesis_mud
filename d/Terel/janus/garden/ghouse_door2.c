/*
    The glass door to the greenhouse
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

    set_door_id("ghouse_door");
    set_pass_command(({"w", "west"}));
    set_long(BS("It appears to be made out of some glasslike material"+
                ". There is a small glass lock in the door. Curiously "+
                "there isn't a single scratch on the door, must be some "+
                "tough glass. \n "));

    set_door_name(({"greenhouse door", "glass door", "door"}));
    set_other_room(GARDENDIR + "garden32");

    set_lock_name("glasslock");
    set_lock_command("lock");
    set_unlock_command("unlock");

/* This door is closed but unlocked */
    set_open(0);
    set_locked(0);
}

