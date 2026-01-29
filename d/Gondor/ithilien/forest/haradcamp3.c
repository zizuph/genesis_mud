/*
 * /d/Gondor/ithilien/forest/haradcamp3.c
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
    set_long(
	"Gray canvas tents are arranged in good order. "+
	"One of the tents here has a large opening on top through which "+
	"the smoke of a fire escapes. "+
	"More tents are visible to the north and west, and forest extends "+
	"south and east.\n");

    add_item( ({ "tent", "largest tent", "large tent", "mess tent", "tents" }),
	
	"The tents appear to be well-maintained. The largest tent has "+
	"an opening on top through which smoke from a fire escapes.\n");
    add_item("forest", "South and east is forest.\n");

    /* have to add "enter mess tent" ourselves */
    add_cmd_item("mess tent", "enter", enter_tent);

    add_exit(ITH_DIR+"forest/haradcamp2", "north", 0);
    add_exit(ITH_DIR+"forest/haradcamp4s", "south", 0);
    add_exit(ITH_DIR+"forest/haradcamp3a", "east", 0);
    add_exit(ITH_DIR+"forest/orccamp3", "west", 0);

    set_tent_path(ITH_DIR+"forest/haradtent3");

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
