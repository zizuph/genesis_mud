/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/desert/d35.c
* Comments: updated by Luther Oct. 2001
*/

inherit "/std/room";
#include "defs.h"

void
create_room()
{
  set_short("On a mountain in the desert");
  set_long("Northeast part of desert at a cliff on a mountain.\n");

  OUTSIDE;

  add_exit(DES+"d14","southeast", 0, 6);
  	reset_room();
}
