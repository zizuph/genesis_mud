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
  set_short("In a desert close to a river");
  set_long("In a desert, north of a quite large river that "+
    "bends south here.\n");

  OUTSIDE;

  add_exit(DES+"d37","east", 0, 6);
  add_exit(DES+"d34","northwest", 0, 6);
  	reset_room();
}
