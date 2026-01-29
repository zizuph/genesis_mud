/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/nomads/w03.c
* Comments: edited by Luther Oct. 2001
*/

inherit "/std/room";
#include "defs.h"

void
create_room()
{
  set_short("In a stream");  
  set_long("This is a stream. The water is cold and refreshing. A large wall stops "+
           "the stream west, and east, the stream continues.\n");  

  add_item("stream","This stream is rather small, but it's nice to swim in\n");
  add_item("water","The water has the right temperature.\n");
  add_item("wall","As you look at the wall, you realizes that the water must pass "+
           "somewhere beneath the surface.\n");
  add_item("surface","You examine the surface and beneath it, you discover a way through "+
           "the wall, a hole which you could dive through.\n");
           
  OUTSIDE;
  WATER;
  
  reset_room();
}

void
init()
{
  ::init();
  add_action("swimmer","swim");
  add_action("diver","dive");
}

int swimmer(string str)
{
	notify_fail("Swim where?\n");
    	if(str!="east")
        	return 0;
  if (str=="east" && TP->query_skill(SS_SWIM) > 35)
  {
    write("You swim east.\n");
    TP->move_living("swimming",NOMAD+"w4");
    return 1;
  }
  return 0;
}

int diver(string str)
{
	notify_fail("Dive where?\n");
    	if(str!="through hole")
        	return 0;
  if (str=="through hole" && TP->query_skill(SS_SWIM) > 35)
  {
    write("You catch your breath and dive through the hole.\n");
    TP->move_living("",NOMAD+"w2");
    return 1;
  }
  return 0;
}
