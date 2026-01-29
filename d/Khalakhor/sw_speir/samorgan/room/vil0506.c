/**********************************************************************
 * - vil0506.c                                                      - *
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
	return ({5, 6});
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
	add_item(({ "southeast", "northeast", "northwest"}),
	"There is a building in that direction.\n");
	add_item(({"west", "east", "south"}),
	"The street continues in that direction.\n");
	add_item(({"north"}),
	"There is a message center in that direction.\n");
	add_item(({"southwest"}),
	"The central square is in that direction.\n");
	
	add_exit("mshop", "north");
	add_exit("vil0606", "south");
	add_exit("vil0505", "west");
	add_exit("vil0507", "east");
	add_fail(({"northeast", "northwest", "southwest", "southeast"}),
	"A building blocks your passage.\n");
}
