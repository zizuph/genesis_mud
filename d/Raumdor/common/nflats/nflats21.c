#include "defs.h"
inherit NFLATS_ROOM;

void
create_room()
{
    ::create_room();

    add_exit(NFLATS_DIR + "nflats24", "north", 0, NFLATS_FATIGUE);
    add_exit(NFLATS_DIR + "nflats22", "east", 0, NFLATS_FATIGUE);
    add_exit(NFLATS_DIR + "nflats19", "southeast", 0, NFLATS_FATIGUE);
    add_exit(NFLATS_DIR + "nflats18", "south", 0, NFLATS_FATIGUE);
    add_exit(NFLATS_DIR + "nflats17", "southwest", 0, NFLATS_FATIGUE);
    add_exit(NFLATS_DIR + "nflats20", "west", 0, NFLATS_FATIGUE);
}
