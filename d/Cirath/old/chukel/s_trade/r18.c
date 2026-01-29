/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/s_trade/r18.c
* Comments: edited by Luther Oct. 2001
*/

inherit "/std/room";
#include "defs.h"

void
create_room()
{
  set_short("On the southern trade-route");  
  set_long("You are travelling a well-kept road that leads in east-"+
           "southwest direction. The surroundings are great as you can "+
           "see the Dohrath mountain to the north, a little stream and "+
           "a jungle to the south. East lies a green forest covered by "+
           "fog. This area is breath-taking.\n");  

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

  add_exit(S_TRADE+"r19","southwest",0,1);
  add_exit(S_TRADE+"r17","east",0,1);
  reset_room();
}
