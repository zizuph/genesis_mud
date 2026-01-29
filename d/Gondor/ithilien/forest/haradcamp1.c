/*
 * /d/Gondor/ithilien/forest/haradcamp1.c
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

static object *Haradrim = allocate(2 + random(3));

public void
create_camp()
{
    set_short("in the Haradrim part of the camp");
    set_long(
	"Grey canvas tents are set in tidy rows. "+
	"The camp continues south and west, although the tents "+
	"appear less orderly to the east. To the east is forest.\n");
    add_item( ({ "rows", "large tent", "largest tent", "tent", "tents" }),
	
	"The tents are well-kept and orderly. "+
	"The largest tent is decorated "+
	"with a rising sun, embroidered with gold. It probably is not "+
	"the tent of a common soldier.\n");
    add_item( ({ "forest", "path" }), 
	"The forest extends east from the camp. A little "+
	"to the south, a path appears to lead into the forest.\n");

    add_exit(ITH_DIR+"forest/haradcamp2", "south", 0);
    add_exit(ITH_DIR+"forest/ncamp2", "north", 0);
    add_exit(ITH_DIR+"forest/haradcamp1a", "east", 0);
    add_exit(ITH_DIR+"forest/orccamp2", "west", 0);

    set_tent_path(ITH_DIR+"forest/haradtent1");

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
