/* -*- Mode: C -*-
 *
 * trade/streets/u-14.c
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
    set_lastline("The street follows the wall here.");

    set_no_of_lamps(2);
    reset_room();

    bay_tells();
    street_tells();
    add_tell("Waves splashes against the road foundations.\n");

    add_exit(DOL_TRADE + "streets/t-13", "northwest", 0, 1);
    add_exit(DOL_TRADE + "streets/v-14", "east", 0, 1);
}

