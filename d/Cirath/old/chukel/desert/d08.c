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
  set_long("Northeast part of desert on north base of "+
    "a mountain.\n");

  OUTSIDE;

  add_exit(DES+"d05","west", 0, 6);
  add_exit(DES+"d12","southeast", 0, 6);
  	reset_room();
}
