/*
* Created by: Luther
* Date: 19 August 2001
*
* File: /d/Cirath/ridge/valley/v02a.c
* Comments: Valley outside of Tyr
*/

#pragma strict_types
#pragma save_binary
inherit "/d/Cirath/std/room";
#include "defs.h"

void
create_room()
{

  set_short("Sand Valley");
  set_long("You are standing not far from the entrance to the valley. "
  	+"The valley starts a little to the south.\n");
  	
  	OUTSIDE
  	LIGHT
  	ADD_SUN_ITEM

  add_exit(RIDGE_VALLEY+"v01a.c","north",0,8,0);
  add_exit(RIDGE_VALLEY+"v04.c","south",0,8,0);
  reset_room();
}


