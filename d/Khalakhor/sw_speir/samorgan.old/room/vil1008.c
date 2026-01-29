/**********************************************************************
 * - vil1007.c                                                      - *
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
	return ({10, 7});
}

public int *
query_global_coords()
{
	return SAMORGAN_COORDS;
}
void
create_khalakhor_room()
{
	config_room("southern");
	
	add_item(({"northwest"}),
	"There is a building in that direction.\n");
	add_item(({"north" }),
	"There is a tavern in that direction.\n");
	
	add_item(({"west", "northeast"}),
	"The street continues in that direction.\n");
	add_item(({"southeast", "southwest", "south", "east"}),
	"There is a rocky beach in that direction.\n");
	
	add_exit("pub", "north");
	add_exit("vil1007", "west");
	add_exit("vil0909", "northeast");
	
	add_fail(({"northwest"}),
	"A building blocks your passage.\n");
	add_fail("east", "The pier is under construction at this time.\n");
	add_fail(({"south", "southeast", "southwest"}),
	"The rocks make it impossible to go that way.\n");
	
}
