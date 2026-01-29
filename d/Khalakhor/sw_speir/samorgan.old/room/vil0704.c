/**********************************************************************
 * - vil0704.c                                                      - *
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
	return ({7, 4});
}
public int *
query_global_coords()
{
	return SAMORGAN_COORDS;
}
void
create_khalakhor_room()
{
	set_xlong(({
	"Immediately south is SaMorgan's weaponry. The fishing village "+
	"of SaMorgan continues on in all directions.",
	"Directly south is SaMorgan's weaponry. The fishing village "+
	"of SaMorgan continues on in all directions.",
	"Precisely south is SaMorgan's weaponry. The fishing village "+
	"of SaMorgan continues on in all directions.",
	"Exactly south is SaMorgan's weaponry. The fishing village "+
	"of SaMorgan continues on in all directions.",}));
	
	config_room("central");
	
	add_item(({"southeast", "southwest", "northwest"}),
	"There is a building in that direction.\n");
	add_item(({"west", "north", "east", "northeast"}),
	"The street continues in that direction.\n");
	add_item(({"south"}),
	"SaMorgan's weaponry is in that direction.\n");
	
	add_exit("vil0604", "north");
	add_exit("wshop", "south");
	add_exit("vil0703", "west");
	add_exit("vil0705", "east");
	
	add_fail("auto", "A building blocks your passage.\n");
}
