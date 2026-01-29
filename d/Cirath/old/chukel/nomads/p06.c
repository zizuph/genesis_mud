/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/nomads/p06.c
* Comments: edited by Luther Oct. 2001
*/

inherit "/std/room";
#include "defs.h"


void
create_room()
{
  set_short("On a path");  
  set_long("This is a small path in the southwestern part of the kingdom Cirath. "+
           "North lies a large mountain and south flows a small stream.\n");  

  add_item("path","It's small and narrow.\n");
  add_item("stream","The stream is shimmering in the sunlight.\n");
  add_item(({"mountain","mountains"}),"The mountains are high with snow on the tops. "+
           "These mountains is the southern part of the large mountain ridge that dominates "+
           "the western parts of Cirath.\n");
  OUTSIDE;
  WATER;

  add_exit(NOMAD+"p07","northeast", 0, 1);
  add_exit(NOMAD+"p05","west", 0, 1);
  reset_room();
}
