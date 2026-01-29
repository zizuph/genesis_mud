/**********************************************************************
 * - vil1002.c                                                      - *
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
	return ({10, 2});
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
	add_item(({ "north", "northeast"}),
	"There is a building in that direction.\n");
	add_item(({"east", "northwest"}),
	"The street continues in that direction.\n");
	add_item(({"west", "southwest", "southeast"}),
	"There is a rocky beach in that direction.\n");
	add_item(({"south"}),
	"Some sort of fishing pier is being built.\n");	
	
	add_exit("vil0901", "northwest");
	add_exit("vil1003", "east");
	
	add_fail(({"west", "southwest", "southeast"}),
	"The rocks make it impossible to go in that direction.\n");
	add_fail(({"south"}),
	"The pier is still under construction.\n");	
	add_fail(({"northeast", "north"}),
	"A building blocks your passage.\n");

}
