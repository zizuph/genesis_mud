#include "defs.h"
inherit NFLATS_ROOM;

void
create_room()
{
    ::create_room();

    add_exit(NFLATS_DIR + "nflats16", "north", 0, NFLATS_FATIGUE);
    add_exit(NFLATS_DIR + "nflats17", "northeast", 0, NFLATS_FATIGUE);
    add_exit(NFLATS_DIR + "nflats13", "east", 0, NFLATS_FATIGUE);
    add_exit(NFLATS_DIR + "nflats06", "southeast", 0, NFLATS_FATIGUE);
    add_exit(NFLATS_DIR + "nflats05", "south", 0, NFLATS_FATIGUE);
    add_exit(NFLATS_DIR + "nflats04", "southwest", 0, NFLATS_FATIGUE);
    add_exit(NFLATS_DIR + "nflats11", "west", 0, NFLATS_FATIGUE);
}
