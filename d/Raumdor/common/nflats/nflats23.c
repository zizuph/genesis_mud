#include "defs.h"
inherit NFLATS_ROOM;

void
create_room()
{
    ::create_room();

    set_no_exit_msg(({"northwest", "north", "northeast"}),
      "Mountains rise in that direction, preventing passage.\n");
    add_exit(FOREST_DIR + "nforest37", "east", 0, NFLATS_FATIGUE);
    add_exit(FOREST_DIR + "nforest26", "southeast", 0, NFLATS_FATIGUE);
    add_exit(FOREST_DIR + "nforest25", "south", 0, NFLATS_FATIGUE);
    add_exit(NFLATS_DIR + "nflats19", "southwest", 0, NFLATS_FATIGUE);
    add_exit(NFLATS_DIR + "nflats22", "west", 0, NFLATS_FATIGUE);
}
