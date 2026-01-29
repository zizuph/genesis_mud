/**********************************************************************
 * - vil0205.c                                                      - *
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
	return ({2, 5});
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
	add_item(({"southeast", "south", "southwest"}),
	"There is a building in that direction.\n");
	add_item(({"west", "east"}),
	"The street continues in that direction.\n");
	add_item(({"northeast", "north", "northwest"}),
	"There is a forest in that direction.\n");
	
	add_exit("vil0204", "west");
	add_exit("vil0206", "east");

	add_fail(({"north", "northeast", "northwest"}),
	"Large thick trees block the way.\n");
	add_fail(({"southwest", "south", "southeast"}),
	"There is a building blocking your way.\n");

}
