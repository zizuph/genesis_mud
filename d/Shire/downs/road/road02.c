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
    set_extraline("The road continues north and south deeper into " +
        "the Downs. Broken stones litter the ground, half buried " +
        "beneath the grass and shrubs.");

    add_exit(ROAD_DIR + "road01", "north");
    add_exit(ROAD_DIR + "road03", "south");
    
 
}

