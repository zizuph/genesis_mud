inherit "/std/door";
#include "/d/Kalad/defs.h"

#pragma strict_types

void
create_door()
{
   set_door_id("capt2door");
   set_pass_command(({"n","north"}));
   set_door_name(({"heavy wooden door","wooden door","door","heavy door"}));
   set_other_room("/d/Kalad/common/sewers/lizards_lair/ll26.c");
   set_fail_pass("The door is closed, maybe you should open it?\n");
   set_open(0);
   set_str(50);
}
