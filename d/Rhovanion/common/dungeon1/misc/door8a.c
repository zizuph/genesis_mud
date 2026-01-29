inherit "/std/door";
#include "/d/Rhovanion/defs.h"
create_door() {
   set_door_id("door_of_fred");
   set_pass_command("east");
   set_fail_pass("First, grasshopper, you must learn the secret " +
      "ways of the door.\n");
   set_door_name("door");
   set_door_desc("An old rotted, wooden door with " +
      "a leather strip for a handle.  It leads east.\n");
   set_other_room("/d/Rhovanion/common/dungeon1/rooms/cell15.c");
   set_open(0);
   set_locked(0);
   set_open_desc("The east door stands open.\n");
   set_closed_desc("The east door stands closed.\n");
   set_open_command("open");
   set_open_mess(({"pulls the door open.","The door shuts."}));
   set_fail_open(({"Your keen mind detects an error.",
            "Re-evaluate your course of action, grasshopper.\n"}));
   set_close_command("close");
   set_close_mess(({"closes the door","You close the door."}));
   set_fail_close("You must first become one with the door " +
      "before you attempt this again.");
}
