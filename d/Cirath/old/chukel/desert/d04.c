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
  	set_long("East part of desert on south base of a mountain.\n");

  	OUTSIDE;

  	add_exit(DES+"d03","north", 0, 6);
  	add_exit(DES+"d07","southeast", 0, 6);
  	reset_room();
}
