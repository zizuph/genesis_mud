/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/nomads/r04.c
* Comments: edited by Luther Oct. 2001
*/

inherit "/std/room";
#include "defs.h"

void
create_room()
{
  set_short("On a desert path");  
  set_long("You are standing on a small path in a canyon. A stream, that flows in east-"+
           "west direction, makes some vegetation to grow here in the desert.\n");  

  add_item("path","It's small and narrow.\n");
  add_item("canyon","It's deep and impressive.\n");
  add_item("desert","You get thirsty just thinking on it...\n");
  add_item("stream","The water looks lovely!\n");
  add_item("water","What shouldn't you give to dive into that water!\n");
  add_item("vegetation","Just some low bushes and grass, but better than nothing.\n");

  OUTSIDE;
  WATER;

  //add_exit(NOMAD+"r05","northwest", 0, 1);
  add_exit(NOMAD+"r03","south", 0, 1);
  reset_room();
}

void
init()
{
  ::init();
  add_action("diver","dive");
}

int diver(string str)
{
	notify_fail("Dive into what?\n");
    	if(str!="into water")
        	return 0;
  if (str=="into water" && TP->query_skill(SS_SWIM) > 35)
  {
    write("You dive into the stream.\n");
    TP->move_living("",NOMAD+"w1");
    return 1;
  }
  return 0;
}
