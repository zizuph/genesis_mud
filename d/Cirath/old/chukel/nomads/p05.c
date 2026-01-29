/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/nomads/p05.c
* Comments: edited by Luther Oct. 2001
*/

inherit "/std/room";
#include "defs.h"


void
create_room()
{
  set_short("On a path");  
  set_long("You are travelling a small path close to the base of a large mountain. "+
           "A small stream flows to your south.\n");  

  add_item("path","It's small and narrow.\n");
  add_item("stream","The stream is shimmering in the sunlight.\n");
  add_item("vegetation","Just some low, dry bushes and grass.\n");
  add_item(({"mountain","mountains"}),"The mountains are high with snow on the tops. "+
           "These mountains is the southern part of the large mountain ridge that dominates "+
           "the western parts of Cirath.\n");
           
  OUTSIDE;
  WATER;

  add_exit(NOMAD+"p06","east", 0, 1);
  add_exit(NOMAD+"p04","west", 0, 1);
  reset_room();
}
