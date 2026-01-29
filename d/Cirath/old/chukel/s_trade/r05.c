/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/s_trade/r05.c
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
  set_short("On the southern trade-route");  
  set_long("This is the southern trade-route, the road that leads from "+
           "the city of Tyr to the "+
           "cirathian city Ciubori. The road is well-kept and made of "+
           "stone bricks, which makes it comfortable to walk on. "+
           "Northeast, you can see a vast jungle and to your west flows "+
           "the river Durni.\n");  

  add_item("road","This is the southern trade-route "+
           "that leads to Tyr.\n");
  add_item(({"river","water","stream","durni","Durni"}),"The river "+
           "Durni flows west of you.\n");
  add_item("jungle","This is the jungle that covers the southern "+
           "part of Cirath.\n");
  add_item(({"brick","bricks"}),"The bricks are flat and polished by the "+
           "many feet that have walked on them.\n");

  OUTSIDE;

  add_exit(S_TRADE+"r06","northwest",0,1);
  add_exit(S_TRADE+"r04","south",0,1);
  reset_room();
}
