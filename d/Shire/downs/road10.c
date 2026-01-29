/*
 * Road in the Barrow Downs
 * By Finwe, December 2001
 */
 
#pragma strict_types
 
#include "local.h"

inherit ROAD_BASE;
 
void
create_road_room()
{
    set_areadesc("path");
    set_area("somewhere in");
    set_areaname("the Barrow Downs");
    set_land("Eriador");

    set_vbfc_extra(road_desc2);
    set_extraline("The trees seem closer here, where the path " +
        "seems to wind into them and disappear.");
    set_add_wight_sounds();

    add_exit(DOWNS_DIR + "road11", "east");

}

