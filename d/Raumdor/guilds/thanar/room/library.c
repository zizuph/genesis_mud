/**********************************************************************
 * - library.c                                                      - *
 * - A small library for Thanar                                     - *
 * - Created by Damaris@Genesis 3/2004                              - *
 **********************************************************************/

#pragma strict_types

#include "../guild.h"
#include <stdproperties.h>

inherit GUILD_ROOM;
inherit "/d/Raumdor/lib/library";

#include "seated.c"
#include "fireplace.c"
/*
 * Function name: library_exit_block
 * Description:   Check to see if the player is carrying a library
 *                scroll.  This is meant to be used as a block function
 *                for exits from the library so that scrolls cannot be
 *                removed.
 * Returns:       1/0 - scroll carried/not carried
 */
public int
library_exit_block()
{
    /* See if the player is carrying a scroll */
    if (::library_exit_block())
    {
    /* A scroll was found.  Give a warning and return 1 to block the exit */
    write("A magical force prevents you from leaving.\n" +
        "You must be carrying a scroll.\n");
    return 1;
    }

    /* No scroll present.  Return 0 to allow the player to exit */
    return 0;
}

void
create_guild_room()
{
	set_short("library");
	set_long("    This is the library that was founded by devout "+
	"clerics of Thanar. You will find many shelves that have "+
	"scrolls placed neatly on them. The clerics have placed them "+
	"here for your information and continued study of Thanar and his "+
	"cause. There are a few wooden tables and chairs situated "+
	"around them invitingly. There are tapestries on the walls. A "+
	"sign has been placed here also that will assist you in your "+
	"knowledge.\n");
	add_item(({"shelf", "shelves"}),
	"The shelves are made from marble and are attached to the "+
	"walls.\n");
	add_item(({"table", "tables"}),
	"The tables are made from dark wood and they have a few "+
	"chairs around them.\n");
	add_item(({"chair", "chairs"}),
	"The chairs are made of dark wood and are scattered invitingly "+
	"around the tables.\n");
	add_item(({"scroll", "scrolls"}),
	"There are scrolls filling the shelves, you may try reading the "+
	"sign to find out how you may read one.\n");
	add_item(({"tapestry", "tapestries"}),
	"The tapestries are made with vibrant silken threads. Finely "+
	"crafted with human hands depicting elves in various "+
	"vocations.\n");
	add_item(({"thread", "threads"}),
	"The silken threads which make of the tapestries are vibrant and "+
	"give depth to each tapestry.\n");
	add_item(({"hall", "library", "room"}), query_long);
	add_item(({"fireplace"}),
	"The fireplace is lit with a nice warm glowing fire.\n");
	add_item(({"mantle"}),
	"The mantle is large and made for the same marble the walls "+
	"and flooring is made from.\n");
	add_item(({"fire"}),
	"The fire dances with golden light which fills the hall with "+
	"warmth and peace.\n");
	
	/* Add an exit using library_exit_block() to be sure that no-one
	* leaves the library with a scroll
	*/
	add_exit("hall1", "south", library_exit_block);
	add_exit("start", "east");
	
	add_prop(ROOM_I_INSIDE, 1);
	add_prop(ROOM_I_NO_ATTACK, 1);
	add_prop(ROOM_I_NO_MAGIC_ATTACK, 1);
	/* Indicate that we want players to have to "borrow" a scroll in
	* order to read it.
	*/
	set_borrow_required(1);
	/* This is the directory where approved scrolls are saved */
	set_scroll_directory(SCROLLS);
	/* This is the directory where scrolls that need approval 
	 * are saved
	 */
	set_scroll_approval_directory(SCROLLS + "approval/");
	/* This is the directory where scrolls that have been denied 
	 * or discarded are saved.
	 */
	set_scroll_removal_directory(SCROLLS + "removed/");
	
	/* Add shelves to the library so that scrolls can be classified 
	 * under different categories.  Note that for each shelf you must 
	 * add a subdirectory with the same name under the base directory 
	 * specified with set_scroll_directory().
	 */
	add_scroll_shelf(({ "general", "history", "lineage" }));
	create_library();
	
	/* Add a sign that gives instructions on how to use the library */
	add_item("sign", library_help());
	add_cmd_item("sign","read", library_help());
	
	add_item(({"chair","chairs"}), seat_desc);
	add_my_desc(seat_desc, this_object());
}

void
init()
{
	::init();
	/* Add the library commands */
	init_library();
	init_seat();
	init_fire();
}

public mixed
library_hook_get_approval_names()
{
	return SERVER->query_librarians();
}

/*
 * Function name: library_admin_access
 * Description:   Limit library administration abilities to certain
 *                people.
 * Returns:       1 - this_player() has administration powers
 *                0 - this_player() does not have administration powers
 */
public int
library_admin_access()
{
	mixed *dat;
	string name;
	name = this_player()->query_real_name();
	
	/* We'll give admin access to wizards */
	if (this_player()->query_wiz_level()  || ( sizeof(dat = SERVER->query_member(name))  && dat[SPEC] == 1) )
	{
		return 1;
	}
	/* No-one else has admin access */
        write("You do not have permission to do that.\n");
        return 0;
}

public int
library_deny_access()
{

}

/*
 * Function name: library_write_access
 * Description:   Limit permission to write scrolls to certain people
 * Returns:       1 - this_player() is allowed to write
 *                0 - this_player() is not allowed to write
 */
public int
library_write_access()
{
	/* We'll allow any member of the racial guild  to write scrolls
	 */
	if (IS_MEMBER(this_player()))
	{
		return 1;
	}
	/* We'll allow wizards to write scrolls */
	if (this_player()->query_wiz_level())
	{
		return 1;
	}
	/* No-one else has permission to write scrolls */
	write("You do not have permission to do that.\n");
	return 0;
}
