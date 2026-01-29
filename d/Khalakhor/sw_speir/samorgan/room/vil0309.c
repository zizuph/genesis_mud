/**********************************************************************
 * - vil0309.c                                                      - *
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
	add_item(({"west", "southwest", "northwest"}),
           "There is a building in that direction.\n");
	add_item(({"north", "south"}),
           "The street continues in that direction.\n");
	add_item(({"northeast", "southeast"}),
           "A rocky beach is in that direction.\n");
	add_item(({"east"}),
           "There is a small house in that direction.\n");
	
	add_exit("vil0209", "north");
	add_exit("vil0409", "south");
  add_exit("house0310", "east");

	add_fail(({"west", "northwest", "southwest"}),
           "There is a building blocking your way.\n");
	add_fail(({"northeast", "southeast"}),
           "Rocks block the way.\n");
	

}
