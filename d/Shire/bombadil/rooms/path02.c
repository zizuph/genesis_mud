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

    set_extraline("The path runs between the old forest and the merry cottage. " +
        "On the north side of the path is the forest. The trees stand outside " +
        "the clearing, looking as if they have tried for centuries to encroach. " +
        "To the south is the cottage, standing in the center of the clearing.");

    add_exit(ROOMS_DIR + "path01", "east");
    add_exit(ROOMS_DIR + "path03", "west");

}
