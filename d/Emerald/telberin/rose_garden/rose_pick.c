/*
 * - rose_pick.c
 *
 *  Inheritable file to add rose picking to rooms.
 *  Step 1.) Inherit this file.
 *  Step 2.) In the create function make a call to set_up_roses()
 *  Step 3.) In your init() function, make a call to init_rose()
 */
#pragma no_clone
#pragma strict_types

#include "rose.h"
#include <composite.h>
#include <language.h>
#include <macros.h>

static public string *rose;
static mapping picked = ([ "MAX":0 ]);

/*
 * Function name: set_up_roses
 * Description	: Add roses to the room.
 * Arguments	: int num - The number of different rose types to add.
 *		  string *arg - A specific list of rose types to add.
 *			        Note: If used, 'num' is ignored.
 * Returns	: void
 */
static varargs void
set_up_roses(int num, string *arg)
{
    string *arr = m_indexes(ROSES);

    rose = ({});

    if (pointerp(arg))
    {
	num = sizeof(arg);
	while(num--)
	{
	    if (ROSES[arg[num]])
	    {
		rose += ({ arg[num] });
	    }
	}
    }
    else
    {
	while(num--)
	{
	    string name;

	    rose += ({ name = one_of_list(arr) });
	    arr   -= ({ name });
	}
    }

    num = sizeof(rose);

    this_object()->add_item(rose + ({ "rose", "roses" }),
	"Within this garden you can see "+
	(num > 1 ? "various " : "") + "roses of the type "+
	COMPOSITE_WORDS(rose) +".\nThey look beautiful and pickable.\n");
}

public int
pick_rose(string str)
{
    string verb = query_verb(), name;
    object ob;

    if (!str)
    {
	return notify_fail(capitalize(verb) +" what?\n");
    }

    if (str == "rose" || str == "roses")
    {
	str = one_of_list(rose);
    }
    else if (member_array(str, rose) == -1)
    {
	return notify_fail("You cannot seem to find any "+
	    LANG_PWORD(str) +" to "+ verb +" here.\n");
    }

    /* Are there any left to pick? */
    if (picked["MAX"] >= ROSE_LIMIT[1])
    {
	write(ROSE_LIMIT[3]);
	return 1;
    }

    /* See if we picked too many already */
    name = this_player()->query_name();
    if (picked[name] >= ROSE_LIMIT[0])
    {
	write(ROSE_LIMIT[2]);
	return 1;
    }

    write("You look over the roses and select "+ LANG_ADDART(str) +
	" for "+ verb +"ing.\n");

    say(QCTNAME(this_player()) +" looks over the roses and selects "+
	LANG_ADDART(str) +" for "+ verb +"ing.\n");

    ob = clone_object(ROSE_PATH);
    ob->set_rose(str);
    ob->move(this_player());

    /* Adjust the limits */
    picked["MAX"]++;
    picked[name]++;

    return 1;
}

static void
init_rose()
{
    add_action(pick_rose, "pick");
    add_action(pick_rose, "pluck");
}

