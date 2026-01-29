/*
 * hillside/streets/k-10.c
 *
 * By Skippern 20(c)01
 *
 * A jatta jatta jatta
 */
#include "../../defs.h"

inherit DOL_STD + "city.c";

int
blocked()
{
    if (this_player()->query_wiz_level())
    {
        this_player()->catch_msg("This area is closed temporary, mortals " +
				 "will get a message about a turned over " +
				 "wagon blocking the way.\n");
	return 0;
    }
    else if (this_player()->query_npc())
    {
	return 1;
    }
    else
    {
	this_player()->catch_msg("A turned over wagon blocks your way.\n");
	return 1;
    }
}

public void
create_dol_amroth()
{
    set_short("a paved road");
    set_extralines("This area is like a platou with a good view over " +
                   "the city.");
    set_lastline("The air is lighter here in the hight above the city.");

    set_sounds("The noise from the city is more distant and you feel " +
               "a bit tranquile.");
    set_sound_detail("Birds sings from the trees in a nearby garden.");

    set_no_of_lamps(4);
    reset_room();

    street_tells();

    add_exit(DOL_HILLS + "streets/j-10", "west", &blocked(), 1);
    add_exit(DOL_HILLS + "streets/l-11", "southeast", 0, 1);
}

