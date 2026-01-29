/*
* Created by: Luther
* Date: 19 August 2001
*
* File: /d/Cirath/ridge/valley/v_cave1.c
* Comments: Cave underneath the ruins
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
  	set_long("You are standing in a cave underneath the building.\n");

  	add_item("cave", "The cave is very plain. There is a grate in one of the walls.\n");  	

	add_item("grate", "Looking throught the grate you see a dark room.\n");

	add_cmd_item("grate", "open", "You try to open the grate but it won't budge.\n");

  	add_exit(RIDGE_VALLEY+"v_cave.c","southeast",0,0,1);

}


