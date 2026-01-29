#include "defs.h"
inherit NFLATS_ROOM;

void
create_room()
{
    ::create_room();

    add_exit(NFLATS_DIR + "nflats17", "northwest", 0, NFLATS_FATIGUE);
    add_exit(NFLATS_DIR + "nflats18", "north", 0, NFLATS_FATIGUE);
    add_exit(NFLATS_DIR + "nflats19", "northeast", 0, NFLATS_FATIGUE);
    add_exit(NFLATS_DIR + "nflats15", "east", 0, NFLATS_FATIGUE);
    add_exit(NFLATS_DIR + "nflats06", "southwest", 0, NFLATS_FATIGUE);
    add_exit(NFLATS_DIR + "nflats07", "south", 0, NFLATS_FATIGUE);
    add_exit(NFLATS_DIR + "nflats08", "southeast", 0, NFLATS_FATIGUE);
    add_exit(NFLATS_DIR + "nflats13", "west", 0, NFLATS_FATIGUE);
}
