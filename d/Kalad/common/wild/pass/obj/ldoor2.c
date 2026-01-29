inherit "/std/door";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_door()
{
   set_door_id("ldoor");
   set_pass_command(({"nw","northwest"}));
   set_door_name(({"stone door","door"}));
   set_door_desc("A large rectangular slab of stone that sits squarely "+
      "in the northwest, blocking the way entirely.\n");
   set_other_room("/d/Kalad/common/wild/pass/desert/salt/l6");
   set_fail_pass("The door is closed, maybe you should open it?\n");
   set_open(0);
   set_str(75);
}
