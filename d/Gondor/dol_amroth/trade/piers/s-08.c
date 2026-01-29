/* -*- Mode: C -*-
 *
 * trade/piers/s-08.c
 *
 * By Skippern 20(c)01
 *
 * A ship is here which players can board and help bring the cargo into a
 *   warehouse nearby.
 */
#include "../../defs.h"

inherit DOL_STD + "city.c";

object o;

public void
create_dol_amroth()
{
    set_short("a stone pier");
    set_extralines("Some warehouses lies south of this pier.");
    set_lastline("This is the east end of the piers.");

    set_no_of_lamps(2);
    reset_room();

    bay_tells();
    street_tells();
    ship_tells();
    pier_tells();
    add_tell("Waves splashes against the road foundations.\n");

    add_exit(DOL_TRADE + "piers/r-08", "west", 0, 1);

    o = clone_object(DOL_OBJ+"doors/s-08-door");
    o->move(this_object());
}

reset_room()
{
    ::reset_room();

    if (!present("ship"))
    {
	o = clone_object(DOL_OBJ+"cargo_ship");
	o->set_short_desc("cargo ship");
	o->set_long_desc("Somebody tries to unload this ship.\n");
	o->add_name("ship");
	o->add_name("vessel");
	o->set_dest(DOL_OTHER+"ships/deck-4");
	o->move(this_object());
    }
}
