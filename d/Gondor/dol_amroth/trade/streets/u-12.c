/* -*- Mode: C -*-
 *
 * trade/streets/u-12.c
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
    set_extralines("The street goes right by the waterfront.");
    set_lastline("A rather big brick building is seen to the south.");

    set_no_of_lamps(2);
    reset_room();

    street_tells();

    add_exit(DOL_TRADE + "streets/v-13", "southeast", 0, 1);
    add_exit(DOL_TRADE + "streets/t-12", "west", 0, 1);
}

