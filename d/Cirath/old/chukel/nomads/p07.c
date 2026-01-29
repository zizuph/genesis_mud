/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/nomads/p07.c
* Comments: edited by Luther Oct. 2001
*/

inherit "/std/room";
#include "defs.h"


void
create_room()
{
  set_short("On a path");  
  set_long("You are travelling on a small path north of a small stream and south "+
           "of a large mountain. Beyond the stream lies some green and grassy plains.\n");  

  add_item("path","It's small and narrow.\n");
  add_item("stream","The stream is shimmering in the sunlight.\n");
  add_item(({"mountain","mountains"}),"The mountains are high with snow on the tops. "+
           "These mountains is the southern part of the large mountain ridge that dominates "+
           "the western parts of Cirath.\n");
  add_item(({"plain","plains"}),"They are vast. You think you can spot some kind of "+
           "town there too.\n");

  OUTSIDE;
  WATER;

  add_exit(NOMAD+"p08","east", 0, 1);
  add_exit(NOMAD+"p06","southwest", 0, 1);
  reset_room();
}
