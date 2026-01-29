/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/s_trade/r12.c
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

object riverboat;

start_ship()
{
  if (!riverboat) 
    {
      riverboat=clone_object("/d/Cirath/chukel/ships/riverboat/riverboat");
      riverboat->move(TO);
    }
  
  riverboat->start_ship(0);
}

void create_room()
{
  set_short("On a pier at southern trade-route");
  
  set_long("You're standing on a wooden pier. Here you can, if you "+
           "want to pay the price, be shipped over to the other side "+
           "of the large river Durni. The river Sophri joins Durni at this location "+
           "and the result is a huge amount of streaming water. East lies "+
           "a small village and the trade-route continues southeast.\n");  

  add_item("road","This is the southern trade-route "+
           "that leads to Tyr.\n");
  add_item(({"river","water","stream","durni","Durni","sophri","Sophri"}),"The river "+
           "Durni flows west of you and Sophri to the north.\n");
  add_item("jungle","This is the jungle that covers the southern "+
           "part of Cirath.\n");
  add_item("village","It's a small village at the bank of the river Sophri../n");
  add_item(({"city","ciubori"}),"A cirathian city that lies south of here.\n");
  add_item("pier","It's a wooden pier.\n");
  
call_out("start_ship",1);
  add_prop(OBJ_S_WIZINFO,
           "type 'Call here start_ship' to restart the boat.\n"); 
           
  OUTSIDE;
  BEACH;
  
  add_exit(S_TRADE+"r11","southeast",0,1);
  reset_room();
}
