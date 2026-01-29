/*
 * Road along the Withywindle
 * By Finwe, December 2001
 */
 
#include "../local.h"
inherit WITHY_BASE;
#include "/d/Shire/sys/defs.h"
 
void
create_withy_room()
{
    set_areadesc("path");
    set_area("along");
    set_areaname("the Withywindle");
    set_land("Old Forest");

    set_extraline("Beneath the canopy of the Old Forest, the trees " +
        "look ominous and spread out in all directions. Their " +
        "branches move about in the breeze almost trying to reach " +
        "out to you.");

    add_exit(ROOMS_DIR + "path13", "north"); 
    add_exit(ROOMS_DIR + "withy02", "east"); 
    add_exit(ROOMS_DIR + "withy04", "southwest");
}


void reset_shire_room()
{
}

