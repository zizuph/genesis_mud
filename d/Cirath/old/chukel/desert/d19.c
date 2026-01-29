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
  set_long("In a desert. North of a river and southeast "+
    "of a large mountain.\n");

  OUTSIDE;

  add_exit(DES+"d15","northwest", 0, 6);
  add_exit(DES+"d25","southeast", 0, 6);
  	reset_room();
}
