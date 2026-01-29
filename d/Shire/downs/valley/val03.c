/*
 * The valley of the Barrow Downs
 * By Finwe, December 2001
 */
 
#pragma strict_types
 
#include "local.h"

inherit ROAD_BASE;
 
void
create_road_room()
{
    set_areadesc("valley");
    set_area("south of");
    set_areaname("the Barrow Downs");
    set_land("Eriador");

    set_extraline("Here, the valley stretches out in all directions. " +
        "Nothing can be seen except for the edge of a forest to " +
        "the south and west and some barrows to the north. The " +
        "land is a field of green grass without anything else " +
        "growing on it.");

    set_add_valley_descrs();

    add_item(({"dark forest", "forest", "old forest"}),
        "The old forest is on the western edge of the downs. It " +
        "has an air of distrust to travellers and seems to be " +
        "watching your every move. The forest marks the western " +
        "edge of the Downs.\n");

    add_exit(VAL_DIR + "val04", "north");
    add_exit(VAL_DIR + "val02", "southwest");

}

