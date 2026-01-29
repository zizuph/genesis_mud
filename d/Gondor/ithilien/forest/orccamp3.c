/*
 * /d/Gondor/ithilien/forest/orccamp3.c
 *
 * Coded by Elessar.
 *
 * Modification log:
 *  4-Feb-1997, Olorin:	General revision.
 * 30-Dec-1997, Gnadnar:	inherit camp.c
 */

#pragma strict_types

inherit "/d/Gondor/ithilien/forest/camp";

#include "/d/Gondor/defs.h"

static object *Orc = allocate(3),
               Uruk;

public void
create_camp()
{
    set_short("southern edge of the orc camp");
    set_long("Several tents are set up here in the edge of the " +
        "clearing, all looking tattered and torn. Some of them have crude "+
        "paintings of red eyes and molested bodies all over them. "+
        "More tents can be seen around a blazing campfire to the north, "+
        "and a different kind of tent is raised to the east.\n");
    add_item( ({ "tents", "tent", }), 
        "The tents are tattered and torn, and covered with crude " +
        "paintings and scribblings. The largest tent looks a bit more clean. " +
	"Other kinds of tents reside to the east.");

    add_exit(ITH_DIR + "forest/orccamp1",   "north", 0, 1);
    add_exit(ITH_DIR + "forest/haradcamp3", "east",  check_allow, 1);

    set_tent_path(ITH_DIR+"forest/orctent3");

    reset_room();

    add_orc_camp_tells();
}

public void
reset_room()
{
    clone_npcs(Orc, NPC_DIR + "reorc", -1.0);

    if (!objectp(Uruk))
	Uruk = clone_npc(Uruk, NPC_DIR + "reuruk");
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
