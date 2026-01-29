#include "defs.h"
inherit NFLATS_ROOM;

void
create_room()
{
    ::create_room();

    add_exit(NFLATS_DIR + "nflats20", "north", 0, NFLATS_FATIGUE);
    add_exit(NFLATS_DIR + "nflats21", "northeast", 0, NFLATS_FATIGUE);
    add_exit(NFLATS_DIR + "nflats18", "east", 0, NFLATS_FATIGUE);
    add_exit(NFLATS_DIR + "nflats14", "southeast", 0, NFLATS_FATIGUE);
    add_exit(NFLATS_DIR + "nflats13", "south", 0, NFLATS_FATIGUE);
    add_exit(NFLATS_DIR + "nflats12", "southwest", 0, NFLATS_FATIGUE);
    add_exit(NFLATS_DIR + "nflats16", "west", 0, NFLATS_FATIGUE);
}
