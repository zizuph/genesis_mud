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
    set_short("a dirty street");
    set_extralines("This streets goes along a residencial area.");
    set_lastline("A wooden platform is mounted along the street by the " +
		 "waterfront");

    set_no_of_lamps(2);
    reset_room();

    pier_tells();
    bay_tells();
    street_tells();
    add_tell("Waves splashes against the road foundations.\n");

    add_exit(DOL_COMMON + "piers/h-05", "west", 0, 1);
    add_exit(DOL_COMMON + "streets/j-05", "east", 0, 1);
}

