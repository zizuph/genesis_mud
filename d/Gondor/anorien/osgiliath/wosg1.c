/*
 *	/d/Gondor/anorien/ithilien/wosg1.c
 *
 *	Coded by Elessar.
 *
 *	Modification log:
 *	 1-Feb-1997, Olorin:	Changed inheritance,
 *				General revision.
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include "/d/Gondor/defs.h"

static object *Ranger = allocate(2);

public void
create_area_room()
{
    set_areadesc("street in the west end of Osgiliath");
    set_area("southern");
    set_areaname("Anorien");
    set_land("Gondor");
    set_grass("no");
    set_extraline("North and east of you are the old, ruined buildings of what "+
        "was once the west end of the capital of Gondor, Osgiliath. Some of "+
        "the houses are burned, others just torn down by time and weather. "+
        "The street continues north-eastwards, while two roads lead away " +
        "from here southwest and northwest.");
    add_exit(OSG_DIR + "wosg3",       "northeast", 0, 2);
    add_exit(OSG_DIR + "wosg4",       "east",      0, 2);
    add_exit(ANO_DIR + "road/rroad8", "south",     0, 3);
    add_exit(ANO_DIR + "road/or5",    "southwest", 0, 3);
    add_exit(ANO_DIR + "road/or3",    "northwest", 0, 3);

    reset_room();
}

public void
reset_room()
{
    clone_npcs(Ranger, NPC_DIR + "random_ranger", -1.0, ANO_DIR + "osgiliath");
    Ranger->set_random_move(10 + random(21));
}

string
query_dir_to_gate()
{
    return "southwest";
}
