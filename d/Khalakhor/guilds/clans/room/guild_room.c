/**********************************************************************
 * - guild_room.c                                                   - *
 * - Clan Guild base_room                                           - *
 * - Created by Damaris 05/2006                                     - *
 **********************************************************************/

#include "../guild.h"
#include <macros.h> /* For the Q macros in messages.. */
#include <stdproperties.h> /* for room props */


inherit "/d/Khalakhor/std/room";

void
create_guild_room()
{
}

nomask void
create_khalakhor_room()
{
	/* To set the short desc. in the rooms. */
	set_short("Guild room of Clans");
	/* To set the long desc. in room. */
	set_long("   Guild room of Clans.\n");
	
	/* To add items to be examined in rooms. */
	add_item(({"light", "light source"}),
	"Large torches light up this area.\n");
	add_item(({"torch", "torches"}),
	"The torches are attached to the walls and are lit adding light "+
	"to this area.\n");
	add_item(({"wall", "walls"}),
	"The walls are made from large grey stones.\n");
	add_item(({"ceiling"}),
	"The ceiling is high but nothing too special.\n");
	add_item(({"floor", "flooring"}),
	"The floor is made from hard wood.\n");
	add_item(({"stone", "stones"}),
	"The stones are grey in colour and are pieced together to create "+
	"the walls.\n");
	add_item(({"wood", "hard wood"}),
	"The wood is hard and makes up the flooring.\n");
	add_item(({"arch", "arches", "archway", "archways"}),
	"The archway leads to another area.\n");
	add_item(({"down"}),
	"It is a floor.\n");
	add_item(({"up"}),
	"A simple ceiling.\n");	
	create_guild_room();
}
