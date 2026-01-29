/*
 *	/d/Gondor/rohan/isengard/isenroad1.c
 *
 *	Modification log:
 *	 7-Feb-1997, Olorin:	Changed inheritance.
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include "/d/Gondor/defs.h"

static object  Orc;

public void
create_area_room()
{
    set_areatype(8);
    set_areadesc("rocky riverbank");
    set_area("central");
    set_areaname("the Gap of Rohan");
    set_land("Rohan");
    set_extraline("You are on the dark road leading north along the River Isen "+
    "towards Isengard. On the other side of the river you can see the "+
    "plains of Rohan begin, but the river is not crossable here. To the "+
    "south however, are the Fords of Isen, the usual crossing point of "+
    "the Isen. To the west are the hills of Dunland.");
    add_exit(ISEN_DIR + "isenroad/isenroad2", "north", 0, 3);
    add_exit(DUN_DIR + "road/r01",   "south", 0, 3);
    reset_room();
}

public void
reset_room()
{
    Orc = clone_npc(Orc, NPC_DIR + "whorc");
}

