/**********************************************************************
 * - vil0604.c                                                      - *
 * - Village room.                                                  - *
 * - Created by Damaris@Genesis 02/2005                             - *
 **********************************************************************/
#pragma strict_types
#include "../defs.h"
inherit SAMORGAN_BASE;
#include <macros.h>
#include <stdproperties.h>

/*********************************************************************
 * - This adds the gks to the room so NPC's know where they are.   - *
 *********************************************************************/
public int *
query_local_coords()
{
	return ({6, 4});
}

public int *
query_global_coords()
{
	return SAMORGAN_COORDS;
}

void
create_khalakhor_room()
{
	config_room("central");
	add_item(({"northwest", "southwest"}),
	"There is a building in that direction.\n");
	add_item(({"southeast", "north", "south", "northeast"}),
	"The street continues in that direction.\n");
	add_item(({"west"}),
	"There is a pub in that direction.\n");
	add_item(({"east"}),
	"The central square is in that direction.\n");
	
	add_exit("vil0504", "north");
	add_exit("vil0704", "south");
	add_exit("board", "west");
	add_exit("well", "east");
	add_exit("vil0505", "northeast");
	add_exit("vil0705", "southeast");
	add_fail("auto", "A building blocks your passage.\n");
}
