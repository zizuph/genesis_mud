/* -*- Mode: C -*-
 *
 * trade/streets/v-13.c
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
    set_extralines("A wall towers up to the east.");
    set_lastline("To the northeast a large worn down building stands.");

    set_no_of_lamps(2);
    reset_room();

    set_sound_detail("The building to the northeast is moaning, it sounds " +
		     "as it is about to collaps.");

    street_tells();
    add_tell("The old building to the northeast is moaning as the wind " +
	     "ruffles the old structure.\n");
    add_tell("A small piece of stone tumbles down from the roof of the " +
	     "building to the northwest.\n");

    add_exit(DOL_TRADE + "streets/v-14", "south", 0, 1);
    add_exit(DOL_TRADE + "streets/u-12", "northwest", 0, 1);
    clone_object(DOL_OBJ + "doors/v-13-door")->move(this_object());
}

