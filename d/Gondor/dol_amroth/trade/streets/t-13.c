/* -*- Mode: C -*-
 *
 * trade/streets/t-13.c
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
    set_lastline("There is a small square by the street here.");

    set_no_of_lamps(2);
    reset_room();

    set_sounds("Everywhere is a buzzing sound of people talking.");
    set_sound_detail("Some people are arguing over the price and the " +
                     "quality of the merchendice.");

    street_tells();
    square_tells();

    add_exit(DOL_TRADE + "streets/t-12", "north", 0, 1);
    add_exit(DOL_TRADE + "streets/s-14", "southwest", 0, 1);
    add_exit(DOL_TRADE + "streets/u-14", "southeast", 0, 1);
    clone_object(DOL_OBJ + "doors/t-13-door")->move(this_object());
}

