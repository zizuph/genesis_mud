#include "defs.h"
inherit NFLATS_ROOM;

void
create_room()
{
    ::create_room();

    add_exit(NFLATS_DIR + "nflats16", "northwest", 0, NFLATS_FATIGUE);
    add_exit(NFLATS_DIR + "nflats17", "north", 0, NFLATS_FATIGUE);
    add_exit(NFLATS_DIR + "nflats18", "northeast", 0, NFLATS_FATIGUE);
    add_exit(NFLATS_DIR + "nflats14", "east", 0, NFLATS_FATIGUE);
    add_exit(NFLATS_DIR + "nflats05", "southwest", 0, NFLATS_FATIGUE);
    add_exit(NFLATS_DIR + "nflats06", "south", 0, NFLATS_FATIGUE);
    add_exit(NFLATS_DIR + "nflats07", "southeast", 0, NFLATS_FATIGUE);
    add_exit(NFLATS_DIR + "nflats12", "west", 0, NFLATS_FATIGUE);
}
