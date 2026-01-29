/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/s_trade/r04.c
* Comments: edited by Luther Oct. 2001
*/

inherit "/std/room";
#include "defs.h"

void
create_room()
{
  set_short("On the southern trade-route");  
  set_long("You are travelling on the southern trade_route that leads "+
           "from Tyr to the city Ciubori. Northeast lies a jungle and "+
           "west, the mighty river Durni. The road continues north and "+
           "southeast.\n");  

  add_item("road","This is the southern trade-route "+
           "that leads to Tyr.\n");
  add_item(({"river","water","stream","durni","Durni"}),"The river "+
           "Durni flows west of you.\n");
  add_item("jungle","This is the jungle that covers the southern "+
           "part of Cirath.\n");

  OUTSIDE;

  add_exit(S_TRADE+"r05","north",0,1);;
  add_exit(S_TRADE+"r03","southwest",0,1);
  reset_room();
}
