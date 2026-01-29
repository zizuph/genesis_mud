/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/s_trade/r10.c
* Comments: edited by Luther Oct. 2001
*/

inherit "/std/room";
#include "defs.h"

void
create_room()
{
  set_short("On the southern trade-route");  
  set_long("You are walking on a quite large road that leads between two "+
           "remote cities, Tyr and Ci'u'bori. Northeast you can see one of "+
           "the little villages that lies on the bank of Durni, the large "+
           "river. South the road continues toward Ci'u'bori.\n");  

  add_item("road","This is the southern trade-route "+
           "that leads to Tyr.\n");
  add_item(({"river","water","stream","durni","Durni"}),"The river "+
           "Durni flows west of you.\n");
  add_item("jungle","This is the jungle that covers the southern "+
           "part of Cirath.\n");
  add_item("village","A small village, dominated by low wooden houses./n");
  add_item(({"city","ciubori"}),"A cirathian city that lies south of here.\n");

  OUTSIDE;

  add_exit(S_TRADE+"r11","northeast",0,1);
  add_exit(S_TRADE+"r09","south",0,1);
  reset_room();
}
