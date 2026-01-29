/**********************************************************************
 * - vil0401.c                                                      - *
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
	return ({4, 1});
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
	
	add_exit("vil0301", "north");
	add_exit("vil0501", "south");
	
	add_fail(({"west", "southwest", "northwest"}),
	"Rocks block your passage.\n");
	add_fail(({"northeast", "southeast", "east"}),
	"A building stops your passage.\n");

}
