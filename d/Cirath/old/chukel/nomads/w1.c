/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/nomads/w01.c
* Comments: edited by Luther Oct. 2001
*/

inherit "/std/room";
#include "defs.h"

void
create_room()
{
  set_short("In a stream");  
  set_long("This is a stream. The water is cold and refreshing. There is a way out "+
           "of the water here. The stream continues east and west, but west it is "+
           "not swimmable because of the sharp rocks.\n");  

  add_item("stream","This stream is rather small, but it's nice to swim in\n");
  add_item("water","The water has the right temperature.\n");
  add_item(({"rock","rocks"}),"Looks nasty.\n");

  OUTSIDE;
  WATER;

  add_exit(NOMAD+"r04","up", 0, 1);
  reset_room();
}

void
init()
{
  ::init();
  add_action("swimmer","swim");
}

int swimmer(string str)
{
	notify_fail("Swim where?\n");
    	if(str!="east")
        	return 0;
  if (str=="east" && TP->query_skill(SS_SWIM) > 35)
  {
    write("You swim east.\n");
    TP->move_living("swimming",NOMAD+"w2");
    return 1;
  }
  return 0;
}
