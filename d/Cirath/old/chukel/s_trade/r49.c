/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/s_trade/r49.c
* Comments: edited by Luther Oct. 2001
*/

inherit "/std/room";
#include "defs.h"

void
create_room()
{
  set_short("On the southern trade-route");  
  set_long("You're travelling on a bricked road through the desert. The gates of the city "+
           "Tyr can be seen to the northwest and southeast, the road continues through the "+
           "dunes of the desert.\n");  

  add_item(({"tyr","Tyr","gate","gates"}),"You can see the gates to the northeast.\n");
  add_item("road","This is the southern trade-route that leads between "+
           "the cities Tyr and Ciubori.\n");
  add_item(({"brick","bricks"}),"The road is made of them.\n");
  add_item("desert","You get thirsty just thinking on it...\n");
  add_item(({"dune","dunes"}),"They are quite impressive.\n");
  add_item(({"rock","rocks"}),"Some are large and many are small and there's a lot of them "+
    "here!\n");
  add_item("sun","It shines on you unmercifully.\n");

  OUTSIDE;

  add_exit(S_TRADE+"r48","southeast",0,1);
  add_exit(S_TRADE+"r50","west",0,1);
  reset_room();
}
