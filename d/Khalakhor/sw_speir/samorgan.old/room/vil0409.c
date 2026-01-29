/**********************************************************************
 * - vil0409.c                                                      - *
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
	return ({4, 9});
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
	
	add_item(({"west", "southwest", "northwest"}),
	"There is a building in that direction.\n");
	add_item(({"north", "south"}),
	"The street continues in that direction.\n");
	add_item(({"east", "northeast", "southeast"}),
	"A rocky beach is in that direction.\n");
	
	add_exit("vil0309", "north");
	add_exit("vil0509", "south");
	
	add_fail(({"northeast", "southeast", "east"}),
	"Rocks block the way.\n");
	add_fail(({"northwest", "southwest"}),
	"There is a building blocking your way.\n");

}
