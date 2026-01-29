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
    set_area("path in front of");
    set_areaname("a cottage");
    set_land("the Old Forest");
    set_areatype(0);

    set_extraline("Some beautiful flower gardens grow in front of " +
        "the house. They are full of bright colored flowers and " +
        "bring color to the clearing.");
    set_add_flowers();
    
    add_exit(ROOMS_DIR + "path06", "south");
//    add_exit(ROOMS_DIR + "garden01", "east");
    add_exit(ROOMS_DIR + "path04", "northeast");

}
