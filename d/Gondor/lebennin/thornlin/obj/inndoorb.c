/*
   Door for inn in Thornlin.
   Thanks to Jeremiah

   Coded by: Boromir Apr. 29. 1995
   Last edited: Apr. 29. 1995
*/

#include "../locals.h"
inherit STDDOOR;

create_door()
{
    set_door_id("inndoor1");
    set_pass_command(({"w","west"}));
    set_door_name(({"oak tree door","door","oak door","tree door","inn door"}));
    set_door_desc("It is a weather-beaten oak door, it seems "+
      "to have been used often.\n");
    set_closed_desc("The oak door to the west is closed, sealing the "+ 
      "entrance to the inn. ");
    set_open_desc("The inn's oak door to the west is open. "+
      "Thick smoke pours out from the inn. ");
    set_fail_pass("You walk right into the closed door.\n");
    set_open_command(({"open","push","kick"}));
    set_close_command(({"close","pull"}));
    set_fail_open("But the door is already open!\n");
    set_fail_close("But the door is already closed!\n");
    set_open_mess(({"pushes the door open.\n",
	"Suddenly the door leading out opens.\n"+
	"Fresh air flows in.\n"}));
    set_close_mess(({"shuts the door.\n",
	"Suddenly the door leading out shuts.\n"}));

    set_other_room(THORN_DIR + "inn");
    set_open(0);
}
