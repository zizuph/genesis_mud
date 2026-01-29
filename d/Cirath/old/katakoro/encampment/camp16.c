/*
* Created by: 
* Date: 
*
* File: /d/Cirath/katakoro/encampment/camp16.c
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
   	set_long("This area is surrounded by yurts of various shapes and "+
		"sizes. For the most part these are homes to the members of "+
		"the Khahan's tribe. In the northwest there is a yurt "+
		"attached to the smith's wagon.\n");

  	add_exit(KAT_CAMP + "camp15","north", 0, 1);  
  	add_exit(KAT_YURTS + "yurt9","enter", 0, 1, 1);
	reset_room();
}

