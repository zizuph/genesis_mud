/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/s_trade/r07.c
* Comments: edited by Luther Oct. 2001
*/

inherit "/std/room";
#include "defs.h"

void
create_room()
{
  set_short("On the southern trade-route");  
  set_long("You are walking on the southern trade-route on the east "+
           "bank of a large river. The jungle is growing on both sides "+
           "of the river and north you can spot a bridge that leads "+
           "over it.\n");  

  add_item("road","This is the southern trade-route "+
           "that leads to Tyr.\n");
  add_item(({"river","water","stream","durni","Durni"}),"The river "+
           "Durni flows west of you.\n");
  add_item("jungle","This is the jungle that covers the southern "+
           "part of Cirath.\n");
  add_item("bridge","It's a stone bridge that leads over the river Durni./n");

  OUTSIDE;

  add_exit(S_TRADE+"r08","north",0,1);
  add_exit(S_TRADE+"r06","south",0,1);
  reset_room();
}
