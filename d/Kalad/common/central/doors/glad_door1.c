inherit "/std/door";
#include "/d/Kalad/defs.h"
/* by Korat with header from Aldarion */
create_door()
{
   set_door_id("glad_door");
   set_pass_command(({"sw","southwest"}));
   set_door_name(({"redwood door","door"}));
   set_long ("This is a solid door made of redwood with "+
      "no fancy decorations on it except a plaque attached "+
      "in the center of it.\n");
   set_other_room("/d/Kalad/common/central/arena/under_arena12");
   set_fail_pass("The door is closed, maybe you should open it?\n");
   set_open(0);
   set_locked(0);
}
