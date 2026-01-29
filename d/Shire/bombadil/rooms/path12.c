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
    set_area("path southwest of");
    set_areaname("a cottage");
    set_land("the Old Forest");
    set_areatype(0);

    set_extraline("A large oak tree grows at the corner of the " +
        "house. It is the only tree, except for fruit trees, " +
        "growing in the clearing. The path wanders past it as it " +
        "runs east and northwest.");

    add_exit(ROOMS_DIR + "oak1", "up");
    add_exit(ROOMS_DIR + "path13", "east");
    add_exit(ROOMS_DIR + "path11", "northwest");
}
