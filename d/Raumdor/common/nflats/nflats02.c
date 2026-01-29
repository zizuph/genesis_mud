#include "defs.h"
inherit NFLATS_ROOM;

void
create_room()
{
    ::create_room();

    add_exit(NFLATS_DIR + "nflats09", "north", 0, NFLATS_FATIGUE);
    add_exit(NFLATS_DIR + "nflats10", "northeast", 0, NFLATS_FATIGUE);
    add_exit(NFLATS_DIR + "nflats03", "east", 0, NFLATS_FATIGUE);
    add_exit(FOREST_DIR + "wforest73", "southwest", 0, NFLATS_FATIGUE);
    add_exit(FOREST_DIR + "wforest74", "south", 0, NFLATS_FATIGUE);
    add_exit(FOREST_DIR + "wforest75", "southeast", 0, NFLATS_FATIGUE);
    add_exit(NFLATS_DIR + "nflats01", "west", 0, NFLATS_FATIGUE);
}
