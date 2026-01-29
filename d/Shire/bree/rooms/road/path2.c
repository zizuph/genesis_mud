/*
 * Path behind the AG in Bree.
 * Raymundo, Jan 2020
 */
 
#pragma strict_types

#include "/d/Shire/sys/defs.h"
#include "defs.h"

inherit PATH_BASE;



void
create_path_room()
{
    add_bree_desc("You are at the corner of the Adventurer's Guild "
        + "building. It's a remarkably square building at that. "
        + "If you were to follow the path west you'd eventually "
        + "find yourself back on the main road in Bree. Here the "
        + "path takes a turn to the south, leading you to the back "
        + "of the square building.\n");

    add_AG("northeast", "The roof hangs over the path some, creating "
        + "shade.");

    add_item("roof", "It looks like a pretty standard roof. It hangs over "
        + "the path, adding shade.\n");
    add_item( ({"shade", "shadows"}), "Thanks to the roof, you can walk "
        + "here without being baked by the sun.\n");
    add_exit(ROAD_DIR + "path1", "west");
    add_exit(ROAD_DIR + "path3", "south");

    reset_shire_room();
}



void
reset_shire_room()
{

}

