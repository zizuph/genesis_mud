/**********************************************************************
 * - vil0708.c                                                      - *
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
	return ({7, 8});
}

public int *
query_global_coords()
{
	return SAMORGAN_COORDS;
}
void
create_khalakhor_room()
{
	config_room("eastern");
	
	add_item(({"southeast", "south", "northeast"," northwest", "north", "southwest"}),
	"There is a building in that direction.\n");
	add_item(({"west","east"}),
	"The street continues in that direction.\n");
	add_exit("vil0707", "west");
	add_exit("vil0709", "east");
	add_fail("auto", "A building blocks your passage.\n");
}
