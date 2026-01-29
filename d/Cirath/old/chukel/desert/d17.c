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
  set_short("On a mountain in a desert");
  set_long("In a desert on the eastern base of a large mountain.\n");

  OUTSIDE;

  add_exit(DES+"d13","west", 0, 6);
  add_exit(DES+"d22","east", 0, 6);
  add_exit(DES+"d18","south", 0, 6);
  	reset_room();
}
