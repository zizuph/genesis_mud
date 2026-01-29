inherit "/std/door";
#include "/d/Rhovanion/defs.h"
create_door() {
   set_door_id("fred_door");
   set_pass_command("south");
   set_fail_pass("Ah, no!  Not yet, Danielsan!\n");
   set_door_name("south door");
   set_door_desc("An old rotted, wooden door with " +
      "a leather strip for a handle.  It leads north.\N");
   set_other_room("/d/Rhovanion/mute/dungeon1/cell15.c");
   set_open(0);
   set_locked(0);
   set_open_desc("The south door stands open.\n");
   set_closed_desc("The south door stands closed.\n");
   set_open_command("open");
   set_open_mess(({"pulls the door open.","The door creaks open."}));
   set_fail_open(({"Your keen mind detects an error.",
            "Re-evaluate your course of action, Danielsan.\n"}));
   set_close_command("close");
   set_close_mess(({"pushes the door shut.","You shut the door."}));
   set_fail_close("You must first become one with the door " +
      "before you attempt this again.");
}
