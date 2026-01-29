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

    set_vbfc_extra(road_desc4);
    set_extraline("The path wanders alongside the river. The " +
        "grass is wet from the river splashing, which flows " +
        "southwest into the forest. Other paths wander past the " +
        "barrows in different directions. ");

    add_exit(DOWNS_DIR + "road15", "south");
    add_exit(DOWNS_DIR + "road11", "west");
    add_exit(DOWNS_DIR + "road07", "northeast"); 
//    add_exit(WITHY_DIR + "withy01", "southwest",0,0,1);
}
