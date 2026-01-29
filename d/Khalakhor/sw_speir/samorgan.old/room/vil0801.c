/**********************************************************************
 * - vil0801.c                                                      - *
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
	return ({8, 1});
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
	add_item(({"northeast", "east", "southeast"}),
	"There is a building in that direction.\n");
	add_item(({ "north", "south"}),
	"The street continues in that direction.\n");
	add_item(({"west", "southwest", "northwest"}),
	"There is a rocky beach in that direction.\n");
	
	add_exit("vil0701", "north");
	add_exit("vil0901", "south");

        add_fail(({"southwest", "northwest", "west"}),
        "The rocks make it impossible to go in that direction.\n");
        add_fail(({"northeast", "east"}),
        "A building blocks your passage.\n");
}
