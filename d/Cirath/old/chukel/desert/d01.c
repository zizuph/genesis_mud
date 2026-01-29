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
  	set_short("At a steep in the desert");
  	set_long("West end of desert. Steep cliff and bridge over Durni to Dohrath.\n");

  	OUTSIDE;

  	add_exit(DES + "d03", "east", 0, 6);
  	reset_room();
}
