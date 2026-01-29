/**********************************************************************
 * - vil0901.c                                                      - *
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
	return ({9, 1});
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
	add_item(({"northeast", "east"}),
	"There is a building in that direction.\n");
	add_item(({ "north", "southeast"}),
	"The street continues in that direction.\n");
	add_item(({"southwest", "northwest", "south"}),
	"There is a rocky beach in that direction.\n");
        add_item(({"west"}),
        "Some sort of fishing pier is being built.\n");	
	
	add_exit("vil0801", "north");
	add_exit("vil1002", "southeast");

        add_fail(({"southwest", "northwest", "south"}),
        "The rocks make it impossible to go in that direction.\n");
        add_fail(({"west"}),
        "The pier is still under construction.\n");     
        add_fail(({"northeast", "east"}),
        "A building blocks your passage.\n");
}
