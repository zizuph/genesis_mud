/* Mountain trail room, credit to Sarr */
#pragma strict_types
#include "defs.h"
inherit MTRAIL_ROOM;

void
create_room()
{
    type = "west";
    roadWest = "southwest";
    roadEast = "northeast";
    ::create_room();
    add_exit(MTRAIL_DIR + "mtrail02", roadEast, "@@up", 2);
    add_exit(FOREST_DIR + "eforest53", roadWest, "@@down", 2);
}
