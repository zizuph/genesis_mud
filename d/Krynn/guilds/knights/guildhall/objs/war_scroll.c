/*
 * Filename:		war_scroll.c
 * Description:		The Grand Master can give this scroll to a player
 *					who will then be allowed to enter the war room.
 *
 *					NOTICE: This is an auto loading object!
 *
 * Copyright (c) 1999 by Daniel W. Mathiasen, Boron
 *
 * Revision history:
 * ----------------------
 *
 */
#include "/d/Krynn/common/defs.h"
#include "../../guild.h"

inherit "/std/scroll";

void
create_scroll()
{
	set_autoload();
	set_file(VOBJ + "/war_scroll.txt");

	set_name("scroll");
	add_adj(({"parchment"}));

	set_long("This is a scroll written on parchment of a high "
			+ "quality.\n");

    add_cmd_item("scroll", ({"destroy", "tear", "burn"/*, "eat"*/}),
                 ({"@@tear", "@@tear", "@@burn" /*, "@@eat"*/}));

}

string
tear()
{
	TO->remove_object();
	return "You tear the scroll a part!\n";
}

string
burn()
{
	TO->remove_object();
	return "You burn the scroll until there is nothing but light ashes left!\n"
			+ "The ashes blows away in the wind.\n";
}

void
eat()
{
	TO->remove_object();
	write("You chew on the scroll abit and swallow it!\n");
	TP->command("swallow");
	TP->command("burp");
}

void
enter_env(object dest, object old)
{
	dest->add_prop("_i_may_pass", 1);
}

void
leave_env(object old, object dest)
{
	old->remove("_i_may_pass");
	::leave_env(old, dest);
}

