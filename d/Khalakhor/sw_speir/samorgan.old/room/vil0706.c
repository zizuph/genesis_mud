/**********************************************************************
 * - vil0706.c                                                      - *
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
	return ({7, 6});
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
	
	add_item(({"northeast", "southeast"}),
	"There is a building in that direction.\n");
	add_item(({"west", "north", "east", "southwest", "northwest"}),
	"The street continues in that direction.\n");
	add_item(({"south"}),
	"SaMorgan's armoury is in that direction.\n");
	
	add_exit("vil0606", "north");
	add_exit("ashop", "south");
	add_exit("vil0705", "west");
	add_exit("vil0707", "east");
	add_fail("auto", "A building blocks your passage.\n");

}
