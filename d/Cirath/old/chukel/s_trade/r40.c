/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/s_trade/r40.c
* Comments: edited by Luther Oct. 2001
*/

inherit "/std/room";
#include "defs.h"

void
create_room()
{
  set_short("On the southern trade-route");  
  set_long("You are travelling on a large road through a hostile-looking desert. "+
           "There is no vegetation here, primaly because there are no water, but "+
           "also the fact that the ground is made of rocks. The road keeps following "+
           "the canyon which bends here.\n");  

  add_item("canyon","It's deep and impressive.\n");
  add_item("road","This is the southern trade-route that leads between "+
           "the cities Tyr and Ciubori.\n");
  add_item(({"brick","bricks"}),"The road is made of them.\n");
  add_item("desert","You get thirsty just thinking on it...\n");
  add_item(({"rock","rocks"}),"Some are large and many are small and there's a lot of them "+
    "here!\n");

  OUTSIDE;

  add_exit(S_TRADE+"r39","northeast",0,1);
  add_exit(S_TRADE+"r41","west",0,1);
  reset_room();
}
