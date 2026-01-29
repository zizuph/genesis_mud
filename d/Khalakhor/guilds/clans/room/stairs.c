/**********************************************************************
 * - stairs.c                                                       - *
 * - Stairwell that leads to the private areas of the Khalakhor     - *
 * - Clans race guild.                                              - *
 * - Created by Damaris 05/2006                                     - *
 **********************************************************************/
#pragma strict_types

#include "../guild.h"
#include <macros.h>
#include <stdproperties.h>
#include "/d/Khalakhor/sys/basic.h"

inherit GUILD_ROOM;

public int
members_only()
{
	if (IS_MEMBER(this_player()) || this_player()->query_wiz_level())
	{
		/* Is a member, pass through as normal */
		return 0;
	}
	write("You may not go this way as you are not of a "+
	"Khalakhor Clan!\n");
	return 1;
}

void
create_guild_room()
{
	set_short("Large stairwell");
	set_long("   This large stairwell is unadorned and quite plain "+
	"with little to show but grey stonewalls. There are large "+
	"torches burning brightly following along the wall up the "+
	"large stone steps that lead to the private area above.\n");
	add_item(({"stairs", "stairwell","room", "area"}), query_long);
	add_item(({"north", "east", "south", "southwest", "southeast", "northeast", "northwest"}),
	"There is a wall in that direction.\n");
	add_item(({"west"}),
	"There is an archway leading back to the hall in that "+
	"direction.\n");
	
	add_prop(ROOM_I_INSIDE, 1);
	add_prop(ROOM_I_LIGHT, 1);
	add_exit("cboard", "up", members_only);
	add_exit("entrance", "west");
	add_fail("auto", "A wall stops you.\n");
}
