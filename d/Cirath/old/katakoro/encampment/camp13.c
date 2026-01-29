/*
* Created by: 
* Date: 
*
* File: /d/Cirath/katakoro/encampment/camp13.c
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
		"sizes.  For the most part these are homes to the members of "+
		"the Khahan's tribe.  In the northwest there is a large "+
		"sturdy looking yurt with several of soldiers passed out "+
		"in front of it.  The sounds coming from the inside suggest "+
		"the presence of bar of some sorts.\n");
	
   	add_item("yurt","This yurt looks to have been built a bit better "+
		"than those surrounding it, suggesting that it sees some "+
		"rough handling from time to time.  The unique smell of "+
		"fermented mares milk, or kumiss, a favored drink among "+
		"these people, floats on the gentle breeze.\n");

  	add_exit(KAT_CAMP + "camp12","north", 0, 1);  
  	add_exit(KAT_YURTS + "yurt8","enter", 0, 1, 1);
	reset_room();
}

