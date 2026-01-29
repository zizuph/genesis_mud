/*
 * hillside/streets/i-10.c
 *
 * By Skippern 20(c)01
 *
 * A jatta jatta jatta
 */
#include "../../defs.h"

inherit DOL_STD + "city.c";

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

    add_exit(DOL_HILLS + "streets/h-11", "southwest", 0, 1);
    add_exit(DOL_HILLS + "streets/j-10", "east", 0, 1);
}

