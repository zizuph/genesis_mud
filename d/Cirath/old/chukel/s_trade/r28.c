/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/s_trade/r28.c
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
  set_long("This is the southern trade-route which is one of "+
           "two large roads that leads through the island of "+
           "Cirath. The southern trade-route goes between the "+
           "cities of Tyr and Ciubori. It's covered with stone "+
           "bricks. The landscape is covered with grassy hills "+
           "and south you can see the sea.\n");  

  add_item("road","This is the southern trade-route that leads between "+
           "the cities Tyr and Ciubori.\n");
  add_item(({"brick","bricks"}),"The road is made of them.\n");
  add_item("seagulls","You can just hear them, not see them.\n");
  add_item("sea","The sea that Athas is surrounded by.\n");
  add_item(({"hill","hills"}),"They are quite low and not difficult "+
           "to climb.\n");

  OUTSIDE;

  add_exit(S_TRADE+"r27","east",0,1);
  add_exit(S_TRADE+"r29","west",0,1);
  reset_room();
}
