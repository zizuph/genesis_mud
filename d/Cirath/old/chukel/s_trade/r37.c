/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/s_trade/r37.c
* Comments: edited by Luther Oct. 2001
*/

inherit "/std/room";
#include "defs.h"

void
create_room()
{
  set_short("On the southern trade-route");  
  set_long("You are standing outside a impressive wall that is built at the base "+
           "of a mountain. Inside the wall, further east, you can spot a large "+
           "gate covers a tunnel that leads through the mountain. West, the road "+
           "leads into a dry desert.\n");  

  add_item("road","This is the southern trade-route that leads between "+
           "the cities Tyr and Ciubori.\n");
  add_item(({"brick","bricks"}),"The road is made of them.\n");
  add_item(({"mountain","mountains","ridge"}),"The mountains looks quite "+
    "massive.\n");
  add_item(({"cave","tunnel","opening"}),"The tunnel doesn't seem natural. "+
    "Someone or something have made it.\n");
  add_item("gate","The gate leads into the kingdom of Cirath.\n");
  add_item("wall","This is the wall that splits Athas into two. It was built "+
    "to protect the cirathian citizens from the nomads that lives in the desert "+
    "west of the kingdom. However, the nomads, and later on, the barbarians from "+
    "Gont have found a way past it and are now populating the desert east of the "+
    "mountain ridge.\n");
  add_item("desert","You get thirsty just thinking on it...\n");

  OUTSIDE;

  add_exit(S_TRADE+"gate","east",0,1);
  add_exit(S_TRADE+"r38","northwest",0,1);
  reset_room();
}
