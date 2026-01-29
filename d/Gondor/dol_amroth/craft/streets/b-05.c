/*
 * craft/streets/b-05.c
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
    set_extralines("Houses surrounds this street on all sides.");
    set_lastline("You see a solid building to the north.");

    set_no_of_lamps(1);
    reset_room();

    pier_tells();
    bay_tells();
    street_tells();
    add_tell("Waves splashes against the road foundations.\n");

    add_exit(DOL_CRAFT + "streets/b-04", "north", 0, 1);
    add_exit(DOL_CRAFT + "streets/c-06", "southeast", 0, 1);
    clone_object(DOL_OBJ + "doors/b-05-door")->move(this_object());
}

