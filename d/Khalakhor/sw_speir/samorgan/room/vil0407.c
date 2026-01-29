/**********************************************************************
 * - vil0407.c                                                      - *
 * - Village room.                                                  - *
 * - Created by Damaris@Genesis 02/2005                             - *
 **********************************************************************/
#pragma strict_types
#include "../defs.h"
inherit SAMORGAN_BASE;
#include <macros.h>
#include <stdproperties.h>

void
create_khalakhor_room()
{
	config_room("eastern");
	add_item(({
             "southeast", "southwest", "west", "northeast", "northwest"
           }),
           "There is a building in that direction.\n");
	add_item(({"south", "north"}),
           "The street continues in that direction.\n");
	add_item(({"east"}),
           "There is a small house in that direction.\n");
	
	add_exit("vil0307", "north");
	add_exit("vil0507", "south");
	add_exit("house0408", "east");
  
	add_fail("auto", "A building blocks your passage.\n");
}
