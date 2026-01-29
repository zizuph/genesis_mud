/*
 * other/pier/k-03.c
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
    set_short("a military dock");
    set_extralines("This is a wooden pier going out into the bay.");
    set_lastline("There is a small sign with the text: Ulmo's Fist.");

    set_no_of_lamps(0);
    reset_room();

    bay_tells();
    pier_tells();

    add_exit(DOL_OTHER + "pier/k-02", "north", 0, 1);
    add_exit(DOL_OTHER + "houses/k-04", "south", 0, 1);
}

reset_room()
{
    object o;

    ::reset_room();
}
