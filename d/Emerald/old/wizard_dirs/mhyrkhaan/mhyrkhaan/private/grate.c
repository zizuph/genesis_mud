inherit "/d/Kalad/std/door";
#include "/d/Kalad/defs.h"

void
create_door()
{
   set_door_id("grate");
   set_pass_command(({"d","down"}));
   set_door_name("grate");
   set_door_desc("This is a steel grate");
   set_other_room("/d/Kalad/mhyrkhaan/testroom");
   set_fail_pass("The grate is closed.\n");
   set_open(0);
}
