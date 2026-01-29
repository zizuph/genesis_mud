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
    set_area("path west of");
    set_areaname("a cottage");
    set_land("the Old Forest");
    set_areatype(0);

    set_extraline("You stand on the west side of the clearing " +
        "next to the cottage. The path leads southwest around to " +
        "the back of the cottage and along the river as well as " +
        "to the  north to the front of the cottage. A large oak " +
        "tree stands beside the cottage spreading its branches " +
        "over the clearing.");

    add_exit(ROOMS_DIR + "path06", "north");
    add_exit(ROOMS_DIR + "path12", "southeast");
}
