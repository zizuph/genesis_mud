/*
 * common/streets/g-06.c
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
    set_lastline("Sounds comes from a basement of a house by the street, " +
		 "sounding much like a tavern.");

    set_sound_detail("From a basement you hear laughter and singing, and " +
		     "occationally some shouting. One voice says: Bring on " +
		     "more beer to my friends!");

    set_no_of_lamps(2);
    reset_room();
    
    street_tells();

    clone_object(DOL_OBJ + "doors/g-06-door")->move(this_object());
    add_exit(DOL_COMMON + "streets/g-07", "south", 0, 1);
    add_exit(DOL_COMMON + "streets/g-05", "north", 0, 1);
}

