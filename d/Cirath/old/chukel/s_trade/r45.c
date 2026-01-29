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
  set_long("You're travelling on a large road that stretches through the desert. "+
           "It is said that a nomad tribe are living in the eastern part of it, and "+
           "you wonder how they "+
           "can survive since you've seen no water, nor any game to hunt. West of here "+
           "changes the desert shape into a sand desert with it's impressive dunes.\n");  

  add_item("road","This is the southern trade-route that leads between "+
           "the cities Tyr and Ciubori.\n");
  add_item(({"brick","bricks"}),"The road is made of them.\n");
  add_item(({"dune","dunes"}),"They lie west of here.\n");
  add_item("desert","You get thirsty just thinking on it...\n");
  add_item(({"rock","rocks"}),"Some are large and many are small and there's a lot of them "+
    "here!\n");
  add_item("sun","It shines on you unmercifully.\n");

  OUTSIDE;

  add_exit(S_TRADE+"r44","southeast",0,1);
  add_exit(S_TRADE+"r46","west",0,1);
  reset_room();
}
