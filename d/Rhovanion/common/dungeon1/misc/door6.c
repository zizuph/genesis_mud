inherit "/std/door";
#include "/d/Rhovanion/defs.h"
create_door() {
   set_door_id("_door_of_fred_");
   set_pass_command("west");
   set_fail_pass("First, grasshopper, you must learn the secret " +
      "ways of the door.\n");
   set_door_name("door");
   set_door_desc("This is a sturdy, wooden door with " +
      "a simple lever for a handle.  It leads west\n");
   set_other_room("/d/Rhovanion/common/dungeon1/rooms/guard17.c");
   set_open(0);
   set_locked(0);
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
}
