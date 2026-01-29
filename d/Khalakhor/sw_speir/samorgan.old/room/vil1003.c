/**********************************************************************
 * - vil1003.c                                                      - *
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
	return ({10, 3});
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
	
	add_item(({"north", "northeast", "northwest"}),
	"There is a building in that direction.\n");
	add_item(({"west", "east"}),
	"The street continues in that direction.\n");
	add_item(({"south",  "southwest", "southeast"}),
	"There is a rocky beach in that direction.\n");
	
	add_exit("vil1002", "west");
	add_exit("vil1004", "east");
	add_fail(({"south","southwest", "southeast"}),
	"The rocks make it impossible to go in that direction.\n");	
	add_fail(({"northwest", "northeast", "north"}),
	"A building blocks your passage.\n");

}
