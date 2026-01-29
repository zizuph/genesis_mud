/*
* Created by: Luther
* Date: 19 August 2001
*
* File: /d/Cirath/ridge/valley/v_gb.c
* Comments: Grey building in the ruins of the valley
*/

#pragma strict_types
#pragma save_binary

inherit "/d/Cirath/std/room";
#include "defs.h"
#include "/d/Cirath/common/mobber.h"

void
reset_room()
{  
}

void
create_room()
{
  	add_prop(ROOM_I_INSIDE, 1);
	set_short("Inside the grey building");
  	set_long("You are standing inside the grey building. There isn't much light "
  		+"except for what comes throught the door. The room is very plain "
  		+"with little furniture and a door at the front of the building.\n");

  	add_item("door", "The door is missing.\n");	
  	
  	add_item("furniture", "The furniture has not been used in a long time. "
  		+"Most of them are broken and unusable. You do not find "
  		+"anything worth salvaging.\n");
  		
  	add_cmd_item("furniture", "get", "None of the furniture is worth taken.\n");
  	
	
  	add_exit(RIDGE_VALLEY+"ruin_1.c","out",0,0,0);
  	reset_room();
}


