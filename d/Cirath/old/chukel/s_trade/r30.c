/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/s_trade/r30.c
* Comments: edited by Luther Oct. 2001
*/

inherit "/std/room";
#include "defs.h"

void
create_room()
{
  set_short("On the southern trade-route");  
  set_long("You are travelling on a stone-bricked road close to the "+
           "southern coast of Athas. The road is well-kept and obviously "+
           "pretty well-travelled. There are low, grassy hills here which "+
           "makes the view quite relaxing. Further west, plains stretches "+
           "out.\n");  

  add_item("road","This is the southern trade-route that leads between "+
           "the cities Tyr and Ciubori.\n");
  add_item(({"brick","bricks"}),"The road is made of them.\n");
  add_item("seagulls","You can just hear them, not see them.\n");
  add_item("sea","The sea that Athas is surrounded by.\n");
  add_item(({"hill","hills"}),"They are quite low and not difficult "+
           "to climb.\n");
  add_item(({"plain","plains"}),"They're flat.\n");

  OUTSIDE;

  add_exit(S_TRADE+"r29","east",0,1);
  add_exit(S_TRADE+"r31","northwest",0,1);
  reset_room();
}
