/* -*- Mode -*-
 *
 * trade/streets/t-12.c
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
    set_lastline("To the south is a small square, and to the southeast " +
		 "is a rather large brick building.");

    set_no_of_lamps(2);
    reset_room();

    street_tells();

    add_exit(DOL_TRADE + "streets/u-12", "east", 0, 1);
    add_exit(DOL_TRADE + "streets/s-11", "northwest", 0, 1);
    add_exit(DOL_TRADE + "streets/t-13", "south", 0, 1);
    clone_object(DOL_OBJ + "doors/t-12-door")->move(this_object());
}

