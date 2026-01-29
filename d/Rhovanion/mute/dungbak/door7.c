inherit "/std/door";
#include "/d/Rhovanion/defs.h"
create_door() {
   set_door_id("_door_of_fred_");
   set_pass_command("west");
   set_fail_pass("First, grasshopper, you must learn the secret " +
      "ways of the door.\n");
   set_door_name("door");
   set_door_desc("This is a strong, wooden door with " +
      "an old, corroded brass handle and lock just below " +
      "it.\n");
   set_other_room("/d/Rhovanion/mute/dungeon1/guard10.c");
   set_open(0);
   set_locked(1);
   set_open_desc("The west door stands open.\n");
   set_closed_desc("The west door stands closed.\n");
   set_open_command("open");
   set_open_mess(({"throws the door open.",
            "The door swings aside."}));
   set_fail_open(({"Your keen mind detects an error.",
            "Re-evaluate your course of action, grasshopper.\n"}));
   set_close_command("close");
   set_close_mess(({"closes the door","You close the door."}));
   set_fail_close("You must first become one with the door " +
      "before you attempt this again.");
   set_lock_name("lock");
   set_lock_desc("It is an old, corroded brass lock.\n");
   set_lock_command("lock");
   set_lock_mess(({"unlocks the door.","Click!"}));
   set_fail_lock(({"Ah-choo!!!","Oh, no!!! Something's wrong!"}));
   set_unlock_command("unlock");
   set_unlock_mess(({"unlocks the door nervously",
            "Click!"}));
   set_fail_unlock("A dragon leaps out of the lock and " +
      "attacks you!");
   set_key(100);
   set_pick(75);
   set_lock_name("lock");
}
