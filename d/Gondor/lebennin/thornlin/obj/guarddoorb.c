/*
   Coded by: Boromir May. 17. 1995
   Last edited: MAy. 17. 1995
*/

#include "../locals.h"
inherit STDDOOR;

create_door()
{
    set_door_id("guarddoor1");
    set_pass_command(({"n","north"}));
    set_door_name(({"solid door","door","north door","northern door"}));
    set_door_desc("The door is seems to be strong and steady, it "+ 
      "looks as if it could withstand quite a lot.\n");
    set_closed_desc("There is a closed solid door leading north into the "+ 
      "important looking building.\n");
    set_open_desc("A solid door leading north into the important looking "+
      "building stands open.\n");
    set_fail_pass("You walk right into the closed door.\n");
    set_open_command(({"open","push","kick"}));
    set_close_command(({"close","pull","shut"}));
    set_fail_open("But the door is already open!\n");
    set_fail_close("But the door is already closed!\n");
    set_open_mess(({"pulls the door open.\n",
	"Suddenly the door leading out, south of here, opens.\n"}));
    set_close_mess(({"shuts the door.\n",
	"Suddenly the door leading out, south of here, shuts.\n"}));
    set_other_room(THORN_DIR + "guardhouse");
    set_open(0);
}
