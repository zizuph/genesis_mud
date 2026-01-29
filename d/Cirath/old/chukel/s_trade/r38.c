/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/s_trade/r38.c
* Comments: edited by Luther Oct. 2001
*/

inherit "/std/room";
#include "defs.h"
#include "/d/Cirath/common/mobber.h"


void
reset_room()
{
	 bring_room_mob("guard", MONSTER + "traveller.c", 1, 1);
}

void
create_room()
{
  set_short("On the southern trade-route");  
  set_long("You are travelling on a road through a desert. To your east you see a "+
           "gigantic wall that stretches from the north to the south, as far as you "+
           "can see. It is built at the base of a mountain ridge and southeast of you, "+
           "there is a way through it. West lies a canyon which bends north here.\n");  

  add_item("canyon","The canyon is quite wide and bend north here. To the north it's "+
           "covered with large rocks.\n");
  add_item(({"rock","rocks"}),"They are large and strangely shaped. You discover "+
           "a small path that leads north through the rocky canyon.\n");
  add_item("path","The path is very small and it seems that someone has tried to "+
           "hide its existance. You have to climb a rock to get to it.\n");
  add_item("road","This is the southern trade-route that leads between "+
           "the cities Tyr and Ciubori.\n");
  add_item(({"brick","bricks"}),"The road is made of them.\n");
  add_item(({"mountain","mountains","ridge"}),"The mountains looks quite "+
    "massive.\n");
  add_item("wall","This is the wall that splits Athas into two. It was built "+
    "to protect the cirathian citizens from the nomads that lives in the desert "+
    "west of the kingdom. However, the nomads, and later on, the barbarians from "+
    "Gont have found a way past it and are now populating the desert east of the "+
    "mountain ridge.\n");
  add_item("desert","You get thirsty just thinking on it...\n");

  OUTSIDE;

  add_exit(S_TRADE+"r37","southeast",0,1);
  add_exit(S_TRADE+"r39","west",0,1);
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
  if (str == "rock")
  {
    NF("Hmmm...you are not skilled enough to climb that rock.");
    if (TP->query_skill(SS_CLIMB) > 40)
    {
      write("You start to climb the rock.\n");
      call_out("rock",5);
      return 1;
    }
    return 0;
  }
  return 0;
}

int rock()
{
  write("You manage to climb the rock and slip down on the other side.\n");
  TP->move_living("climbs a rock",NOMAD+"r01");
  return 1;
}
