/*
* Created by: Luther
* Date: 19 August 2001
*
* File: /d/Cirath/ridge/valley/v_fountain.c
* Comments: Inside the fountain of the ruins
*/

#pragma strict_types
#pragma save_binary

inherit "/d/Cirath/std/room";
#include "defs.h"

void
create_room()
{
  	add_prop(ROOM_I_INSIDE, 1);
	add_prop(ROOM_I_LIGHT, 0);
  	set_short("Underground");
  	set_long("You are standing in the bottom of the fountain.\n");

  	add_item("fountain", "The is no water down here. The well must have dried "
  		+"up a long time ago. In one of the walls is a grate.\n");  	

	add_item("grate", "Looking throught the grate you see a dark room.\n");	

	add_cmd_item("grate", "open", "You try to open the grate but it won't budge.\n");

  	add_exit(RIDGE_VALLEY+"ruin_1.c","up",0,0,1);
  	

}


