/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/s_trade/c4.c
* Comments: edited by Luther Oct. 2001
*/

inherit "/std/room";
#include "defs.h"

void
create_room()
{
  set_short("In a tunnel");  
  set_long("You're at the west end of a tunnel. West, you can see the light "+
           "and east it proceeds further inside the mountain.\n");  

  add_item("road","This is the southern trade-route that leads between "+
           "the cities Tyr and Ciubori.\n");
  add_item(({"mountain","mountains","ridge"}),"The tunnel leads through it.\n");
  add_item(({"cave","tunnel","opening"}),"The tunnel doesn't seem natural. "+
    "Someone ore something have made it. It leads through the mountain.\n");

  INSIDE;
  DARK;

  add_exit(S_TRADE+"c3","east",0,1);
  add_exit(S_TRADE+"gate","west",0,1);
  reset_room();
}
