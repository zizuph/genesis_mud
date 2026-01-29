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
    set_area("path south of");
    set_areaname("a cottage");
    set_land("the Old Forest");
    set_areatype(0);

    set_extraline("The sounds of the river echo up from the south. " +
        "Its fast flowing water is clear and cool looking as it " +
        "runs west over smooth stones. A path leads south to the " +
        "riverbank where the path continues east and west around " +
        "the cottage.");
    add_item(({"smooth stones", "river stones"}),
        "The smooth stones lie at the bottom of the river. They " +
        "are rounded and a slate grey color. They have been " +
        "smoothed by the water flowing over them for countless " +
        "years.\n");

    add_exit(ROOMS_DIR + "withy03", "south");
    add_exit(ROOMS_DIR + "path14", "east");
    add_exit(ROOMS_DIR + "path12", "west");
}
