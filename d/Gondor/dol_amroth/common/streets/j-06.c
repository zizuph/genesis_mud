/*
 * common/streets/j-06.c
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
    set_extralines("This streets goes through a residencial area.");
    set_lastline("Tall building towers up on each side of the street.");

    set_no_of_lamps(2);
    reset_room();

    street_tells();

    add_exit(DOL_COMMON + "streets/j-05", "north", 0, 1);
    add_exit(DOL_COMMON + "streets/j-07", "south", 0, 1);
    clone_object(DOL_OBJ + "doors/j-06-door")->move(this_object());
}

