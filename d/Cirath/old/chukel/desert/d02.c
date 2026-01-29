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
  	set_long("East part of desert on a top of a mountain.\n");

  	OUTSIDE;

  	add_exit(DES+"d03","south", 0, 6);
  	add_exit(DES+"d06","northeast", 0, 6);
  	reset_room();
}
