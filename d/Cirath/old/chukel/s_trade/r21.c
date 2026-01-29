/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/s_trade/r21.c
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
  set_long("You travel on a road south of a dark green forest surrounded "+
           "fog. South of the road is a stream and the road continues over "+
           "it by a wooden bridge. To your southeast lies a large jungle.\n");  

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
  add_item("bridge","The bridge is made of wood and is well-built. It looks safe "+
           "to pass over.\n");

  OUTSIDE;

  add_exit(S_TRADE+"r20","east",0,1);
  add_exit(S_TRADE+"r22","south",0,1);
  reset_room();
}
