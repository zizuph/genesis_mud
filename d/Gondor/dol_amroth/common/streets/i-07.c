/* -*- Mode: C -*-
 * common/streets/j-07.c
 *
 * By Skippern 20(c)01
 *
 * A street in common district
 */
#include "../../defs.h"

inherit DOL_STD + "city.c";

void
load_store()
{
    find_player("skippern")->catch_msg("Test", 0);
    DOL_COMMON+"houses/i-06"->reset_room();

    //    find_player("skippern")->catch_msg("Test", 0);
}

public void
create_dol_amroth()
{
    set_short("a dirty street");
    set_extralines("This streets goes through a residencial area.");
    set_lastline("Some houses cling to the mountain side as it gets " +
                 "too steep for them.");


    set_no_of_lamps(2);
    reset_room();
    
    street_tells();

    clone_object(DOL_OBJ + "doors/i-07-door")->move(this_object());
    add_exit(DOL_COMMON + "streets/j-07", "east", 0, 1);
    add_exit(DOL_COMMON + "streets/h-07", "west", 0, 1);

    //    set_alarm(0.5, 0.0, &load_store());
}

