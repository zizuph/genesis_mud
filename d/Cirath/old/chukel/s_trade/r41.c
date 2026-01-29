/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/s_trade/r41.c
* Comments: edited by Luther Oct. 2001
*/

inherit "/std/room";
#include "defs.h"

void
create_room()
{
  set_short("On the southern trade-route");  
  set_long("You are standing on a road that leads through the rocks in a desert canyon."+
           "The canyon was propably made by a river that dried out long ago. The sun burns "+
           "your shoulders and the "+
           "sweat is pouring from your skin. This is no place to live, unless you "+
           "can survive on eating rocks.\n");  

  add_item("canyon","The canyon is pretty deep. and has quite impressive shapes.\n");
  add_item("road","This is the southern trade-route that leads between "+
           "the cities Tyr and Ciubori.\n");
  add_item(({"brick","bricks"}),"The road is made of them.\n");
  add_item("desert","You get thirsty just thinking on it...\n");
  add_item(({"rock","rocks"}),"Some are large and many are small and there's a lot of them "+
    "here!\n");
  add_item("sun","It shines on you unmercifully.\n");

  OUTSIDE;

  add_exit(S_TRADE+"r40","east",0,1);
  add_exit(S_TRADE+"r42","west",0,1);
  reset_room();
}
