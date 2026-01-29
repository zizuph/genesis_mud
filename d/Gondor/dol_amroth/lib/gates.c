/* -*- Mode: C -*-
 *
 * lib/gates.c
 *
 * Skippern 20(c)01
 *
 * Lib file for the gates, includes functions to show/hide exits, and to 
 *  block them.
 */

int open;

public int
closed_gate()
{
    write("A large iron gate blocks your way.\n");
    return 1;
}

public int
closed_visible()
{
    return 1;
}

public int
inner_gate()
{
    open = 0;

    if (this_player()->query_race() == "rat")
	return 1;

    return open;
}

public int
inner_visible()
{
    return 0;
}

public int
outher_gate()
{
    open = 0;

    if (this_player()->query_race() == "rat")
	return 1;

    return open;
}

public int
outher_visible()
{
    return 0;
}
