/*
 * common/streets/k-05.c
 *
 * By Skippern 20(c)01
 *
 * A pier where some military vessels dock.
 */
#include "../../defs.h"

inherit DOL_STD + "city.c";

public void
create_dol_amroth()
{
    set_short("a wooden pier");
    set_extralines("This pier goes far into the bay.");
    set_lastline("The boards in the pier look heavy and would " +
		 "still hold many years of usage.");

    set_no_of_lamps(1);
    reset_room();

    pier_tells();
    bay_tells();
    street_tells();
    add_tell("Waves splashes against the road foundations.\n");

    add_exit(DOL_COMMON + "streets/g-05", "south", 0, 1);
}

