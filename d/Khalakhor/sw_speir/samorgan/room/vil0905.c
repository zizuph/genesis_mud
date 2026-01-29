/**********************************************************************
 * - vil0905.c                                                      - *
 * - Village room.                                                  - *
 * - Created by Damaris@Genesis 02/2005                             - *
 **********************************************************************/
#pragma strict_types
#include "../defs.h"
inherit SAMORGAN_BASE;
#include <macros.h>
#include <stdproperties.h>
#define PIE1005 "/d/Khalakhor/sw_speir/samorgan/pier/pie1005" 
/*********************************************************************
 * - This adds the gks to the room so NPC's know where they are.   - *
 *********************************************************************/
public int *
query_local_coords()
{
	return ({9, 5});
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
	
	add_item(({"northwest", "northeast"}),
	"There is a building in that direction.\n");
	add_item(({"southwest", "north", "southeast"}),
	"The street continues in that direction.\n");
	add_item(({"west"}),
	"There is a delivery office in that direction.\n");
	add_item(({"east"}),
	"The postal area is in that direction.\n");
	add_item(({"south"}),
	"The docks are in that direction.\n");
	add_item(({"dock", "docks", "pier", "piers"}),
	"The docks are towards the south.\n");
	
	add_exit("vil0805", "north");
	add_exit(PIE1005, "south");
	add_exit("vil1006", "southeast");
	add_exit("vil1004", "southwest");
	add_exit("delivery", "west");
	add_exit("post","east");
	
	add_fail("auto", "A building blocks your passage.\n");

}
