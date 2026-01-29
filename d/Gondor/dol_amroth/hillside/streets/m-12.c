/*
 * hillside/streets/m-12.c
 *
 * By Skippern 20(c)01
 *
 * A jatta jatta jatta
 */
#include "../../defs.h"

inherit DOL_STD + "city.c";

int
rat_block()
{
    if (this_player()->query_race() == "rat")
	return 1;
    return 0;
}

public void
create_dol_amroth()
{
    set_short("a paved road");
    set_extralines("The road goes uphill connecting the trade " +
                   "district with the fasionable mansions on the hillside.");
    set_lastline("The air is lighter here in the hight above the city.");

    set_sounds("The noise from the city is more distant and you feel " +
               "a bit tranquile.");
    set_sound_detail("Birds sings from the trees in a nearby garden.");

    set_no_of_lamps(4);
    reset_room();

    street_tells();

    add_exit(DOL_HILLS + "streets/l-11", "northwest", &rat_block(), 1);
    add_exit(DOL_HILLS + "streets/n-13", "southeast", 0, 1);
}

