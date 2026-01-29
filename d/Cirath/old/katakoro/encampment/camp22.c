/*
* Created by: 
* Date: 
*
* File: /d/Cirath/katakoro/encampment/camp22.c
* Comments: edited by Luther Sept 2001
*/

inherit "/std/room.c";
#include "defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Cirath/common/mobber.h"

void
create_room()
{
  	set_short("Barbarian camp");
   	set_long("This is the eastern fringe of the encampment, there is "+
		"only a faint trail here, made by the guards that are assigned "+
		"to this area. Patches of white snow, green grass and brown "+
		"dirt break up the uniformity of the rolling hillocks.\n");

  	add_exit(KAT_CAMP + "camp24","west", 0, 1);  
  	add_exit(KAT_CAMP + "camp19","east", 0, 1);
	reset_room();
}

