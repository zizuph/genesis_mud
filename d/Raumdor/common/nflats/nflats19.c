#include "defs.h"
inherit NFLATS_ROOM;

void
create_room()
{
    ::create_room();

    add_exit(NFLATS_DIR + "nflats21", "northwest", 0, NFLATS_FATIGUE);
    add_exit(NFLATS_DIR + "nflats22", "north", 0, NFLATS_FATIGUE);
    add_exit(NFLATS_DIR + "nflats23", "northeast", 0, NFLATS_FATIGUE);
    add_exit(FOREST_DIR + "nforest25", "east", 0, NFLATS_FATIGUE);
    add_exit(FOREST_DIR + "nforest13", "southeast", 0, NFLATS_FATIGUE);
    add_exit(NFLATS_DIR + "nflats15", "south", 0, NFLATS_FATIGUE);
    add_exit(NFLATS_DIR + "nflats14", "southwest", 0, NFLATS_FATIGUE);
    add_exit(NFLATS_DIR + "nflats18", "west", 0, NFLATS_FATIGUE);
}
