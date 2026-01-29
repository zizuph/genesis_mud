/*
 * common/streets/j-05.c
 *
 * By Skippern 20(c)01
 *
 * A street in common district
 */
#include "../../defs.h"

inherit DOL_STD + "city.c";

public void
create_dol_amroth()
{
    set_short("a dirty street");
    set_extralines("The street goes right by the waterfront.");
    //    set_lastline("");

    set_no_of_lamps(2);
    reset_room();

    bay_tells();
    street_tells();
    add_tell("Waves splashes against the road foundations.\n");

    add_exit(DOL_COMMON + "streets/j-06", "south", 0, 1);
    add_exit(DOL_COMMON + "streets/k-05", "east", 0, 1);
    add_exit(DOL_COMMON + "piers/i-05", "west", 0, 1);
}

