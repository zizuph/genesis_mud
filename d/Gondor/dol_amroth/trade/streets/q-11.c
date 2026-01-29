/* -*- Mode: C -*-
 *
 * trade/streets/q-11.c
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
    set_extralines("To the east a large square buzzes with life.");
    set_lastline("Smells of all sorts of food fills the air.");

    set_no_of_lamps(4);
    reset_room();

    set_sounds("Everywhere is a buzzing sound of people talking.");
    set_sound_detail("Some people are arguing over the price and the " +
                     "quality of the merchendice.");

    street_tells();

    add_exit(DOL_TRADE + "streets/p-11", "west", 0, 1);
    add_exit(DOL_TRADE + "streets/r-11", "east", 0, 1);
}

