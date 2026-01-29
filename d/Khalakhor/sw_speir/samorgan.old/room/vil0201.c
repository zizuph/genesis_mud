/**********************************************************************
 * - vil0301.c                                                      - *
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
	return ({3, 1});
}

public int *
query_global_coords()
{
	return SAMORGAN_COORDS;
}
void
create_khalakhor_room()
{
	config_room("northern");
	add_item(({"southeast", "northeast"}),
	"There is a building in that direction.\n");
	add_item(({"south", "east"}),
	"The street continues in that direction.\n");
	add_item(({"west", "southwest", "northwest"}),
	"There is a rocky beach in that direction.\n");
	add_item(({"north"}),
	"There is a forest in that direction.\n");
		
	add_exit("vil0202", "east");
	add_exit("vil0301", "south");

	add_fail(({"west", "southwest", "northwest"}),
	"Rocks block your passage.\n");
	add_fail(({"northeast", "southeast"}),
	"A building stops your passage.\n");
	add_fail(({"north"}),
	"The trees are too thick making passage impossible.\n");
}
