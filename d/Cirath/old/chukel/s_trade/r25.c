/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/s_trade/r25.c
* Comments: edited by Luther Oct. 2001
*/

inherit "/std/room";
#include "defs.h"

void
create_room()
{
  set_short("On the southern trade-route");  
  set_long("You are travelling on a large and neatly bricked road that "+
           "leads between the two cities of Tyr and Ciubori. This road "+
           "is called 'The Southern Trade-Route' because it is frequently "+
           "used by merchants. East lies a jungle.\n");  

  add_item("road","This is the southern trade-route that leads between "+
           "the cities Tyr and Ciubori.\n");
  add_item("jungle","This is the west part of the large jungles that grows "+
           "on the southeastern part of Athas.\n");
  add_item(({"brick","bricks"}),"The road is made of them.\n");

  OUTSIDE;

  add_exit(S_TRADE+"r24","north",0,1);
  add_exit(S_TRADE+"r26","southwest",0,1);
  reset_room();
}
