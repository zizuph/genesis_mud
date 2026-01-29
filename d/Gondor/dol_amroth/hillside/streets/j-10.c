/*
 * hillside/streets/j-10.c
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
    set_short("a paved road");
    set_extralines("To the south a large garden is seen, with a sign on " +
                   "gate.");
    set_lastline("The air is lighter here in the hight above the city.");

    set_sounds("The noise from the city is more distant and you feel " +
               "a bit tranquile.");
    set_sound_detail("Birds sings from the trees in a nearby garden.");

    add_item( ({ "sign", "sign on gate" }), "\n" +
              " +---------------------------------------+\n" +
              " |                                       |\n" +
              " |  <>                               <>  |\n" +
              " |      The residence of                 |\n" +
              " |          Sir Aldir of Hallacar,       |\n" +
              " |          Alchemist.                   |\n" +
              " |  <>                               <>  |\n" +
              " |                                       |\n" +
              " +---------------------------------------+\n\n");

    set_no_of_lamps(4);
    reset_room();

    street_tells();

    add_exit(DOL_HILLS + "streets/i-10", "west", 0, 1);
    add_exit(DOL_HILLS + "streets/k-10", "east", 0, 1);
    add_exit(DOL_HILLS + "j-11/garden1", "south", 0, 1);
}

