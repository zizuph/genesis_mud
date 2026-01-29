/* -*- Mode: C -*-
 * trade/streets/r-10.c
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
    set_short("a crowded square");
    set_extralines("A large crowd is present here.");
    set_lastline("A huge inn cuts the corner of the square here.");

    set_sounds("Everywhere is a buzzing sound of people talking.");
    set_sound_detail("Some people are arguing over the price and the " +
                     "quality of the merchendice.");


    set_no_of_lamps(4);
    reset_room();

    street_tells();
    square_tells();

    add_exit(DOL_TRADE + "streets/r-10", "west", 0, 1);
    clone_object(DOL_OBJ + "doors/s-10-door")->move(this_object());
}

