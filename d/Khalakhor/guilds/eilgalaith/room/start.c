/**********************************************************************
 * - start.c                                                        - *
 * - Eil-Galaith Start room                                         - *
 * - Created by Damaris 08/Y2K                                      - *
 * - Recoded by Damaris 2/2002                                      - *
 * - Recoded by Damaris 4/2005                                      - *
 **********************************************************************/
#pragma strict_types

#include "../guild.h"
#include <stdproperties.h>

inherit GUILD_ROOM;

void
create_guild_room()
{
	set_short("An inner sanctum");
	set_long("   This is the inner sanctum of Eil-Galaith. This "+
	"room is small but has a warm inviting atmosphere with "+
	"tapestries and paintings covering the walls. You may <start "+
	"here> and make this your new home.\n");
	add_item(({"tapestry", "tapestries"}),
	"The tapestries are woven with elven flair and style. The silken "+
	"threads are colourful and produce a most spectacular vision "+
	"before you.\n");
	add_item(({"thread", "threads"}),
	"The threads used in the tapestries are vibrant and have been "+
	"woven by skilled elven hands.\n");
	add_item(({"painting", "paintings"}),
	"A skilled elven artist beautifully crafts the paintings. The "+
	"depictions of them are of the same theme, which is of elven "+
	"gardens and forest areas.\n");
	add_item(({"inner sanctum", "room", "sanctum"}),
	"This is a small room but has a warm inviting atmosphere "+
	"with tapestries and paintings covering the walls.\n");
	
	add_prop(ROOM_I_INSIDE, 1);

	add_exit("garden", "north");
	add_exit("entrance", "south");
	add_exit("train", "west");
	add_exit("board", "east");
	add_exit("crystal", "up");
	add_fail("auto", "You walked into a wall!\n"+
	"Ouch! That's gotta hurt!\n");
}

int
start(string str)
{
	if (str != "here")
	{
		notify_fail("Start here?\n");
		return 0;
	}
	if (!this_player()->query_guild_member(GUILD_NAME))
	{
		write("You are not a member of "+ GUILD_NAME + "!\n");
		return 1;
	}
	if (this_player()->set_default_start_location(STARTLOC))
	{
		write("Ok.\n");
	}
	else
	{
		write("Sorry, some problem prevents you from "+
		"starting here.\n");
	}
	return 1;
}

void
init()
{
	::init();
	add_action(start, "start");
}
