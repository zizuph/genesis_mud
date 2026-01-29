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
    set_areadesc("country");
    set_area("road");
    set_areaname("halfway up the Hill");
    set_land("Bree");

    add_my_desc("Hobbit holes line the country road and trees dot " +
        "the hillside. Neat hobbit gardens surround the road, which " +
        "turns sharply south up the hill. Trees line the road, " +
        "making it shady here.\n");

    set_add_hobbit_holes();
    set_add_on_hill();

    add_exit(ROAD_DIR + "broad09", "west");
    add_exit(ROAD_DIR + "broad11", "southeast");
    add_exit(HOUSES_DIR + "hobbit02", "east", test_size);
}
