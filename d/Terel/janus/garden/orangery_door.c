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

   set_key(666000666);
    set_door_id("orangery_door");
    set_long(BS("A crystal clear glass door."+
        "The glass is slightly opaque, and you " +
          "see something that looks like shelves with plants and "+
             "bushes on the other side of the door.\n"));
    set_pass_command(({"w", "west"}));
    set_door_name(({"orangery door", "glass door", "door"}));
    set_other_room(GARDENDIR + "orangery/orang1");

    set_lock_name("glasslock");
    set_lock_command("lock");
    set_unlock_command("unlock");

/* This door is closed and locked */
    set_open(0);
    set_locked(1);
/* 2017-09-18 Malus: Area incomplete, so should not be pickable. */ 
    set_no_pick();
}

