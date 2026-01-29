#include "defs.h"
inherit NFLATS_ROOM;

void
create_room()
{
    ::create_room();

    add_exit(NFLATS_DIR + "nflats09", "northwest", 0, NFLATS_FATIGUE);
    add_exit(NFLATS_DIR + "nflats10", "north", 0, NFLATS_FATIGUE);
    add_exit(NFLATS_DIR + "nflats11", "northeast", 0, NFLATS_FATIGUE);
    add_exit(NFLATS_DIR + "nflats04", "east", 0, NFLATS_FATIGUE);
    add_exit(FOREST_DIR + "wforest76", "southeast", 0, NFLATS_FATIGUE);
    add_exit(FOREST_DIR + "wforest75", "south", 0, NFLATS_FATIGUE);
    add_exit(FOREST_DIR + "wforest74", "southwest", 0, NFLATS_FATIGUE);
    add_exit(NFLATS_DIR + "nflats02", "west", 0, NFLATS_FATIGUE);
}
