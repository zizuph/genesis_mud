#include "defs.h"
inherit NFLATS_ROOM;

void
create_room()
{
    ::create_room();

    add_exit(NFLATS_DIR + "nflats20", "northwest", 0, NFLATS_FATIGUE);
    add_exit(NFLATS_DIR + "nflats21", "north", 0, NFLATS_FATIGUE);
    add_exit(NFLATS_DIR + "nflats22", "northeast", 0, NFLATS_FATIGUE);
    add_exit(NFLATS_DIR + "nflats19", "east", 0, NFLATS_FATIGUE);
    add_exit(NFLATS_DIR + "nflats15", "southeast", 0, NFLATS_FATIGUE);
    add_exit(NFLATS_DIR + "nflats14", "south", 0, NFLATS_FATIGUE);
    add_exit(NFLATS_DIR + "nflats13", "southwest", 0, NFLATS_FATIGUE);
    add_exit(NFLATS_DIR + "nflats17", "west", 0, NFLATS_FATIGUE);
}
