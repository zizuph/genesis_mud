#include "defs.h"
inherit NFLATS_ROOM;

void
create_room()
{
    ::create_room();

    add_exit(NFLATS_DIR + "nflats13", "northwest", 0, NFLATS_FATIGUE);
    add_exit(NFLATS_DIR + "nflats14", "north", 0, NFLATS_FATIGUE);
    add_exit(NFLATS_DIR + "nflats15", "northeast", 0, NFLATS_FATIGUE);
    add_exit(NFLATS_DIR + "nflats08", "east", 0, NFLATS_FATIGUE);
    add_exit(FOREST_DIR + "wforest80", "southeast", 0, NFLATS_FATIGUE);
    add_exit(FOREST_DIR + "wforest79", "south", 0, NFLATS_FATIGUE);
    add_exit(FOREST_DIR + "wforest78", "southwest", 0, NFLATS_FATIGUE);
    add_exit(NFLATS_DIR + "nflats06", "west", 0, NFLATS_FATIGUE);
}
