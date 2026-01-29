/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/s_trade/r23.c
* Comments: edited by Luther Oct. 2001
*/

inherit "/std/room";
#include "defs.h"

void
create_room()
{
  set_short("On the southern trade-route");  
  set_long("Your on the great road named 'The Southern Trade-Route' that "+
           "leads from the city of Tyr on the western side of Athas, to "+
           "the cirathian city Ciubori on the southern part. The road is "+
           "covered with bricks, to make it easier to walk on. To your "+
           "north lise a stream and beyond it a dark, a little threatening "+
           "forest. East and west, small paths leads off the road and into "+
           "the wilderness.\n");  

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
  add_item(({"path","paths"}),"The paths are small, maybe made by animals.\n");

  OUTSIDE;

 // add_exit(ANTHRAX+"r01","west",0,1);
 // add_exit(JUNGLE+"r1","east",0,1);
  add_exit(S_TRADE+"r22","northeast",0,1);
  add_exit(S_TRADE+"r24","southeast",0,1);
  reset_room();
}
