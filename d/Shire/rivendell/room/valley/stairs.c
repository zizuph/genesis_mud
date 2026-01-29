/*
 * Path to Rivendell
 * By Finwe, November 1997
 */
 
#include "local.h"
 
inherit VALLEY_BASE; 
 
 
void
create_valley_room()
{
    set_area("in a");
    set_areaname("valley");
    set_land("Eriador");
    set_areatype(7);
    set_areadesc("set of stairs");
    set_grass("sparse, dry");
    set_treetype("deciduous");;
 
    set_extraline("These steps curve around the plateau as they " +
        "descend into the valley. Melodic elvish voices fill " +
        "the air.");
 
    add_item(({"deciduous trees", "deciduous tree", "deciduous"}),
        "Large beech and oak trees cover the valley below.\n");
 
    add_exit(VALLEY_DIR + "stairs01", "down", 0, 1);
    add_exit(VALLEY_DIR + "track04", "west", 0, 1);
 
}
