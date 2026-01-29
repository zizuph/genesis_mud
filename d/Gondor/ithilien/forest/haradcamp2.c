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

static object	*Haradrim = allocate(3);

public void
create_camp()
{
    set_short("In the Haradrim part of the camp");
    set_long("Orderly rows of tents fill this clearing. A path meanders " +
        "amongst the oaks eastwards, and the camp continues to the west, " +
        "north and south.\n");
    add_item(({ "rows", "clearing", "large tent", "largest tent", 
            "tents", "tent" }), 
	    "The tents are kept in good order. The largest tent is decorated "+
	    "with a rising sun, embroidered with gold. It probably is not "+
	    "the tent of a common soldier.\n");
    add_item("forest", 
        "The forest extends to the east and northeast.\n");
    add_item("path",
	    "The path leads east, and seems to have been made by humans.\n");

    add_exit(ITH_DIR+"forest/haradcamp3", "south", 0);
    add_exit(ITH_DIR+"forest/orccamp1", "west", 0);
    add_exit(ITH_DIR+"forest/haradcamp1", "north", 0);
    add_exit(ITH_DIR+"forest/olipath1", "east");

    set_tent_path(ITH_DIR+"forest/haradtent2");

    reset_room();
}

public void
reset_room()
{
    ::reset_room();
    clone_npcs(Haradrim, NPC_DIR+"haradrim", -1.0);
}
