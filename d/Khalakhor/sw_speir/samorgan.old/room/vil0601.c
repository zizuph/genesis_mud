/**********************************************************************
 * - vil0601.c                                                      - *
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
	return ({6, 1});
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
	add_item(({"northeast", "east", "southeast"}),
	"There is a building in that direction.\n");
	add_item(({ "north", "south"}),
	"The street continues in that direction.\n");
	add_item(({"west", "southwest", "northwest"}),
	"There is a rocky beach in that direction.\n");
	
	add_exit("vil0501", "north");
	add_exit("vil0701", "south");
	add_fail(({"west", "southwest", "northwest"}),
	"The rocks make this impossible to pass.\n");
	add_fail(({"southeast", "east", "northeast"}),
	"A building blocks your way.\n");
}
