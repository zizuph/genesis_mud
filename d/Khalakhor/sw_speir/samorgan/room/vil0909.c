/**********************************************************************
 * - vil0909.c                                                      - *
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
	return ({9, 9});
}

public int *
query_global_coords()
{
	return SAMORGAN_COORDS;
}
void
create_khalakhor_room()
{
	config_room("southeastern");
	add_item(({ "west", "northwest"}),
	"There is a building in that direction.\n");
	add_item(({"north", "southwest",}),
	"The street continues in that direction.\n");
	add_item(({"southeast", "south", "northeast", "east"}),
	"There is a rocky beach in that direction.\n");
	
	add_exit("vil0809", "north");
	add_exit("vil1008", "southwest");
	add_fail("auto", "A building blocks your passage.\n");
}
