/*
 * /d/Gondor/ithilien/forest/haradcamp2.c
 *
 * Coded by Elessar.
 *
 * Modification log:
 * 30-Dec-1997, Gnadnar: general revision
 *
 */

#pragma strict_types

inherit "/d/Gondor/ithilien/forest/camp";

#include "/d/Gondor/defs.h"

static object	*Haradrim = allocate(1 + random(3));

public void
create_camp()
{
    set_short("In the Haradrim part of the camp");
    set_long("The camp runs east, west, and south. It's more orderly here " +
        "with rows of tents lining the lane.\n");
    add_item(({ "rows", "tents", "tent" }), 
	    "The tents are kept in good order. They are used by the common " +
        "soldiers.\n");
    add_item("forest", 
        "The forest extends to the east and northeast.\n");
    add_item("path",
	    "The path leads east and west, and seems to have been made by " +
        "humans. A side path leads south\n");

    add_exit(ITH_DIR+"forest/haradcamp2n", "north", 0);
    add_exit(ITH_DIR+"forest/olipath1", "south", 0);
    add_exit(ITH_DIR+"forest/haradcamp1", "west", 0);
    add_exit(ITH_DIR+"forest/haradcamp1b", "east");

    reset_room();

    add_harad_camp_tells();
}

public void
reset_room()
{
    ::reset_room();
    clone_npcs(Haradrim, NPC_DIR+"haradrim", -1.0);
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
    {
        start_room_tells();
    }
}
