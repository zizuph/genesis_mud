/**********************************************************************
 * - vil0407.c                                                      - *
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
	return ({4, 7});
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
	add_item(({"southeast", "west", "southwest", "east", "northeast", "northwest"}),
	"There is a building in that direction.\n");
	add_item(({"south", "north"}),
	"The street continues in that direction.\n");
	
	add_exit("vil0307", "north");
	add_exit("vil0507", "south");
	
	add_fail("auto", "A building blocks your passage.\n");
}
