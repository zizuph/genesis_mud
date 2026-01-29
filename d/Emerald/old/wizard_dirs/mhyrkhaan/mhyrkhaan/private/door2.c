inherit "/std/door";
#include "/d/Kalad/aldarion/header.h"

void
create_door()
{
   set_door_id("door");
   set_pass_command(({"e","east"}));
   set_door_name(({"grey door","door"}));
   set_other_room("/d/Kalad/sarr/workroom");
   set_fail_pass("The door is closed, maybe you should open it?\n");
   set_open(0);
}
