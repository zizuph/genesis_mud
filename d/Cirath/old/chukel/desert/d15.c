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
  set_long("In a desert on southeastern base of a mountain.\n");

  OUTSIDE;

  add_exit(DES+"d10","west", 0, 6);
  add_exit(DES+"d18","northeast", 0, 6);
  add_exit(DES+"d19","southeast", 0, 6);
  	reset_room();
}
