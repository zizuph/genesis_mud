inherit "/std/door";
#include "/d/Kalad/defs.h"
/* by Korat with header from Aldarion */
create_door()
{
   set_door_id("bell_door");
   set_pass_command(({"s","south"}));
   set_door_name(({"small oak door","door"}));
   set_long("This small oak door looks like its made to keep "+
      "out something else than people, since it there is no "+
      "lock on it.\n");
   set_other_room("/d/Kalad/common/central/citadel/bell1");
   set_fail_pass("The doors are closed. Maybe you should open them?\n");
   set_open(0);
   set_locked(0);
}
