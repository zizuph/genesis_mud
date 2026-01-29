/*
 * Road to the Barrow Downs
 * By Finwe, December 2001
 */
 
//#pragma strict_types
 
#include "../local.h"
inherit ROAD_BASE;

#define ER_DIR "/d/Shire/eastroad/western/"

void
create_road_room()
{
    set_area("west of the");
    set_extraline("The road meanders past stones. It is broken, " +
        "nothing more than a faint path in the grass. The path " +
        "runs north out of the Downs and south into mists and " +
        "darkness.");
    set_add_wight_sounds();

    add_exit(ROAD_DIR + "road03", "north");
    add_exit(ROAD_DIR + "road05", "south");
    
 
}

