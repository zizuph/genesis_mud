/**********************************************************************
 * - vil0507.c                                                      - *
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
	return ({5, 9});
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
	add_item(({"southeast", "northwest", "south", "northeast", "southwest"}),
	"There is a building in that direction.\n");
	add_item(({"west","north", "east"}),
	"The street continues in that direction.\n");
	
	add_exit("vil0508", "east");
	add_exit("vil0506", "west");
	add_exit("vil0407", "north");
	
	add_fail("auto", "A building blocks your passage.\n");
}
