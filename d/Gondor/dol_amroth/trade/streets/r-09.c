/* -*- Mode: C -*-
 *
 * trade/streets/r-09.c
 *
 * By Skippern 20(c)01
 *
 * A jatta jatta jatta
 */
#include "../../defs.h"

inherit DOL_STD + "city.c";

public void
create_dol_amroth()
{
    set_short("a crowded square");
    set_extralines("A large crowd is present here.");
    set_lastline("To the north you see a busy pier while to the south a " +
		 "large square is seen.");

    set_no_of_lamps(4);
    reset_room();

    street_tells();
    square_tells();

    add_exit(DOL_TRADE + "piers/r-08", "north", 0, 1);
    add_exit(DOL_TRADE + "streets/r-10", "south", 0, 1);
    clone_object(DOL_OBJ + "doors/r-09-door")->move(this_object());
}

