/*
* Created by: Asmodean
* Date: March 18, 1995
*
* File: /d/Cirath/katakoro/almorel/lk1.c
* Comments: BG - Property of Cirath Domain, edited by Luther Oct. 2001
*/

#pragma strict_types
#pragma save_binary

#include "defs.h"

inherit LAKE_MASTER;

void
create_lakeside()
{
    	set_short("Lakeside");
    	set_long("You are on a wide street that winds up and down the "+
        	"shore of the Lake of Mists. The street is covered in "+
		"packed snow and ice. All around you are single story "+
		"houses with strangely slanted rooves. The street "+
		"continues to the Northeast and South. Through the fog "+
		"to the west, the Tower of Raumkreml can be seen towering "+
		"above the shoreline.\n\n");

    	add_exit(KAT_ALMO + "rd4", "south", 0, 1);
    	add_exit(KAT_ALMO + "lk2", "northeast", 0, 1);
    	reset_room();
}
