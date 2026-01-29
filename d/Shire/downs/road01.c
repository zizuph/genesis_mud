/*
 * Road to the Barrow Downs
 * By Finwe, December 2001
 */
 
#pragma strict_types
 
#include "local.h"
inherit ROAD_BASE;

#define ER_DIR "/d/Shire/eastroad/western/"

void
create_road_room()
{
    set_area("west of the");
    set_extraline("The road is nothing more than a path leading " +
        "south into the Barrow Downs. Rumours persist that the " +
        "Downs are haunted, and only the fearless travel there.");

    add_exit(ER_DIR + "er25s", "north");
    add_exit(DOWNS_DIR + "road02", "south");
    
 
}

