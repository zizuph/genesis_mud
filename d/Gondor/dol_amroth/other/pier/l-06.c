/*
 * other/pier/l-06.c
 *
 * By Skippern 20(c)01
 *
 * A pier.
 */
#include "../../defs.h"

inherit DOL_STD + "city.c";

#include <stdproperties.h>

public void
create_dol_amroth()
{
    set_short("a small pier");
    set_extralines("A quay goes along the water front.");
    set_lastline("There are some rumble in a corner.");

    set_no_of_lamps(2);

    add_exit(DOL_OTHER + "pier/l-07", "south", 0, 1);
    add_exit(DOL_COMMON + "streets/k-05", "northwest", 0, 1);

    reset_room();

    street_tells();
    bay_tells();
    ship_tells();
    pier_tells();

    set_sounds("The waves crushes into the road foundments and makes " +
        "a buzzing sound mixed with the sound of sea gulls screaming in " +
	"the sky.");
}

reset_room()
{
    object o;

    ::reset_room();
    if (!present("ship"))
    {
        o = clone_object(DOL_OBJ + "empty_ship");
	o->set_short_desc("small ship");
	o->set_long_desc("It looks abandoned.\n");
	o->add_name("ship");
	o->add_name("vessel");
	o->move(this_object());
    }
    /*
    if (!present("wilhelma"))
    {
        o = clone_object(DOL_NPC + "artist-mason");
        o->move(this_object());
    }
    */
}



