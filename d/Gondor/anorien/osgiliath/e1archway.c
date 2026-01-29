/*
 *	/d/Gondor/anorien/osgiliath/e1archway.c
 *
 *	Coded by Elessar.
 *
 *	Modification log:
 *	 7-Feb-1997, Olorin:	Changed inheritance.
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";
inherit "/d/Gondor/anorien/osgiliath/osgiliath";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public int     block_ranger();

static object *Ranger = allocate(2),
               IRanger;

public void
create_area_room()
{
    set_areadesc("archway facing east");
    set_area("eastern");
    set_areaname("the ruins of Osgiliath");
    set_land("Gondor");
    set_grass("no");
    set_extraline("Some light enters through the stone archway, and beyond it, "+
    "the bridge stretches east, on arched pillars across the river. "+
    "The room you are in is gloomy because of the dim light, and the naked "+
    "stone walls echo every sound. A collapsed stairway once lead up here, "+
      "but now it is only possible to follow a corridor southwest.");
    add_item("bridge", BS(
    "The current bridge must be quite recently reconstructed, as the "+
    "stones of the foundations seem to be fresh from the quarry.\n"));
    add_item("stairway",BSN("The stairway that once provided access to the above "+
    "floors here, no longer does - it is now but a pile of rocks on the floor."));
    add_item(({"ruins","archway"}),BSN("Before you to the east is a "+
    "gaping archway of stone allowing exit from the ruins out onto the "+
    "bridge across the Anduin."));
    add_item("corridor",BSN("The corridor is dark, you only see that it leads "+
			  "southeast from here, and nothing more."));
    add_prop(ROOM_M_NO_TELEPORT, check_teleport);
    add_prop(ROOM_I_INSIDE,1);
    add_exit(OSG_DIR + "ebridge3",  "east",      0, 1);
    add_exit(OSG_DIR + "lvl1corr3", "southwest", block_ranger, 1);

    reset_room();
}

public void
reset_room()
{
    clone_npcs(Ranger, NPC_DIR + "random_ranger", -1.0, OSG_DIR);
    Ranger[0]->set_random_move(10 + random(11));

    IRanger = clone_npc(IRanger, NPC_DIR + "i_ranger", OSG_DIR);
    IRanger->set_random_move(10 + random(6));
}

public int
block_ranger()
{
    if (TP->query_npc() && TP->id("ranger"))
        return 1;
    return 0;
}

