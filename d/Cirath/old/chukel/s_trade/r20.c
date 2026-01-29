/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/s_trade/r20.c
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
  set_long("This is the southern trade-route that goes between the cities "+
           "of Tyr and Ciubori. The bricked road looks well-kept and well-"+
           "travelled. North of the road lies a dark forest, covered with "+
           "mist and south flows a stream joyfully. Southeast, on the other "+
           "side of the stream lies a jungle.\n");  

  add_item("road","This is the southern trade-route that leads between "+
           "the cities Tyr and Ciubori.\n");
  add_item(({"water","stream"}),"The stream flows fast and the water is "+
           "clear.\n");
  add_item("jungle","This is the west part of the large jungles that grows "+
           "on the southeastern part of Athas.\n");
  add_item("forest","It's a dark green forest. Somewhat threatening with all "+
          "that fog around it.\n");
  add_item(({"fog","mist"}),"It is surrounding the forest.\n");
  add_item(({"brick","bricks"}),"The road is made of them.\n");

  OUTSIDE;

  add_exit(S_TRADE+"r21","west",0,1);
  add_exit(S_TRADE+"r19","northeast",0,1);
  reset_room();
}
