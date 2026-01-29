/**********************************************************************
 * - vil0505.c                                                      - *
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
	return ({5, 5});
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
	
	add_item(({"northeast", "northwest"}),
	"There is a building in that direction.\n");
	add_item(({"west", "east"}),
	"The street continues in that direction.\n");
	add_item(({"north"}),
	"There is a shop in that direction.\n");
	add_item(({"southeast", "south", "southwest"}),
	"The central square is in that direction.\n");	
	add_exit("gshop", "north");	
	add_exit("well", "south");
	add_exit("vil0504", "west");
	add_exit("vil0506", "east");
	add_exit("vil0604", "southwest");
	add_exit("vil0606", "southeast");
	add_fail("auto", "A building blocks your passage.\n");
}
