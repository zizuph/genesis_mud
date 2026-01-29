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
    set_areadesc("deserted");
    set_area("road");
    set_areaname("outside");
    set_land("north of Bree");

    add_bree_desc("The road is deserted as it runs west to an old " +
        "road and east to Bree. Few travellers use the road now, " +
        "and it even seems haunted.\n");

    set_add_outside_hedge();
    set_add_dike();

    add_exit(ROAD_DIR + "road03",  "northeast");
    add_exit(ROAD_DIR + "nroad06", "west");
}
