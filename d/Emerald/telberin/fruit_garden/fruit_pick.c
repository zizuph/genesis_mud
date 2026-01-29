/*
 * - fruit_pick.c
 *
 *  Inheritable file to add fruit picking to rooms.
 *  Step 1.) Inherit this file.
 *  Step 2.) In the create function make a call to set_up_fruits()
 *  Step 3.) In your init() function, make a call to init_fruit()
 */
#pragma no_clone
#pragma strict_types

#include "fruit.h"
#include <composite.h>
#include <language.h>
#include <macros.h>

static public string *fruit;
static mapping picked = ([ "MAX":0 ]);

/*
 * Function name: set_up_fruits
 * Description	: Add fruits to the room.
 * Arguments	: int num - The number of different fruit types to add.
 *		  string *arg - A specific list of fruit types to add.
 *			        Note: If used, 'num' is ignored.
 * Returns	: void
 */
static varargs void
set_up_fruits(int num, string *arg)
{
    string *arr = m_indexes(FRUITS);

    fruit = ({});

    if (pointerp(arg))
    {
	num = sizeof(arg);
	while(num--)
	{
	    if (FRUITS[arg[num]])
	    {
		fruit += ({ arg[num] });
	    }
	}
    }
    else
    {
	while(num--)
	{
	    string name;

	    fruit += ({ name = one_of_list(arr) });
	    arr   -= ({ name });
	}
    }

    num = sizeof(fruit);

    this_object()->add_item(fruit + ({ "fruit", "fruits" }),
	"Within this garden you can see "+
	(num > 1 ? "various " : "") + "fruits of the type "+
	COMPOSITE_WORDS(fruit) +".\nThey look ripe and pickable.\n");
}

public int
pick_fruit(string str)
{
    string verb = query_verb(), name;
    object ob;

    if (!str)
    {
	return notify_fail(capitalize(verb) +" what?\n");
    }

    if (str == "fruit" || str == "fruits")
    {
	str = one_of_list(fruit);
    }
    else if (member_array(str, fruit) == -1)
    {
	return notify_fail("You cannot seem to find any "+
	    LANG_PWORD(str) +" to "+ verb +" here.\n");
    }

    /* Are there any left to pick? */
    if (picked["MAX"] >= FRUIT_LIMIT[1])
    {
	write(FRUIT_LIMIT[3]);
	return 1;
    }

    /* See if we picked too many already */
    name = this_player()->query_name();
    if (picked[name] >= FRUIT_LIMIT[0])
    {
	write(FRUIT_LIMIT[2]);
	return 1;
    }

    write("You look over the fruits and select "+ LANG_ADDART(str) +
	" for "+ verb +"ing.\n");

    say(QCTNAME(this_player()) +" looks over the fruits and selects "+
	LANG_ADDART(str) +" for "+ verb +"ing.\n");

    ob = clone_object(FRUIT_PATH);
    ob->set_fruit(str);
    ob->move(this_player());

    /* Adjust the limits */
    picked["MAX"]++;
    picked[name]++;

    return 1;
}

static void
init_fruit()
{
    add_action(pick_fruit, "pick");
    add_action(pick_fruit, "pluck");
}

