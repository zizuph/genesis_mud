/*
* Created by: Luther
* Date: 19 August 2001
*
* File: /d/Cirath/ridge/valley/v_cave.c
* Comments: Cave underneath the ruins
*/


inherit "/d/Cirath/std/room";
#include "defs.h"

void
create_room()
{
  	add_prop(ROOM_I_INSIDE, 1);
	add_prop(ROOM_I_LIGHT, 0);
  	set_short("Underground");
  	set_long("You are standing in a cave underneath the building.\n");

  	add_item("cave", "The cave is very plain.\n");  	

  	add_exit(RIDGE_VALLEY+"v_ew.c","up",0,0,1);
  	add_exit(RIDGE_VALLEY+"v_cave1.c","northwest",0,0,1);
	reset_room();
}


