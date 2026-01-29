/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/s_trade/r33.c
* Comments: edited by Luther Oct. 2001
*/

inherit "/std/room";
#include "defs.h"

void
create_room()
{
  set_short("On the southern trade-route");  
  set_long("You're travelling on a road on the cirathian plains that "+
           "covers the southern part of Athas. The plains are covered "+
           "with grass. West lies a mountain ridge and east, the plains "+
           "continue.\n");  

  add_item("road","This is the southern trade-route that leads between "+
           "the cities Tyr and Ciubori.\n");
  add_item(({"brick","bricks"}),"The road is made of them.\n");
  add_item(({"plain","plains"}),"They're flat.\n");
  add_item(({"mountain","mountains","ridge"}),"The mountains looks quite "+
    "massive.\n");

  OUTSIDE;

  add_exit(S_TRADE+"r32","southeast",0,1);
  add_exit(S_TRADE+"r34","west",0,1);
  reset_room();
}
