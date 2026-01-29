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
    set_long("The trail ends here in a large clearing. Orderly tents " +
        "surround it with the forest hiding the camp. \n");
    add_item(({ "rows", "tents", "tent" }), 
	    "The tents are kept in good order. They are used by the common " +
        "soldiers.\n");
    add_item("forest", 
        "The forest surrounds the camp, hiding it from prying eyes and muffling its sounds. \n");
    add_item("path",
	    "The path leads east, west, and northeast. It looks well traveled " +
        "buy humans and beasts.\n");

    add_exit(ITH_DIR+"forest/haradcamp3n", "north", 0);
    add_exit(ITH_DIR+"forest/haradcamp1a", "west", 0);
    add_exit(ITH_DIR+"forest/haradcamp4n", "northeast", 0);

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
