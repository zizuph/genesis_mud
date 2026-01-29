/*
 * Path in Tom Bombadill's Clearing
 * By Finwe, December 2001
 */
 
#pragma strict_types

#include "/d/Shire/sys/defs.h" 
#include "../local.h"

inherit CLEAR_BASE;
 
void
create_path_room()
{
    set_areadesc("light");
    set_area("path north of");
    set_areaname("a cottage");
    set_land("the Old Forest");
    set_areatype(0);

    set_extraline("Flower gardens dominate this part of the " +
        "clearing as they grow alongside the cottage. Their " +
        "bright colors and textures contrast with the house and " +
        "clearing.");
    set_add_flowers();

//    add_exit(ROOMS_DIR + "garden01", "south");
    add_exit(ROOMS_DIR + "path03", "east");
    add_exit(ROOMS_DIR + "path05", "southwest");

}
