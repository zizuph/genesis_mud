/**********************************************************************
 * - vil0301.c                                                      - *
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
	
	add_item(({"northeast", "east", "southeast"}),
           "There is a building in that direction.\n");
	add_item(({ "north", "south"}),
           "The street continues in that direction.\n");
	add_item(({"west", "southwest", "northwest"}),
           "There is a rocky beach in that direction.\n");
	
	add_exit("vil0201", "north");
	add_exit("vil0401", "south");
  add_exit("house0302", "east");

	add_fail(({"west", "southwest", "northwest"}),
           "Rocks block your passage.\n");
	add_fail(({"northeast", "southeast"}),
           "A building stops your passage.\n");
}
