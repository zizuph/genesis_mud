/*
 * common/streets/g-07.c
 *
 * By Skippern 20(c)01
 *
 * A street in common district
 */
#include "../../defs.h"

inherit DOL_STD + "city.c";

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

    add_exit(DOL_COMMON + "streets/g-06", "north", 0, 1);
    add_exit(DOL_COMMON + "streets/h-07", "east", 0, 1);
    clone_object(DOL_OBJ + "doors/g-07-door")->move(this_object());
}

