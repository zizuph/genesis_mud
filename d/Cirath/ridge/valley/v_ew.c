/*
* Created by: Luther
* Date: 19 August 2001
*
* File: /d/Cirath/ridge/valley/v_ew.c
* Comments: Green building in the ruins of the valley
*/

#pragma strict_types
#pragma save_binary

inherit "/d/Cirath/std/room";
#include "defs.h"
#include "/d/Cirath/common/teamer.h"

void
reset_room()
{
    bring_room_team(RIDGE_NPC+"v_skull.c", 1, 0);
}

void
create_room()
{
  	add_prop(ROOM_I_INSIDE, 1);
	set_short("Inside the green building");
  	set_long("You are standing inside the green building. There isn't much light "
  		+"except for what comes throught the window. The room is very plain "
  		+"with little furniture and a door at the front of the building. "
  		+"The back of the building is dark, almost an unatural darkness.\n");

  	add_item("darkness", "Looking into the darkness you can make out a hole in the "
  		+"floor. You start to take a better look and you think you can enter the "
  		+"hole.\n");

	add_item("hole", "At the back of the building there is a hole in the floor.\n");

  	add_item("door", "The door is solid stone.\n");
	
	add_cmd_item("door", "open", "The door is locked.\n");	
	
  	add_exit(RIDGE_VALLEY+"ruin_1.c","out",0,0,0);  	
	reset_room();
	
	
}


void
init()
{
    ::init();
    add_action("enter_hole", "enter");
}

int
enter_hole(string str)
{
	object guard = present ("guard", TO);
   	notify_fail("Enter what?\n");
    	if(str!="hole")
        	return 0;
       	
  	if (str == "hole" && (!objectp(guard)))
     	{
        TP->catch_msg("You enter the hole.\n");
        TP->move_living("climbing down the hole", "/d/Cirath/ridge/valley/v_cave.c",1);
               
        return 1;
        }
        else
      	{
        TP->catch_msg("The skeleton laughs at you as you find him standing "
        	+"in front of you.\n");	
        return 1;
	}   

    return 0;
}