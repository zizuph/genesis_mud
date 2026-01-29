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
    add_exit(MTRAIL_DIR + "mtrail05", roadEast, "@@up", 2);
    add_exit(MTRAIL_DIR + "mtrail03", roadWest, "@@down", 2);
}

