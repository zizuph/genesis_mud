#include "defs.h"
inherit NFLATS_ROOM;

void
create_room()
{
    ::create_room();

    add_exit(NFLATS_DIR + "nflats14", "northeast", 0, NFLATS_FATIGUE);
    add_exit(NFLATS_DIR + "nflats13", "north", 0, NFLATS_FATIGUE);
    add_exit(NFLATS_DIR + "nflats12", "northwest", 0, NFLATS_FATIGUE);
    add_exit(NFLATS_DIR + "nflats07", "east", 0, NFLATS_FATIGUE);
    add_exit(FOREST_DIR + "wforest79", "southeast", 0, NFLATS_FATIGUE);
    add_exit(FOREST_DIR + "wforest78", "south", 0, NFLATS_FATIGUE);
    add_exit(FOREST_DIR + "wforest77", "southwest", 0, NFLATS_FATIGUE);
    add_exit(NFLATS_DIR + "nflats05", "west", 0, NFLATS_FATIGUE);
}
