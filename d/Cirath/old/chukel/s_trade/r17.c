/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/s_trade/r17.c
* Comments: edited by Luther Oct. 2001
*/

inherit "/std/room";
#include "defs.h"

void
create_room()
{
  set_short("On the southern trade-route");  
  set_long("This is the southern trade-route that leads from Tyr to "+
           "the cirathian city Ciubori. The road is made of stone "+
           "bricks that have been polished by all the feets that have "+
           "walked on them. The view from here is great. North, the "+
           "mountain Dohrath can be seen, with all its might. To the "+
           "south is a stream and on the other side a jungle. A little "+
           "village is to the northeast and to the west, there is a green "+
           "forest surrounded by mist.\n");  

  add_item("road","This is the southern trade-route that leads between "+
           "the cities Tyr and Ciubori.\n");
  add_item(({"water","stream"}),"The stream flows fast and the water is "+
           "clear.\n");
  add_item("village","It's one of the poor villages that are inhabited by "+
           "the 'inlanders' as the cirathian people prefer to call them./n");
  add_item(({"dohrath","mountain","peak","peaks","my-doh","kar-doh","suri-doh",
           "nih-doh"}),"Dohrath is a very impressive mountain.\n");
  add_item("jungle","This is the west part of the large jungles that grows "+
           "on the southeastern part of Athas.\n");
  add_item("forest","It's a dark green forest. Somewhat threatening with all "+
          "that fog around it.\n");
  add_item(({"fog","mist"}),"It is surrounding the forest.\n");

  OUTSIDE;

  add_exit(S_TRADE+"r18","west",0,1);
  add_exit(S_TRADE+"r16","northeast",0,1);
  reset_room();
}
