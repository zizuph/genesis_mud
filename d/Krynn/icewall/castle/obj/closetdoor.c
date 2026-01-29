#include "/d/Krynn/icewall/local.h"
inherit "/std/door";

create_door()
{
   ::create_door();
   
   set_door_id("closetdoor");
   set_pass_command(({"e", "east"}));
   set_fail_pass("You try to walk into the door and hit your nose.\n");
	set_door_name(({"door","small door","wooden door","closet door"}));
   set_other_room("/d/Krynn/icewall/castle/floor2/closet.c");
   set_lock_command("lock");
   set_lock_name("keyhole");
   set_lock_desc("You see a small keyhole.\n");
   set_unlock_command("unlock");
   set_door_desc("It is a closet door with a keyhole under the knob.\n");
   set_open(0);
   set_locked(1);
}
