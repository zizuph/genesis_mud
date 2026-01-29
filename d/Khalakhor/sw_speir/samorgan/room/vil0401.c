/**********************************************************************
 * - vil0401.c                                                      - *
 * - Village room.                                                  - *
 * - Created by Damaris@Genesis 02/2005                             - *
 * - Tidied up and optimized by Tapakah, 05/2021                    - *
 **********************************************************************/

#pragma strict_types

#include "../defs.h"

inherit SAMORGAN_BASE;

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
	
	add_exit("vil0301", "north");
	add_exit("vil0501", "south");
  add_exit("house0402", "east");
	
	add_fail(({"west", "southwest", "northwest"}),
           "Rocks block your passage.\n");
	add_fail(({"northeast", "southeast"}),
           "A building stops your passage.\n");

}
