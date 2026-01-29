/**********************************************************************
 * - vil0504.c                                                      - *
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
	return ({6, 5});
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
	add_item(({ "southwest", "northeast", "northwest"}),
	"There is a building in that direction.\n");
	add_item(({"west", "east", "south"}),
	"The street continues in that direction.\n");
	add_item(({"north"}),
	"There is a postal office in that direction.\n");
	add_item(({"southeast"}),
	"The central square is in that direction.\n");
	
	add_exit("dshop", "north");
	add_exit("vil0604", "south");
	add_exit("vil0503", "west");
	add_exit("vil0505", "east");
	add_fail("auto", "A building blocks your passage.\n");
}
