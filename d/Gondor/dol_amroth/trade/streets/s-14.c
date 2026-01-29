/* -*- Mode: C -*-
 *
 * trade/streets/s-14.c
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
    set_extralines("To the south a high wall towers up.");
    set_lastline("The road goes close to the wall.");

    set_no_of_lamps(2);
    reset_room();

    street_tells();

    add_exit(DOL_TRADE + "streets/r-13", "northwest", 0, 1);
    add_exit(DOL_TRADE + "streets/t-13", "northeast", 0, 1);
}

