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
  set_short("By a river in the desert");
  set_long("Southeast part of desert close to a mountain and "+
    "north of a river.\n");

  OUTSIDE;

  add_exit(DES+"d04","northwest", 0, 6);
  add_exit(DES+"d11","east", 0, 6);
  	reset_room();
}
