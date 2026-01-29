#include "defs.h"
inherit NFLATS_ROOM;

void
create_room()
{
    ::create_room();

    add_exit(NFLATS_DIR + "nflats18", "northwest", 0, NFLATS_FATIGUE);
    add_exit(NFLATS_DIR + "nflats19", "north", 0, NFLATS_FATIGUE);
    add_exit(FOREST_DIR + "nforest25", "northeast", 0, NFLATS_FATIGUE);
    add_exit(FOREST_DIR + "nforest13", "east", 0, NFLATS_FATIGUE);
    add_exit(FOREST_DIR + "nforest01", "southeast", 0, NFLATS_FATIGUE);
    add_exit(NFLATS_DIR + "nflats08", "south", 0, NFLATS_FATIGUE);
    add_exit(NFLATS_DIR + "nflats07", "southwest", 0, NFLATS_FATIGUE);
    add_exit(NFLATS_DIR + "nflats14", "west", 0, NFLATS_FATIGUE);
}
