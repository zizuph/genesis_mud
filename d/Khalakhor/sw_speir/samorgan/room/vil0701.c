/**********************************************************************
 * - vil0701.c                                                      - *
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
	return ({7, 1});
}
public int *
query_global_coords()
{
	return SAMORGAN_COORDS;
}
void
create_khalakhor_room()
{
	config_room("western");
	add_item(({"southeast", "northeast"}),
	"There is a building in that direction.\n");
	add_item(({"north","south", "east" }),
	"The street continues in that direction.\n");
	add_item(({"west", "northwest", "southwest"}),
	"There is a rocky beach in that direction.\n");
	
	add_exit("vil0601", "north");
	add_exit("vil0801", "south");
	add_exit("vil0702", "east");

        add_fail(({"southwest", "northwest", "west"}),
        "The rocks make it impossible to go in that direction.\n");
        add_fail(({"northeast", "southeast"}),
        "A building blocks your passage.\n");

}
