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
    set_extralines("The street goes right by the waterfront.");
    set_lastline("You see a solid building to the north.");

    set_no_of_lamps(2);
    reset_room();

    bay_tells();
    street_tells();
    add_tell("Waves splashes against the road foundations.\n");

    add_exit(DOL_OTHER + "houses/k-04", "north", 0, 1);
    add_exit(DOL_COMMON + "streets/j-05", "west", 0, 1);
    add_exit(DOL_OTHER + "pier/l-06", "southeast", 0, 1);
}

