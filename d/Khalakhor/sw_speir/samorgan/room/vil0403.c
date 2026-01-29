/**********************************************************************
 * - vil0403.c                                                      - *
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
	config_room("western");
	add_item(({"southeast", "west", "southwest", "east", "northeast", "northwest"}),
           "There is a building in that direction.\n");
	add_item(({"south", "north"}),
           "The street continues in that direction.\n");
	
	add_exit("vil0303", "north");
	add_exit("vil0503", "south");
  add_exit("house0404", "east");
	
	add_fail("auto", "A building blocks your passage.\n");
}
