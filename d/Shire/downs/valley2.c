/*
 * Valley south of the Barrows
 * By Finwe, December 2001
 */
 
#pragma strict_types

#include "/d/Shire/sys/defs.h"
#include "local.h"

inherit ROAD_BASE;

#define QUEST_BARROW  "/d/Gondor/common/quest/nv/edown"

void
create_road_room()
{
    set_areadesc("valley");
    set_area("south of");
    set_areaname("the Barrow Downs");
    set_land("Eriador");

    set_extraline("The valley narrows as it leads south. Barrows " +
        "surround it, blocking travel to the south. Trees grow " +
        "along the western edge, fencing you in. The fogs are " +
        "much thinner here.");

    add_exit(DOWNS_DIR + "valley1", "north");
}

