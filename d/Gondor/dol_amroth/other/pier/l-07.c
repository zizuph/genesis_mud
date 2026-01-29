/*
 * other/pier/l-07.c
 *
 * By Skippern 20(c)01
 *
 * A pier.
 */
#include "../../defs.h"

inherit DOL_STD + "city.c";

public void
create_dol_amroth()
{
    set_short("a small pier");
    set_extralines("A quay goes along the water front.");
    set_lastline("A odour of fresh paint fills the atmosphare.");

    set_no_of_lamps(2);
    reset_room();

    add_exit(DOL_OTHER + "streets/m-08", "southeast", 0, 1);
    add_exit(DOL_OTHER + "pier/l-06", "north", 0, 1);

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
	o->set_short_desc("small yacht");
	o->set_long_desc("It looks abandoned.\n");
	o->add_name("ship");
	o->add_name("yacht");
	o->add_name("vessel");
	o->move(this_object());
    }
    /*
    if (!present("ian"))
    {
	o = clone_object(DOL_NPC + "artist-painter");
	o->move(this_object());
    }
    */
}



