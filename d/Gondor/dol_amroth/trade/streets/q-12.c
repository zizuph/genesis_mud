/* -*- Mode: C -*-
 *
 * trade/streets/q-12.c
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
    set_short("a dirty street");
    set_extralines("To the south a wall towers up.");
    set_lastline("To the east you see the side wall of an " +
		 "armoured building.");

    set_no_of_lamps(2);
    reset_room();

    street_tells();

    add_exit(DOL_TRADE + "streets/p-12", "west", 0, 1);
    add_exit(DOL_TRADE + "streets/r-13", "southeast", 0, 1);
}

