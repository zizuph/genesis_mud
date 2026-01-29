/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/s_trade/r36.c
* Comments: edited by Luther Oct. 2001
*/

inherit "/std/room";
#include "defs.h"

void
create_room()
{
  set_short("On the southern trade-route");  
  set_long("You are standing on a road east of a mountain and west of "+
           "some plains. The road leads west through an opening in the "+
           "mountain, which is dark, but doesn't look especially "+
           "threatening. East, the road leads through the plains.\n");  

  add_item("road","This is the southern trade-route that leads between "+
           "the cities Tyr and Ciubori.\n");
  add_item(({"brick","bricks"}),"The road is made of them.\n");
  add_item(({"plain","plains"}),"They're flat.\n");
  add_item(({"mountain","mountains","ridge"}),"The mountains looks quite "+
    "massive.\n");
  add_item(({"cave","tunnel","opening"}),"The tunnel doesn't seem natural. "+
    "Someone ore something have made it.\n");

  OUTSIDE;

  add_exit(S_TRADE+"r35","southeast",0,1);
  add_exit(S_TRADE+"c1","west",0,1);
  reset_room();
}
