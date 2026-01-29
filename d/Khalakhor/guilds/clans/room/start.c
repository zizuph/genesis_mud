/**********************************************************************
 * - start.c                                                        - *
 * - Clan Start room                                                - *
 * - Created by Damaris 05/2006                                     - *
 **********************************************************************/
#pragma strict_types

#include "../guild.h"
#include <stdproperties.h>

inherit GUILD_ROOM;

#include "lay.c"
#include "fireplace.c"

static public string *kilt;
static mapping select = ([ "MAX":0 ]);

nomask static int
select_kilt(string str)
{
	string verb = query_verb(), name;
	object ob;
	if ((str != "kilt"))
	{
		notify_fail("Select what? A kilt maybe?\n");
		return 0;
	}
	/* Are there any left to pick? */
	if (select["MAX"] >= KILT_LIMIT[1])
	{
		write(KILT_LIMIT[1]);
		return 1;
	}
	
	/* See if we select too many already */
	name = this_player()->query_name();
	if (select[name] >= KILT_LIMIT[0])
	{
		write(KILT_LIMIT[2]);
		return 1;
	}
	setuid();
	seteuid(getuid());
	clone_object(GOBJ + "kilt")->move(TP, 1);
	write("You look over the kilts on the shelf and select "+
	"one.\n");
	say(this_player()->query_name() + " looks over the kilts on "+
	"shelf and selects one.\n");
	
	/* Adjust the limits */
	select["MAX"]++;
	select[name]++;
	return 1;
}
void
create_guild_room()
{
	set_short("Sleeping room");
	set_long("   This is a sleeping room with a large fireplace "+
	"in the eastern wall that keeps this dimly lit room warm on "+
	"cold nights and also adds just enough light to allow for "+
	"vision of the comings and goings of clans. It is within "+
	"these walls that those who have announced their clan linage "+
	"may <start here> to rest their minds and bodies, if that is "+
	"their wish. ");
	add_item(({"area", "room"}), 
	"This is a sleeping room with a large fireplace "+
	"in the eastern wall that keeps this dimly lit room warm on "+
	"cold nights and also adds just enough light to allow for "+
	"vision of the comings and goings of clans. A small shelf "+
	"for holding kilts have been placed here as well. It is within "+
	"these walls that those who have announced their clan linage "+
	"may rest <start here> their minds and bodies, if that is "+
	"their wish.\n");
	add_my_desc(lay_desc, this_object());
	add_item(({"fur","furs", "mat", "mats", "sleeping mat", "sleeping mats"}), lay_desc);
	add_item(({"fireplace"}),
	"The fireplace is quite large with a holder placed on one side "+
	"with tools to stoke the fire and logs on the otherside to "+
	"place on the fire.\n");
	add_item(({"tool", "tools", "poker", "fireplace poker"}),
	"There are tools in a holder next to the fireplace so one can "+
	"stoke the fire.\n");
	add_item(({"log", "logs", "stack"}),
	"Logs for the fire are piled in a neat stack next to the "+
	"fireplace.\n");
	add_item(({"north"}),
	"An archway leading to the grand hall is in that direction.\n");
	add_item(({"east"}),
	"An archway leading to a meeting area is in that direction.\n");
	add_item(({"northeast"}),
	"An archway leading to the commons area is in that direction.\n");
	add_item(({"west", "southeast", "southwest", "northwest"}),
	"A wall is in that direction.\n");
	add_item(({"shelf"}),
	"There are kilts place on a shelf for clan members to choose.\n");
	add_item(({"kilt", "kilts"}),
	"You may <select kilt> to take one for the day.\n");
	
	add_prop(ROOM_I_INSIDE, 1);
	add_prop(ROOM_I_LIGHT, 1);
	
	add_exit("clan", "north");
	add_exit("cboard", "northeast");
	add_exit("board", "east");
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
	init_lay();
	init_fire();
	add_action(start, "start");
	add_action(select_kilt, "select");
}
