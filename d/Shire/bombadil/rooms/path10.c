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
    set_area("path east of");
    set_areaname("a cottage");
    set_land("the Old Forest");
    set_areatype(0);

    set_extraline("You stand at the back door of the cottage.  " +
        "East is a stable with the doors closed. The path runs " +
        "northeast and south towards the river and around the " +
        "side of the cottage.");

    add_item(({"stable"}),
        "The stable is a large building made of wood. It is " +
        "rectangular and houses horses that belong to the owner " +
        "of the cottage. The doors are closed, preventing anyone " +
        "from entering the stables except for the owner.\n");

    add_exit(ROOMS_DIR + "path14", "south");
//    add_exit(ROOMS_DIR + "stables", "east");
    add_exit(ROOMS_DIR + "rm_kitchen", "west","@@enter_house@@");
    add_exit(ROOMS_DIR + "path08", "northeast");
}

void enter_house()
{
    write("You dust off your clothes and cross the hearth, entering " +
    "the small cottage through the back door.\n");
}
