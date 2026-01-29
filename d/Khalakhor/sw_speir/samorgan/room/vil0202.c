/**********************************************************************
 * - vil0202.c                                                      - *
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
	return ({2, 2});
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
	add_item(({"northeast", "northwest"}),
	"There is a forest in that direction.\n");
	
	add_exit("vil0203", "east");
	add_exit("vil0201", "west");
	
	add_fail(({"north", "northeast", "northwest"}),
	"Large thick trees block the way.\n");
	add_fail(({"south", "southwest", "southeast"}),
	"There is a building blocking your way.\n");

}
