/*
 * /d/Gondor/ithilien/forest/orcpath1.c
 *
 * Coded by Elessar.
 *
 *      Do not remove the scout from this room without
 *      fixing /d/Gondor/common/guild2/npc/morandir.c!
 *
 * Modification log:
 *  4-Feb-1997, Olorin:	General revision.
 * 30-Dec-1997, Gnadnar:	inherit camp.c
 */

#pragma strict_types

inherit "/d/Gondor/std/room.c";
inherit "/d/Gondor/ithilien/forest/room_tells";

#include "/d/Gondor/defs.h"

static object  Orc,
               Scout;

public void
create_gondor()
{
    set_short("a well-used track in the Ithilien forest");
    set_long("A dirty track runs north and south through the forest. "+
	"Trees along the track have been brutally broken and cut down, "+
	"and some of the still standing trees have crude carvings "+
	"in their trunks. The track passes over a small hill to the south; " +
    "a few thin spirals of smoke rise beyond the hill.\n");
    add_item("trees", 
	"Several of the trees along the track have been broken down. "+
	"Others still standing have crude carvings in the bark.\n");
    add_item( ({ "crude carvings", "carvings" }), 
    	"The carvings mostly depict a lidless eye and other foul images.\n");
    add_item( ({ "ground", "track", }), 
	"The track appears to have been made by hundreds of feet trampling "+
	"through the forest.\n");
    add_exit(ITH_DIR+"forest/orcpath2", "north", 0, 2);
    add_exit(ITH_DIR+"forest/ncamp",    "south", 0, 1);

    reset_room();

    add_orc_camp_tells();
}

public void
reset_room()
{
    Orc = clone_npc(Orc, NPC_DIR + "reorc");
    Scout = clone_npc(Scout, NPC_DIR + "rescout");
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
