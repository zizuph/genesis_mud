/**********************************************************************
 * - vil1006.c                                                      - *
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
	return ({10, 6});
}

public int *
query_global_coords()
{
	return SAMORGAN_COORDS;
}
void
create_khalakhor_room()
{
	config_room("southern");
	
	add_item(({"west", "northeast"}),
	"There is a building in that direction.\n");
	add_item(({"northwest", "east"}),
	"The street continues in that direction.\n");
	add_item(({"southeast", "southwest", "south"}),
	"There is a rocky beach in that direction.\n");
	add_item(({"north"}),
	"There is a postal area in that direction.\n");
	
	
	add_exit("vil1007", "east");
	add_exit("post", "north");
	add_exit("vil0905", "northwest");
	add_fail(({"south", "southwest", "southeast"}),
	"The rocks make it impossible to go in that direction.\n");	
	add_fail(({"northeast"}),
	"A building blocks your passage.\n");

}
