/**********************************************************************
 * - vil0606.c                                                      - *
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
	return ({6, 6});
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
	add_item(({"southwest", "north", "south", "northwest"}),
	"The street continues in that direction.\n");
	add_item(({"east"}),
	"The Hall of records is in that direction.\n");
	
	add_item(({"west"}),
	"The central square is in that direction.\n");
	
	add_exit("vil0506", "north");
	add_exit("vil0706", "south");
	add_exit("bank", "east");
	add_exit("well", "west");
	add_exit("vil0505", "northwest");
	add_exit("vil0705", "southwest");
	add_fail("auto", "A building blocks your passage.\n");

}
