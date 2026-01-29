/**********************************************************************
 * - vil0705.c                                                      - *
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
	return ({7, 5});
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
	"Immediately southwest is SaMorgan's weaponry and to the "+
	"southeast is the armoury. Sounds of laughter coming from "+
	"the village square that is just north from here. The "+
	"fishing village of SaMorgan continues on in all directions.",
	"Directly southwest is SaMorgan's weaponry and to the "+
	"southeast is the armoury. The faint sounds of people talking "+
	"filter in from the village square just north of here. The "+
	"fishing village of SaMorgan continues on in all directions.",
	"Precisely southwest is SaMorgan's weaponry and to the "+
	"southeast is the armoury. The village square is just north "+
	"from here. The fishing village of SaMorgan continues on in "+
	"all directions.",
	"Exactly southwest is SaMorgan's weaponry and to the "+
	"southeast is the armoury. Splashes can be heard from the north. "+
	"The fishing village of SaMorgan continues on in all "+
	"directions.",}));
	
	config_room("central");
	
	add_item(({"southeast"}),
	"SaMorgan's Armoury is in that direction.\n");
	add_item(({"southwest"}),
	"SaMorgan's Weaponry is in that direction.\n");
	add_item(({"north"}),
	"The village square with a large well is in that direction.\n");	
	add_item(({"west", "east", "south", "northeast", "northwest"}),
	"The street continues in that direction.\n");
	
	add_exit("well", "north");
	add_exit("vil0805", "south");
	add_exit("vil0706", "east");
	add_exit("vil0704", "west");
	add_exit("vil0604", "northwest");
	add_exit("vil0606", "northeast");
	add_exit("wshop", "southwest");
	add_exit("ashop", "southeast");
	add_fail("auto", "A building blocks your passage.\n");
}
