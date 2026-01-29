/*
 * common/streets/j-07.c
 *
 * By Skippern 20(c)01
 *
 * A street in common district
 */
#include "../../defs.h"

inherit DOL_STD + "city.c";

#include <macros.h>
#include <ss_types.h>

int climb_pipe(string a);

public void
create_dol_amroth()
{
    set_short("a dirty street");
    set_extralines("This streets goes through a residencial area.");
    set_lastline("Some houses cling to the mountain side as it gets " +
                 "too steep for them.");

    set_no_of_lamps(2);
    reset_room();
    
    street_tells();

    add_exit(DOL_COMMON + "streets/j-06", "north", 0, 1);
    add_exit(DOL_COMMON + "streets/i-07", "west", 0, 1);
}

void
init()
{
    ::init();
    add_action(climb_pipe, "climb");
}

int
climb_pipe(string a)
{
    notify_fail("Climb what?\n");

    if (a == "pipe")
    {
        int Climb = this_player()->query_skill(SS_CLIMB);

	if (Climb < 25)
	{
	    write("As you try to climb up the pipe you " +
		  "realize your skill isn't good enough.\n");
	    say(QCTNAME(this_player()) + " tries to climb up the " +
		"drain pipe, but falls to the ground.\n");
	    return 1;
	}
	write("You climb up the drain pipe.\n");
	say(QCTNAME(this_player()) + " leaves up the drain pipe.\n");
	this_player()->move_living("M", DOL_COMMON+"roof", 1, 0);
	say(QCTNAME(this_player()) + " arrives from below.\n");
	return 1;
    }

    return 0;
}
