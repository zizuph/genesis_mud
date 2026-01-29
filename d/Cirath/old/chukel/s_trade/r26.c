/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/s_trade/r26.c
* Comments: edited by Luther Oct. 2001
*/

inherit "/std/room";
#include "defs.h"

void
create_room()
{
  set_short("On the southern trade-route");  
  set_long("You're travelling a large road near the southern coast "+
           "of Athas. The surroundings are dominated by green grassy, "+
           "not so very high, hills and in the distance you can hear "+
           "seagulls.\n");  

  add_item("road","This is the southern trade-route that leads between "+
           "the cities Tyr and Ciubori.\n");
  add_item(({"brick","bricks"}),"The road is made of them.\n");
  add_item("seagulls","You can just hear them, not see them.\n");

  OUTSIDE;

  add_exit(S_TRADE+"r25","northeast",0,1);
  add_exit(S_TRADE+"r27","southwest",0,1);
  reset_room();
}
