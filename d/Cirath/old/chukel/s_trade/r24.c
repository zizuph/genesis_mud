/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/s_trade/r24.c
* Comments: edited by Luther Oct. 2001
*/

inherit "/std/room";
#include "defs.h"

void
create_room()
{
  set_short("On the southern trade-route");  
  set_long("You are travelling on a quite large road in the middle of "+
           "the island Athas. The road is covered with bricks to save "+
           "the poor travellers feet. East of you lies a green jungle.\n");  

  add_item("road","This is the southern trade-route that leads between "+
           "the cities Tyr and Ciubori.\n");
  add_item("jungle","This is the west part of the large jungles that grows "+
           "on the southeastern part of Athas.\n");
  add_item(({"fog","mist"}),"It is surrounding the forest.\n");
  add_item(({"brick","bricks"}),"The road is made of them.\n");

  OUTSIDE;

  add_exit(S_TRADE+"r23","northwest",0,1);
  add_exit(S_TRADE+"r25","south",0,1);
  reset_room();
}
