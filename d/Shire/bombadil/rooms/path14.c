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
    set_area("path southeast of");
    set_areaname("a cottage");
    set_land("the Old Forest");
    set_areatype(0);

    set_extraline("The path takes a sharp angle as it goes around " +
        "the corner of the house. South is a river that runs along " +
        "the edge of the clearing. The water is clear as it runs " +
        "west from the Downs.");

    add_exit(ROOMS_DIR + "path10", "north");
    add_exit(ROOMS_DIR + "path13", "west");
}
