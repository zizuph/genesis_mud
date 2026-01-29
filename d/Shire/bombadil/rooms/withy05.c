/*
 * Road in the Barrow Downs
 * By Finwe, December 2001
 */
 
#pragma strict_types
 
#include "../local.h"

inherit WITHY_BASE;
 
void
create_withy_room()
{
    set_areadesc("path");
    set_area("along");
    set_areaname("the Withywindle");
    set_land("Old Forest");

    set_extraline("The river straightens out as it flows east and " +
        "west. Bright flowers along the riverbank offer bright " +
        "spots in this rather ominous forest.");

    add_exit(ROOMS_DIR + "withy04", "east"); 
    add_exit(ROOMS_DIR + "withy06", "west");
}

