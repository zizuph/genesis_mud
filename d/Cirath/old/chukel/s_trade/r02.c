/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/s_trade/r02.c
* Comments: edited by Luther Oct. 2001
*/

inherit "/std/room";
#include "defs.h"

void
create_room()
{
  set_short("On the southern trade-route");  
  set_long("You are travelling along the southern trade-route "+
           "through the marches of the mouth of Durni, the mighty "+
           "river. Everywhere are small streams running slowly through "+
           "the vegetation. South, you can see the city of Ci'u'bori.\n");  

  add_item("road","This is the southern trade-route "+
           "that leads to Tyr.\n");
  add_item(({"river","water","stream","durni","Durni"}),"This is the "+
           "mouth of the large river Durni.\n");
  add_item(({"march","marches","swamp"}),"The area is full of water "+
           "and the ground is not very reliable.\n");
  add_item(({"city","ciubori","town","Ciubori"}),"This is the third "+
           "city of Cirath. It's magnifique.\n");

  OUTSIDE;

  add_exit(S_TRADE+"r03","north",0,1);
  add_exit(S_TRADE+"r01","south",0,1);
  reset_room();
}
