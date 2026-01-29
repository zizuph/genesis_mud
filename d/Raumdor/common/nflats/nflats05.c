#include "defs.h"
inherit NFLATS_ROOM;

void
create_room()
{
    ::create_room();

    add_exit(NFLATS_DIR + "nflats11", "northwest", 0, NFLATS_FATIGUE);
    add_exit(NFLATS_DIR + "nflats12", "north", 0, NFLATS_FATIGUE);
    add_exit(NFLATS_DIR + "nflats13", "northeast", 0, NFLATS_FATIGUE);
    add_exit(NFLATS_DIR + "nflats06", "east", 0, NFLATS_FATIGUE);
    add_exit(FOREST_DIR + "wforest78", "southeast", 0, NFLATS_FATIGUE);
    add_exit(FOREST_DIR + "wforest77", "south", 0, NFLATS_FATIGUE);
    add_exit(FOREST_DIR + "wforest76", "southwest", 0, NFLATS_FATIGUE);
    add_exit(NFLATS_DIR + "nflats04", "west", 0, NFLATS_FATIGUE);
}
