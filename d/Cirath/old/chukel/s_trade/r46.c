/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/s_trade/r46.c
* Comments: edited by Luther Oct. 2001
*/

inherit "/std/room";
#include "defs.h"

void
create_room()
{
  set_short("On the southern trade-route");  
  set_long("The southern trade-route leads through the sand desert. The sun is terrible and "+
           "no signs of wildlife can be seen neither a drop of water. East of here changes "+
           "the desert into a more rocky shape.\n");  

  add_item("road","This is the southern trade-route that leads between "+
           "the cities Tyr and Ciubori.\n");
  add_item(({"brick","bricks"}),"The road is made of them.\n");
  add_item("desert","You get thirsty just thinking on it...\n");
  add_item(({"rock","rocks"}),"Some are large and many are small and there's a lot of them "+
    "here!\n");
  add_item("sun","It shines on you unmercifully.\n");

  OUTSIDE;

  add_exit(S_TRADE+"r45","east",0,1);
  add_exit(S_TRADE+"r47","west",0,1);
  reset_room();
}
