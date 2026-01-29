/*
 * Copyright (c) 1991 Chalmers Computer Society
 *
 * This code may not be copied or used without the written permission
 * from Chalmers Computer Society.
 *
 * The standard commands of Genesis.
 */
inherit "/cmd/std/misc_cmd";

#include <macros.h>
#include <std.h>
#include <stdproperties.h>

void
create()
{
    seteuid(getuid(this_object())); 
}

/*
 * What souls to use as misc souls
 */
string *
replace_soul()
{
    return ({ MASTER }) +
        ::replace_soul();
}

/* **************************************************************************
 * Return a proper name of the soul in order to get a nice printout.
 */
string
get_soul_id()
{
    string *st;

    st = explode(file_name(this_object()), "/");
    return st[sizeof(st) - 1];
}

/* **************************************************************************
 * This is a command soul.
 */
int
query_cmd_soul()
{
    return 1;
}

/* **************************************************************************
 * The list of verbs and functions. Please add new in alfabetical order.
 */
mapping
query_cmdlist()
{
    return ([
               "block":"block",         // Global block ability
               "exploration":"exploration",
	     ]);
}

/* **************************************************************************
 * Here follows the actual functions. Please add new functions in the 
 * same order as in the function name list.
 * **************************************************************************/

/*
 * block - Global block ability for crowd control. Calls the ability
 *         file directly
 */
int
block(string str)
{
    string block_ability = "/d/Genesis/specials/std/block";
    setuid();
    seteuid(getuid());
    return block_ability->do_ability(str);
}

/*
 * help - This is specific Genesis help information.
 *
 * This is called before the standard help, so as to be able to override
 * standard help on a given subject.
 *
 * No notify_fail is used as the standard help will fix proper fail msgs.
public int
genesis_help(string what)
{
    // Let the standard help handle it
    if (!strlen(what))
	return 0;

    setuid();
    seteuid(getuid());

    if (this_player()->query_wiz_level() &&
	(file_size("/d/Genesis/doc/help/wizard/" + what) > 0))
    {
	this_player()->more(read_file("/d/Genesis/doc/help/wizard/" + what));
	return 1;
    }
    if (file_size("/d/Genesis/doc/help/general/" + what) > 0)
    {
	this_player()->more(read_file("/d/Genesis/doc/help/general/" + what));
	return 1;
    }
    return 0;
}
 */


/*
 * exploration - temporary command to interface to the Exploration Event
 *     controlroom to let players display their score or register a guess of
 *     the total number of rooms in the game.
 */
public int
exploration(string str)
{
    setuid();
    seteuid(getuid());

    "/d/Genesis/ateam/aoe/events/roomcount2012/controlroom"->exploration(str);
    return 1;
}

