/**********************************************************************
 * - vil0503.c                                                      - *
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
	return ({5, 3});
}

public int *
query_global_coords()
{
	return SAMORGAN_COORDS;
}

void
create_khalakhor_room()
{
	config_room("western");
	add_item(({"north", "southeast", "southwest", "northeast", "northwest"}),
	"There is a building in that direction.\n");
	add_item(({"west", "east", "south"}),
	"The street continues in that direction.\n");
	
	add_exit("vil0502", "west");
	add_exit("vil0504", "east");
	add_exit("vil0403", "north");
	
	add_fail("auto", "A building blocks your passage.\n");
}
