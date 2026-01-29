/*
 * trade/streets/p-12.c
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
    set_lastline("A nicely paved road leads southwest uphill to " +
		 "some large villas.");

    set_no_of_lamps(2);
    reset_room();

    street_tells();

    add_exit(DOL_HILLS + "streets/o-13", "southwest", 0, 1);
    add_exit(DOL_TRADE + "streets/p-11", "north", 0, 1);
    add_exit(DOL_TRADE + "streets/q-12", "east", 0, 1);
}

