/*
 * Road to the Barrow Downs
 * By Finwe, December 2001
 */
 
//#pragma strict_types
 
#include "local.h"
inherit ROAD_BASE;

#define ER_DIR "/d/Shire/eastroad/western/"

void
create_road_room()
{
    set_area("west of the");
    set_extraline("The road becomes nothing more than a path, " +
        "leading south into the Downs. North the road wanders " +
        "away from here towards the Great East Road. An old, " +
        "great dike runs east and west on either side of the road");
    add_item(({"dike", "great dike", "old great dike", "embankment", 
            "wide embankment"}),
        "The dike is a wide embankment of earth with an ancient, "+
        "crumbling wall on it. The dike stretches east and west, " +
        "marking the border of the ancient realm of Cardolan, " +
        "one of the divisions of Arnor.\n");
    add_item(({"wall", "ancient wall", "ancient crumbling wall", 
            "crumbling wall", "great wall"}),
        "Little remains of the great wall that sat atop the dike. " +
        "Some broken, large stones sit on both sides of the dike. " +
        "They look like they were once polished blocks, but now " +
        "are cracked and broken with age.\n");
    add_item(({"cracked stones", "cracked blocks", "large stones", 
            "broken stones", "polished blocks", "large blocks", 
            "broken blocks", "polished blocks"}),
        "The large blocks of stone once made up the walled dike. " +
        "Now they are fallen, cracked and buried in the dirt by " +
        "time and the enemies of the realm of Cardolan. They are "+
        "a silent testimony to the once proud nation that lived here.\n");

    add_exit(DOWNS_DIR + "road02", "north");
    add_exit(DOWNS_DIR + "road04", "south");
    
 
}

