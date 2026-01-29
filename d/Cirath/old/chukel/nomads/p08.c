/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/nomads/p08.c
* Comments: edited by Luther Oct. 2001
*/

inherit "/std/room";
#include "defs.h"


void
create_room()
{
  set_short("On a path");  
  set_long("You are standing on a path at the base of a large mountain. There's a "+
           "stream to your south and beyond it lies some plains. The vegitation consists "+
           "of grass and some high bushes.\n");  

  add_item("path","It's small and narrow.\n");
  add_item("stream","The stream is shimmering in the sunlight.\n");
  add_item(({"mountain","mountains"}),"The mountains are high with snow on the tops. "+
           "These mountains is the southern part of the large mountain ridge that dominates "+
           "the western parts of Cirath.\n");
  add_item(({"plain","plains"}),"They are vast. You think you can spot some kind of "+
           "town there too.\n");
  add_item(({"bush","bushes"}),"The bushes makes it hard to see where you go.\n");

  OUTSIDE;
  WATER;

  add_exit(NOMAD+"p09","southeast", 0, 1);
  add_exit(NOMAD+"p07","west", 0, 1);
  reset_room();
}
