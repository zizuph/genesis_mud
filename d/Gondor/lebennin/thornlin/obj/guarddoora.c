/*
   Coded by: Boromir May. 17. 1995
   Last edited: MAy. 17. 1995
*/

#include "../locals.h"
inherit STDDOOR;

create_door()
{
    set_door_id("guarddoor1");
    set_pass_command(({"s","south"}));
    set_door_name(({"solid door","door","south door","southern door"}));
    set_door_desc("The door is seems to be strong and steady, it "+ 
      "looks as if it could withstand quite a lot.\n");
    set_closed_desc("The solid door leading out, south of here, is "+ 
      "closed.\n");
    set_open_desc("The solid door leading out, south of here, is open.\n");
    set_fail_pass("You walk right into the closed door.\n");
    set_open_command(({"open","pull"}));
    set_close_command(({"close","push","kick","shut"}));
    set_fail_open("But the door is already open!\n");
    set_fail_close("But the door is already closed!\n");
    set_open_mess(({"pulls the door open.\n",
	"Suddenly the door in the northern building opens.\n"}));
    set_close_mess(({"shuts the door.\n",
	"Suddenly the door in the northern building shuts.\n"}));
    set_other_room(THORN_DIR + "r2a");
    set_open(0);
}

