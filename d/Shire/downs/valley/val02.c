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

    set_extraline("The land is a sea of green grass, punctuated " +
        "with an occasional hill. The valley is bare of any other " +
        "plants or signs of life to the west is the edge of an old " +
        "forest.");

    set_add_valley_descrs();

    add_item(({"dark forest", "forest", "old forest"}),
        "The old forest is on the western edge of the downs. It " +
        "has an air of distrust to travellers and seems to be " +
        "watching your every move. The forest marks the western " +
        "edge of the Downs.\n");

    add_exit(VAL_DIR + "val03", "northeast");
    add_exit(VAL_DIR + "val01", "south");

}

