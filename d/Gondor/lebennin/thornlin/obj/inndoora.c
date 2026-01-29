/*
   Door for inn in Thornlin.
   Thanks to Jeremiah

   Coded by: Boromir Apr. 29. 1995
   Last edited: Apr. 29. 1995
*/

#include "/d/Gondor/defs.h"
#include "../locals.h"
inherit STDDOOR;

void
create_door()
{
    set_door_id("inndoor1");
    set_pass_command(({"e","east"}));
    set_door_name(({"oak tree door","door","oak door","tree door",
	"eastern door","east door"}));
    set_door_desc("It is a weather-beaten oak door, it seems "+
      "to have been used often.\n");
    set_closed_desc("The eastern door is closed, making the temperature and "+
      "the air in here more cosy.\n");
    set_open_desc("The eastern door is open, letting some fresh air enter "+
      "the room.\n");
    set_fail_pass("You walk right into the closed door.\n"+
      "Have you been drinking to much ?\n");
    set_open_command(({"open","pull"}));
    set_close_command(({"close","push","kick","shut"}));
    set_fail_open("But the door is already open!\n"+
      "Have you been drinking to much ?\n");
    set_fail_close("But the door is already closed!\n"+
      "Have you been drinking to much ?\n");
    set_open_mess(({"pulls the door open.\n",
	"Suddenly the door into the inn opens.\n"}));
    set_close_mess(({"shuts the door.\n",
	"Suddenly the door to the inn shuts.\n"}));
    set_other_room(THORN_DIR + "r2a");
    set_open(0);
}



