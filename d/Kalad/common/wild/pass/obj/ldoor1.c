inherit "/std/door";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_door()
{
   set_door_id("ldoor");
   set_pass_command(({"se","southeast"}));
   set_door_name(({"stone door","door"}));
   set_door_desc("A large rectangular shaped slab of rock that blocks "+
      "the way to the southeast.\n");
   set_other_room("/d/Kalad/common/wild/pass/desert/salt/l7");
   set_fail_pass("The door is closed, maybe you should open it?\n");
   set_open(0);
   set_str(75);
}
