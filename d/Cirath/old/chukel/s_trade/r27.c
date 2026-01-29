/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/s_trade/r27.c
* Comments: edited by Luther Oct. 2001
*/

inherit "/std/room";
#include "defs.h"

void
create_room()
{
  set_short("On the southern trade-route");  
  set_long("The bricked road you are currently travelling on, "+
           "goes through low, grassy hills, quite near the south "+
           "coast of Athas. The road is made of stone bricks which "+
           "makes it easier to walk on. The air smells of salt and "+
           "you can hear seagulls in the distance.\n");  

  add_item("road","This is the southern trade-route that leads between "+
           "the cities Tyr and Ciubori.\n");
  add_item(({"brick","bricks"}),"The road is made of them.\n");
  add_item("seagulls","You can just hear them, not see them.\n");

  OUTSIDE;

  add_exit(S_TRADE+"r26","northeast",0,1);
  add_exit(S_TRADE+"r28","west",0,1);
  reset_room();
}
