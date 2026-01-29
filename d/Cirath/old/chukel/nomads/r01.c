/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/nomads/r01.c
* Comments: edited by Luther Oct. 2001
*/

inherit "/std/room";
#include "defs.h"


void
create_room()
{
  set_short("On a desert path");  
  set_long("This is a small path in a desert canyon. Once was this a river, but it has "+
           "dried out eons ago. South lies a large rock, which ends the path in that "+
           "direction. Past the rock, you can see a pretty large road. The path continues "+
           "northeast through the canyon.\n");  

  add_item("path","It's small and narrow.\n");
  add_item("canyon","It's deep and impressive.\n");
  add_item("road","The road is south of you and leads west through the canyon and "+
           "southeast out of it.\n");
  add_item("desert","You get thirsty just thinking on it...\n");
  add_item(({"rock","rocks"}),"Some are large and many are small and there's a lot of them "+
    "here! The large rock south of you seems climbable.\n");

  OUTSIDE;

  add_exit(NOMAD+"r02","northeast", 0, 1);
  reset_room();
}

void
init()
{
  ::init();
  add_action("climber","climb");
}

int climber(string str)
{
	notify_fail("Climb what?\n");
    	if(str!="rock")
    	return 0;
  if (str=="rock" && TP->query_skill(SS_CLIMB) > 45)
  {
    write("You climb the rock and slip easily down on the other side.\n");
    TP->move_living("",S_TRADE+"r38");
    return 1;
  }
  return 0;
}
