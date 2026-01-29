inherit "/d/Kalad/std/door/newdoor.c";
#include "/d/Kalad/defs.h"
/* by Korat with header from Aldarion */
create_door()
{
   set_door_id("duergar_door");
   set_pass_command(({"w","west"}));
   set_door_name(({"redwood door","door"}));
   set_long ("This is a solid door made of redwood with "+
      "no fancy decorations on it.\n");
   set_other_room("/d/Kalad/common/wild/pass/dwarf/guild/entrance");
   set_fail_pass("The door is closed, maybe you should open it?\n");
   set_open(0);
   set_locked(0);
}
