inherit "/std/door";
#include "/d/Kalad/defs.h"
/* by Korat with header from Aldarion */
create_door()
{
   set_door_id("citadel_door");
   set_pass_command(({"se","southeast"}));
   set_door_name(({"huge bronze gate","gate"}));
   set_long("This gate is huge, with intricate engravings "+
      "made in the thick layers of bronze that covers the "+
      "kernel of hard oak. If someone decided to close and "+
      "lock it, you would need an army to break it down.\n");
   set_other_room("/d/Kalad/common/central/citadel/entrance");
   set_fail_pass("The gate is closed. Maybe you should open it?\n");
   set_open(0);
   set_locked(0);
}
