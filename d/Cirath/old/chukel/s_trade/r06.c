/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/s_trade/r06.c
* Comments: edited by Luther Oct. 2001
*/

inherit "/std/room";
#include "defs.h"
#include "/d/Cirath/common/mobber.h"


void
reset_room()
{
	 bring_room_mob("guard", MONSTER + "traveller.c", 1, 1);
}

void
create_room()
{
  set_short("On the southern trade-route");  
  set_long("The road leads close to the eastern bank of the large "+
           "river Durni. You have a jungle to your east and you can "+
           "see that it continues on the other side of the river. "+
           "The road bends here to the southeast and away from the river.\n");  

  add_item("road","This is the southern trade-route "+
           "that leads to Tyr.\n");
  add_item(({"river","water","stream","durni","Durni"}),"The river "+
           "Durni flows west of you.\n");
  add_item("jungle","This is the jungle that covers the southern "+
           "part of Cirath.\n");

  OUTSIDE;

  add_exit(S_TRADE+"r07","north",0,1);
  add_exit(S_TRADE+"r05","southeast",0,1);
  reset_room();
}
