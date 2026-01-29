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

    set_extraline("This is the eastern edge of the flower garden " +
        "along the side of the cottage. The garden fills this " +
        "corner of the house. It offers a nice view for those " +
        "inside looking out.");
    set_add_flowers();

//    add_exit(ROOMS_DIR + "garden02", "south");
    add_exit(ROOMS_DIR + "path02", "east");
    add_exit(ROOMS_DIR + "path04", "west");

}
