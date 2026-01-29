/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/s_trade/r16.c
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
  set_short("Outside a village on southern trade-route");  
  set_long("You are standing on a road close to a village. The "+
           "village is small and looks rather poor. To the south "+
           "there is a small stream and the water is glimmering in "+
           "the sunlight. Beyond the stream lies a jungle and north, "+
           "the king of mountains, Dohrath, with its four mighty peaks "+
           "almost touching the sun. The road continues southwest and "+
           "east.\n");  

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
  add_item("sun","The sun shines bright and warms your shoulders.\n");
  
  OUTSIDE;

  add_exit(S_TRADE+"r17","southwest",0,1);
  add_exit(S_TRADE+"r15","east",0,1);
  reset_room();
}
