/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/s_trade/r19.c
* Comments: edited by Luther Oct. 2001
*/

inherit "/std/room";
#include "defs.h"

void
create_room()
{
  set_short("On the southern trade-route");  
  set_long("You are travelling a road between two far away cities. The "+
           "air is peaceful and the view is enormous. You can see a large "+
           "mountain to the north and south is a stream and a jungle. West "+
           "lies a scary forest surrounded by a tight fog. The road continues "+
           "northeast and southwest.\n");  

  add_item("road","This is the southern trade-route that leads between "+
           "the cities Tyr and Ciubori.\n");
  add_item(({"water","stream"}),"The stream flows fast and the water is "+
           "clear.\n");
  add_item(({"dohrath","mountain","peak","peaks","my-doh","kar-doh","suri-doh",
           "nih-doh"}),"Dohrath is a very impressive mountain.\n");
  add_item("jungle","This is the west part of the large jungles that grows "+
           "on the southeastern part of Athas.\n");
  add_item("forest","It's a dark green forest. Somewhat threatening with all "+
          "that fog around it.\n");
  add_item(({"fog","mist"}),"It is surrounding the forest.\n");

  OUTSIDE;

  add_exit(S_TRADE+"r20","southwest",0,1);
  add_exit(S_TRADE+"r18","northeast",0,1);
  reset_room();
}
