/* front door for the icewall mansion created by Stevenson
*/
#include "/d/Krynn/icewall/local.h"
#include "/d/Krynn/common/defs.h"
inherit "/std/door";

create_door() {
   ::create_door();
   set_door_id("housedoor");
   set_other_room(ICE_CAST1_R + "main_hall");
   set_open_command("open");
   set_pass_command(({"n","north"}));
   set_door_name(({"massive oaken door","door"}));
   set_fail_pass("You bump your nose as you run into the door.\n");
   set_open_mess(({"pushes the oaken door open.\n",
            "The oaken door suddenly opens, sending gusts of cold "
            + "wind into the room.\n"}));
   set_close_mess(({"forces the door shut.\n",
            "The oaken door slams shut with a loud bang.\n"}));
   set_open(0);
   set_locked(0);
}
