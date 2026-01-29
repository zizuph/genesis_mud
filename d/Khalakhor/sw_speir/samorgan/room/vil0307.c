/**********************************************************************
 * - vil0307.c                                                      - *
 * - Village room.                                                  - *
 * - Created by Damaris@Genesis 02/2005                             - *
 * - Tidied up and optimized by Tapakah, 05/2021                    - *
 **********************************************************************/

#pragma strict_types

#include "../defs.h"

inherit SM_STREET_BASE;

void
create_khalakhor_room()
{
	config_room("eastern");
	add_item(({"southeast", "southwest", "northeast", "northwest"}),
           "There is a building in that direction.\n");
	add_item(({"west"}),
           "There is a clothing shop in that direction.\n");
	add_item(({"east"}),
           "There is a small house in that direction.\n");
	add_item(({"south", "north"}),
           "The street continues in that direction.\n");
	
	add_exit("vil0207", "north");
	add_exit("vil0407", "south");
	add_exit("house0308", "east");
	add_fail("auto", "A building blocks your passage.\n");
}
