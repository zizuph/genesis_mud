/*
 * other/pier/k-02.c
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
    set_extralines("This is the northmost point of a wooden pier going " +
	"out into the bay.");
    set_lastline("There is a small sign here with the text: Gondorian Pride.");

    set_no_of_lamps(0);
    reset_room();

    add_exit(DOL_OTHER + "pier/k-03", "south", 0, 1);

    bay_tells();
    pier_tells();
}

reset_room()
{
    object o;

    ::reset_room();
}



