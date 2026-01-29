/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/s_trade/r11.c
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

void create_room()
{
  set_short("On the southern trade-route");  
  set_long("You're standing on the southern trade-route. A smaller road "+
           "leads into a little village to the northeast. To the north"+
           "west lies a small wooden pier where Krull ship travellers over "+
           "the river Durni. Southwest, the road continues towards the "+
           "city Ci'u'bori.\n");  

  add_item("road","This is the southern trade-route "+
           "that leads to Tyr.\n");
  add_item(({"river","water","stream","durni","Durni"}),"The river "+
           "Durni flows west of you.\n");
  add_item("jungle","This is the jungle that covers the southern "+
           "part of Cirath.\n");
  add_item("village","It's a small village, dominated by low, wooden buildings./n");
  add_item(({"city","ciubori"}),"A cirathian city that lies south of here.\n");
  add_item("pier","It's a wooden pier nortwest of you.\n");

  OUTSIDE;

 // add_exit(S_VILLAGE+"r01","northeast",0,1);
  add_exit(S_TRADE+"r12","northwest",0,1);
  add_exit(S_TRADE+"r10","southwest",0,1);
  reset_room();
}
