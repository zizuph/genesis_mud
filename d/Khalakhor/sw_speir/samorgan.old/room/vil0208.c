/**********************************************************************
 * - vil0208.c                                                      - *
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
	return ({2, 8});
}

public int *
query_global_coords()
{
	return SAMORGAN_COORDS;
}

#define GUILD "/d/Khalakhor/guilds/defenders/room/entrance"

void
create_khalakhor_room()
{
	config_room("northern");
	add_item(({"southeast", "south", "southwest"}),
	"There is a building in that direction.\n");
	add_item(({"west", "east"}),
	"The street continues in that direction.\n");
	add_item(({"northeast", "northwest"}),
	"A forest is in that direction.\n");
	add_item(({"north"}),
	"A large building is in that direction.\n");	
	
//	add_exit(GUILD, "north");
	add_exit("vil0207", "west");
	add_exit("vil0209", "east");
	add_fail(({"north"}),
	"The Grand Hall is closed right now.\n");
	add_fail(({"northeast", "northwest"}),
	"Large thick trees block the way.\n");
	add_fail(({"southwest", "south", "southeast"}),
	"There is a building blocking your way.\n");

}
