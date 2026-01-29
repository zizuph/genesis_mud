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
  set_short("Near an oasis camp");
  set_long("In a desert, south of a camp in an oasis.\n");

  OUTSIDE;

  add_exit(DES+"oasis","north", 0, 6);
  add_exit(DES+"d21","east", 0, 6);
  	reset_room();
}
