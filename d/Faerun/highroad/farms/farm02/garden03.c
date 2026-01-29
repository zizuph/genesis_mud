/*
 * Farm flower garden
 * By Finwe, October 2006
 */

#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"

inherit BASE_GARDEN;
inherit BASE_COMMON;

void
create_garden_room()
{
    set_short("A large flower garden");
    add_prop(ROOM_S_MAP_FILE, "farm_w_map.txt");

    set_extraline("The flowerbeds are thick and full of bright flowers. " +
        "Bees bounce from flower to flower, and butterflies lightly flutter " +
        "among the flowerbeds. A stone wall surrounds the garden protecting " +
        "all who are here. The farmhouse is to the west, and a path leads north.");

    add_item(({"farmhouse", "house"}),
        "The farmhouse is large and surrounded flowerbeds. It is whitewashed " +
        "and sits at the western edge of the garden.\n");

    reset_room();

    add_exit(FARM2_DIR + "garden02", "north");
}

void reset_room()
{
    ::reset_room();
}
