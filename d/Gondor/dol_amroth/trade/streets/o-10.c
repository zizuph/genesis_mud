/* -*- Mode: C -*-
 *
 * trade/streets/o-10.c
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
    set_extralines("A hill towers up to the west.");
    set_lastline("The street buzzles with life.");

    set_no_of_lamps(2);
    reset_room();

    street_tells();

    add_exit(DOL_TRADE + "streets/p-11", "southeast", 0, 1);
    add_exit(DOL_TRADE + "streets/o-09", "north", 0, 1);
}

