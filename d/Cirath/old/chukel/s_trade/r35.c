/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/s_trade/r35.c
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
  set_long("You're travelling on a road through the cirathian plains, "+
           "which lies between a massive mountain ridge and the jungles "+
           "on the southeastern part of Athas. The road is covered with "+
           "stone bricks. East of here, the road continues over the plains "+
           "and to the west it leads towards a mountain.\n");  

  add_item("road","This is the southern trade-route that leads between "+
           "the cities Tyr and Ciubori.\n");
  add_item(({"brick","bricks"}),"The road is made of them.\n");
  add_item(({"plain","plains"}),"They're flat.\n");
  add_item(({"mountain","mountains","ridge"}),"The mountains looks quite "+
    "massive.\n");

  OUTSIDE;

  add_exit(S_TRADE+"r34","east",0,1);
  add_exit(S_TRADE+"r36","northwest",0,1);
  reset_room();
}
