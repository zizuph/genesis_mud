/*
 * Paralyze used in the library when searching for books.
 */
#include "/d/Krynn/common/defs.h"
#include "../tower/mage_lib.h"

inherit "/std/paralyze";

public void
create_paralyze()
{
    set_fail_message("You can't do that while searching for books. You may however " +
			"'stop searching'.\n");
    set_stop_verb("stop");
    set_stop_fun("stop_search");
    set_stop_object(TO);
    set_remove_time(100);
    set_stop_message("You stop searching for the book.\n");
    add_name(LIB_PARALYZE_NAME);
}

public int
stop_search(string str)
{
    if (!str || !strlen(str))
    {
        write("Stop what? Stop searching?\n");
        return 1;
    }

    if (L(str) != "searching")
    {
        write("You can't stop that.\n");
    }

    return 0;
}

