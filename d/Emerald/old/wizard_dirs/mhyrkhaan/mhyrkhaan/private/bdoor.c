inherit "/std/door";
#include "/d/Kalad/aldarion/header.h"

void
create_door()
{
   set_door_id("door");
   set_pass_command(({"e","east"}));
   set_door_name(({"set of golden double doors","doors"}));
   set_other_room("/d/Kalad/mhyrkhaan/bedroom");
   set_fail_pass("The door is closed.\n");
   set_open(0);
}
