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
    set_areadesc("hillside");
    set_area("track on top of");
    set_areaname("the Hill");
    set_land("Bree");

    add_my_desc("It is a green meadow, dotted with wildflowers and " +
        "trees. The road that runs through Bree meets the the track " +
        "that runs across the hill.\n");

    set_add_hilltop();

    add_exit(ROAD_DIR + "broad15",  "northeast");
    add_exit(ROAD_DIR + "broad13", "west");

}
