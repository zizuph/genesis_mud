/**********************************************************************
 * - vil1004.c                                                      - *
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
	return ({10, 4});
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
	add_item(({"north", "east", "northwest"}),
	"There is a building in that direction.\n");
	add_item(({"northeast","west"}),
	"The street continues in that direction.\n");
	add_item(({"south", "southwest", "southeast",}),
	"There is a rocky beach in that direction.\n");
	
	add_exit("delivery", "north");	
	add_exit("vil1003", "west");
	add_exit("vil0905", "northeast");
	add_fail(({"south", "east", "southwest", "southeast"}),
	"The rocks make it impossible to go in that direction.\n");	
	add_fail(({"northwest"}),
	"A building blocks your passage.\n");

}
