/*
 * Path in Tom Bombadill's Clearing
 * By Finwe, December 2001
 */
 
#pragma strict_types

#include "/d/Shire/sys/defs.h" 
#include "../local.h"

inherit CLEAR_BASE;
inherit HERB_SEARCH;
 
void
create_path_room()
{
    set_areadesc("light");
    set_area("path outside");
    set_areaname("a cottage");
    set_land("the Old Forest");
    set_areatype(0);

    set_extraline("This is part one of the path that runs around " +
        "the clearing. It is lined with grey stones and also runs " +
        "to the threshold of the house. Growing to the right of the " +
        "house is a mighty oak tree.");
    add_item(({"oak tree", "oak", "mighty oak", "mighty oak tree"}),
        "The mighty oak tree grows beside the house, sheltering " +
        "it from the elements and providing some shade. It is the " +
        "only tree growing in the clearing, and looks very ancient.\n");

    add_exit(ROOMS_DIR + "path05", "north");
    add_exit(ROOMS_DIR + "path11", "south");
    add_exit(ROOMS_DIR + "rm_main", "east", "@@enter_house@@");
    add_exit(ROOMS_DIR + "path09", "southwest");

    add_herbs();
    add_prop(OBJ_I_SEARCH_TIME, 4);
    add_prop(OBJ_S_SEARCH_FUN, "herb_search");
    set_search_places(({"bush","bushes","trees"}));


}

void enter_house()
{
    write("You dust off your clothes and cross the hearth, entering " +
    "the small cottage.\n");
}