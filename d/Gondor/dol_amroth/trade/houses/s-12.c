/* -*- Mode: C -*-
 *
 * trade/houses/s-12.c
 *
 * Skippern 20(c)01
 *
 * A common house.
 */
#include "../../defs.h"

inherit DOL_STD + "inside";

#include <macros.h>

/* Prototypes */

void
create_inside()
{
    FIX_EUID;  

    set_short("inside a house");
    set_long("The common room of a gondorian house. The room is " +
	     "purely furnished, there is only a small bookshelf, " +
	     "a table and four chairs here. There are nothing " +
	     "nothing special with any of the furnishing.\n");

    add_item("table", "It is a common table, nothing special about it.\n");
    add_item( ({ "chair", "chairs" }), "It is a common chair, " +
	      "nothing special about it.\n");
    add_item("bookshelf", "This is a small bookself. Some of the " +
	     "shelves are empty and dusty, while other hold books. " +
	     "Among the titles you see titles such as: The batchelors " +
	     "cookbook, The Anarcist handbook and Bribery, the art of " +
	     "influencing governments. Looking closely on the cookbook " +
	     "you notice the top of the back is more worn down than the " +
	     "rest of it.\n");

    clone_object(DOL_OBJ + "doors/s-12-door")->move(this_object());
}

int
pull_l(string str)
{
    notify_fail("Pull what?\n");
    if (!strlen(str))
	return 0;

    if (str == "cookbook" || str == "lever")
    {
	write("You pull the lever and finds a hidden path behind the " +
	      "bookshelf leading down to a basement.\n");
	say(QCTNAME(this_player()) + " fumbles with " +
	    "something and disapears behind the bookshelf.\n");
	this_player()->move_living("M", DOL_SEWER + "s-12", 1, 0);
	say(QCTNAME(this_player()) + " arrives from above.\n");
	return 1;
    }
    return 0;
}

void
init()
{
    ::init();
    add_action(pull_l, "pull");
}
