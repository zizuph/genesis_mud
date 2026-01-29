/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/s_trade/r32.c
* Comments: edited by Luther Oct. 2001
*/

inherit "/std/room";
#include "defs.h"

void
create_room()
{
  set_short("On the southern trade-route");  
  set_long("You're on a large road that leads through the plains. It's "+
           "bricked with stones which makes it easy to travel on. Some "+
           "mountains can be seen at the western horizon and to the east "+
           "the road proceeds over the plains.\n");  

  add_item("road","This is the southern trade-route that leads between "+
           "the cities Tyr and Ciubori.\n");
  add_item(({"brick","bricks"}),"The road is made of them.\n");
  add_item(({"plain","plains"}),"They're flat.\n");
  add_item(({"mountain","mountains","ridge"}),"The mountains looks quite "+
    "massive.\n");

  OUTSIDE;

  add_exit(S_TRADE+"r31","east",0,1);
  add_exit(S_TRADE+"r33","northwest",0,1);
  reset_room();
}
