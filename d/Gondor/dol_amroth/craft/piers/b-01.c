/*
 * craft/piers/b-01.c
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
    set_short("a windwittered pier");
    set_extralines("We should have a ship service here.");
    set_lastline("Bay of Belfalas washes constantly over the pier here.");

    set_no_of_lamps(1);
    reset_room();

    pier_tells();
    bay_tells();
    street_tells();
    add_tell("Waves splashes against the road foundations.\n");

    add_exit(DOL_CRAFT + "streets/a-02", "southwest", 0, 1);
}

