/**********************************************************************
 * - vil0709.c                                                      - *
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
	return ({7, 9});
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
	
	add_item(({"southwest", "northwest"}),
	"There is a building in that direction.\n");
	add_item(({"southeast", "east", "northeast"}),
	"A rocky beach is in that direction.\n");
	add_item(({"west","north", "south"}),
	"The street continues in that direction.\n");
	
	add_exit("vil0708", "west");
	add_exit("vil0609", "north");
	add_exit("vil0809", "south");
	add_fail(({"northwest", "southwest"}),
	"A building blocks your passage.\n");
	add_fail(({"northeast", "southeast", "east"}),
	"Rocks block your passage.\n");
}
