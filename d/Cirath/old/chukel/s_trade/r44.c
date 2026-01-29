/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/s_trade/r44.c
* Comments: edited by Luther Oct. 2001
*/

inherit "/std/room";
#include "defs.h"

void
create_room()
{
  set_short("On the southern trade-route");  
  set_long("The desert seems like it will never end. The place seems completely empty "+
           "from both life and water. The surroundings are filled with strange shaped "+
           "rocks and would have been very hard to travel if the road didn't make "+
           "things easier.\n");  

  add_item("road","This is the southern trade-route that leads between "+
           "the cities Tyr and Ciubori.\n");
  add_item(({"brick","bricks"}),"The road is made of them.\n");
  add_item("desert","You get thirsty just thinking on it...\n");
  add_item(({"rock","rocks"}),"Some are large and many are small and there's a lot of them "+
    "here!\n");
  add_item("sun","It shines on you unmercifully.\n");

  OUTSIDE;

  add_exit(S_TRADE+"r43","southeast",0,1);
  add_exit(S_TRADE+"r45","northwest",0,1);
  reset_room();
}
