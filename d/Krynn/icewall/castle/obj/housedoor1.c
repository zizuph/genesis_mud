/* front door for the icewall mansion created by Stevenson
*/
#include "/d/Krynn/icewall/local.h"
#include "/d/Krynn/common/defs.h"
inherit "/std/door";

create_door() {
   ::create_door();
   set_door_id("housedoor");
   set_other_room(ICE_OUT+"up_stairs3");
   set_pass_command(({"s","south"}));
   set_door_name(({"massive oaken door","door"}));
	set_fail_pass("From behind you hear snickers as you walk into the door.\n");
   set_open_mess(({"opens the door.\n\nA very cold wind enters the room.\n",
            "The oaken door slowly swings open.\n"}));
   set_close_mess(({"struggles with the wind as he closes "
            + "the oaken door.\n","The oaken door slams shut.\n"}));
   set_open(0);
   set_locked(0);
}
