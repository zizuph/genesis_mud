/**********************************************************************
 * - vil0509.c                                                      - *
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
	return ({5, 9});
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
	add_item(({"southwest", "northwest"}),
	"There is a building in that direction.\n");
	add_item(({"west", "north", "south", "east"}),
	"The street continues in that direction.\n");
	add_item(({ "northeast", "southeast"}),
	"A rocky beach is in that direction.\n");
	
	add_exit("vil0409", "north");
	add_exit("vil0609", "south");
	add_exit("vil0510", "east");
	add_exit("vil0508", "west");
	
	add_fail(({"northwest", "southwest"}),
	"A building blocks your passage.\n");
	add_fail(({"northeast", "southeast"}),
	"Rocks block your passage.\n");
	

}
