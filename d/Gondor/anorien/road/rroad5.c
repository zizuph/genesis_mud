/*
 *	/d/Gondor/anorien/road/rroad5.c
 *
 *	Coded by Elessar.
 *
 *	Modification log:
 *	30-Jan-1997, Olorin:	Changed inheritance.
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

static object  Soldier;

public void
create_area_room()
{
    set_areadesc("green, grassy field");
    set_areatype(8);
    set_area("southeastern");
    set_areaname("Anorien");
    set_land("Gondor");
    set_extraline("The road runs north and south across the fields outside the "+
    "Rammas Echor, following the west banks of the river Anduin. Far to the "+
    "north you think you can see some ruins.");
    add_item("ruins","You are not sure, but they might be the ruins of Osgiliath.\n");
    add_item("river","The river flows lazily by to the east, ever confident that\n"+
	     "it will reach the Sea sooner or later.\n");
    add_exit(ANO_DIR + "road/rroad6", "north", 0, 2);
    add_exit(ANO_DIR + "road/rroad4", "south", 0, 2);
    reset_room();
}

public void
reset_room()
{
    if (!objectp(Soldier))
    {
	Soldier = clone_npc(Soldier, NPC_DIR + "gsoldier");
	Soldier->set_random_move(10);
	Soldier->set_restrain_path( ({ ANO_DIR + "road" }) );
    }
}
