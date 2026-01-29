inherit "/std/door";
#include "/d/Kalad/defs.h"
/* by Korat with header from Aldarion */
create_door()
{
   set_door_id("barracks_door");
   set_pass_command(({"s","south"}));
   set_door_name(({"oak door","door"}));
   set_long("This is a solid door made of oak.\n");
   set_other_room("/d/Kalad/common/central/barracks/barracks4");
   set_fail_pass("The door is closed, maybe you should open it?\n");
   set_open(0);
   set_locked(0);
}
