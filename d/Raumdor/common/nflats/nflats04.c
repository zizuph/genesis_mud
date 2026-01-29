#include "defs.h"
inherit NFLATS_ROOM;

void
create_room()
{
    ::create_room();

    add_exit(NFLATS_DIR + "nflats10", "northwest", 0, NFLATS_FATIGUE);
    add_exit(NFLATS_DIR + "nflats11", "north", 0, NFLATS_FATIGUE);
    add_exit(NFLATS_DIR + "nflats12", "northeast", 0, NFLATS_FATIGUE);
    add_exit(NFLATS_DIR + "nflats05", "east", 0, NFLATS_FATIGUE);
    add_exit(FOREST_DIR + "wforest77", "southeast", 0, NFLATS_FATIGUE);
    add_exit(FOREST_DIR + "wforest76", "south", 0, NFLATS_FATIGUE);
    add_exit(FOREST_DIR + "wforest75", "southwest", 0, NFLATS_FATIGUE);
    add_exit(NFLATS_DIR + "nflats03", "west", 0, NFLATS_FATIGUE);
}
