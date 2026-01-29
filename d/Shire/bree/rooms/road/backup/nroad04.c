/*
 * Road in Bree
 * By Finwe, June  2001
 */
 
#pragma strict_types

#include "/d/Shire/sys/defs.h" 
#include "defs.h"

inherit ROAD_BASE;

void
create_road_room()
{

    set_areadesc("ancient highway");
    set_area("north of");
    set_areaname("Bree");
    set_land("Eriador");

    set_extraline("Broad and wide, the highway runs north and " +
        "south and is straight and true. An old guard house " +
        "stands to the west in this desolate land.\n");
    add_item(({"guard house", "old guard house", "house"}),
        "The old guard has collapsed in on itself. It looks " +
        "like it was once large enough to shelter some guards who " +
        "watched the highway. Now, it is little more than a pile " +
        "of stone rubble.\n");
    add_item(({"stone rubble", "rubble"}),
        "It is a pile of weathered stones. Some are still stacked " +
        "on top of each other, but most are fallen to the ground " +
        "and smashed and cracked.\n");

    set_add_nroad();

    add_exit(ROAD_DIR + "nroad05", "north");
    add_exit(ROAD_DIR + "nroad03", "south");
}
