/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/s_trade/r13.c
* Comments: edited by Luther Oct. 2001
*/

inherit "/std/room";
#include "defs.h"
#include "/d/Cirath/common/teamer.h"

void
reset_room()
{
	bring_room_team(MONSTER + "c_guard", 1, 1);
}

void
create_room()
{
  set_short("On a pier at southern trade-route");  
  set_long("This is a wooden pier on the west side of the river Durni. "+
           "The river is quite wide here since the river Sophri joins "+
           "Durni here. A small boat uses to take travellers over to "+
           "the other side. To the southwest lies a little village that "+
           "looks rather poor.\n");  

  add_item("road","This is the southern trade-route "+
           "that leads to Tyr.\n");
  add_item(({"river","water","stream","durni","Durni","sophri","Sophri"}),"The river "+
           "Durni flows west of you and Sophri to the north.\n");
  add_item("village","It's one of the poor villages that are inhabited by "+
           "the 'inlanders' as the cirathian people prefer to call them./n");
  add_item("pier","It's a wooden pier.\n");

  OUTSIDE;
  BEACH;
  
  add_exit(S_TRADE+"r14","southwest",0,1);
  reset_room();
}
