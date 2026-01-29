/* -*- Mode: C -*-
 *
 * trade/piers/p-08.c
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
    set_lastline("A group of people are running back and forth between the " +
		 "ships and the warehouse here.");

    set_no_of_lamps(2);
    reset_room();

    bay_tells();
    street_tells();
    ship_tells();
    pier_tells();
    add_tell("Waves splashes against the road foundations.\n");

    add_exit(DOL_TRADE + "streets/o-09", "southwest", 0, 1);
    add_exit(DOL_TRADE + "piers/q-08", "east", 0, 1);

    o = clone_object(DOL_OBJ+"doors/p-08-door");
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
	o->set_dest(DOL_OTHER+"ships/deck-1");
	o->move(this_object());
    }
}
