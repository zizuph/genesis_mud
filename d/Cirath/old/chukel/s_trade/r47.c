/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/s_trade/r47.c
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
  set_long("You're standing on a bricked road in the hostile desert. TThe road is free "+
           "from sand which seems very strange. Someone is appearantly keeping it clean.\n");  

  add_item("road","This is the southern trade-route that leads between "+
           "the cities Tyr and Ciubori.\n");
  add_item(({"brick","bricks"}),"The road is made of them.\n");
  add_item("desert","You get thirsty just thinking on it...\n");
  add_item("sun","It shines on you unmercifully.\n");

  OUTSIDE;

  add_exit(S_TRADE+"r46","east",0,1);
  add_exit(S_TRADE+"r48","southwest",0,1);
  reset_room();
}
