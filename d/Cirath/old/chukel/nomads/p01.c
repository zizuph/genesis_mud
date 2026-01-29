/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/nomads/p01.c
* Comments: edited by Luther Oct. 2001
*/

inherit "/std/room";
#include "defs.h"

void
create_room()
{
  set_short("On a path");  
  set_long("You are standing on a small path close to a stream. There are high mountains "+
           "to the north and south. The vegatation is sparse here.\n");  

  add_item("path","It's small and narrow.\n");
  add_item("stream","The water looks lovely!\n");
  add_item("water","What shouldn't you give to dive into that water!\n");
  add_item("vegetation","Just some low, dry bushes and grass.\n");

  OUTSIDE;
  WATER;

  add_exit(NOMAD + "p02", "southeast", 0, 1);
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
    TP->move_living("dives into the stream",NOMAD+"w4");
    return 1;
  }
  return 0;
}
