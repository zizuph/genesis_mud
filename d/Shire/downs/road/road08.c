/*
 * road in the Downs
 * By Finwe, December 2001
 */
 
#pragma strict_types
 
#include "../local.h"

inherit ROAD_BASE;
 
void
create_road_room()
{
    set_areadesc("path");
    set_area("somewhere in");
    set_areaname("the Barrow Downs");
    set_land("Eriador");

    set_vbfc_extra(road_desc3);

    set_extraline("The mists swirl all about, obscuring the path " +
        "leading south and west. The path leads northeast away " +
        "from this haunted place past a flowing river.");
    set_add_wight_sounds();
    
    add_exit(ROAD_DIR + "road13", "south");
    add_exit(ROAD_DIR + "road07", "west");
    add_exit(ROAD_DIR + "road06", "northeast"); 
}

