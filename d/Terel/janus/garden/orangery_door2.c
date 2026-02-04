/*
    The glass door to the orangery
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

    set_door_id("orangery_door");
    set_pass_command(({"e", "east"}));
    set_door_name(({"orangery door", "glass door", "door"}));
    set_long(BS("A crystal clear glass door." +
          "The glass is slightly opaque, and you" +
              "see something that looks like a garden on the other "+
             "side of the door. \n"));
    set_other_room(GARDENDIR + "garden22");

    set_lock_name("crystallock");
    set_lock_command("lock");
    set_unlock_command("unlock");

/* This door is closed and locked */
    set_open(0);
    set_locked(1);
}

