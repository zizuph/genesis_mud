inherit "/std/door";
#include "/d/Rhovanion/defs.h"
create_door() {
   set_door_id("freddy_door");
   set_pass_command("east");
   set_fail_pass("Ah, no!  Not yet, Danielsan!\n");
   set_door_name("door");
   set_door_desc("This is an old, dry-rotted wooden " +
      "door with an old iron handle, padlock, and a small " +
      "window set with iron bars.\n");
   set_other_room("/d/Rhovanion/common/dungeon1/rooms/cell10.c");
   set_open(0);
   set_locked(1);
   set_open_desc("The door stands open.\n");
   set_closed_desc("The door stands closed.\n");
   set_open_command("open");
   set_open_mess(({"throws the door open.",
            "The door swings aside."}));
   set_fail_open(({"Re-evaluate your course of action," +
            "grasshopper.\n","This'un must be locked!.\n"}));
   set_close_command("close");
   set_close_mess(({"closes the door","You close the door."}));
   set_fail_close("You must first become one with the door " +
      "before you attempt this again.");
   set_lock_name("padlock");
   set_lock_desc("It is a corroded, iron padlock.\n");
   set_lock_command("lock");
   set_lock_mess(({"unlocks the door.","Click!"}));
   set_fail_lock(({"Ah-choo!!!","Oh, no!!! Something's wrong!"}));
   set_unlock_command("unlock");
   set_unlock_mess(({"unlocks the door nervously",
            "Click!"}));
   set_fail_unlock("A dragon leaps out of the lock and " +
      "attacks you!");
   set_key(200);
   set_pick(35);
}
