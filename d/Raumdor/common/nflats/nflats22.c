#include "defs.h"
inherit NFLATS_ROOM;

void
create_room()
{
    ::create_room();

    set_no_exit_msg(({"north", "northeast"}),
      "Mountains rise in that direction, preventing passage.\n");
    add_exit(NFLATS_DIR + "nflats24", "northwest", 0, NFLATS_FATIGUE);
    add_exit(NFLATS_DIR + "nflats23", "east", 0, NFLATS_FATIGUE);
    add_exit(FOREST_DIR + "nforest25", "southeast", 0, NFLATS_FATIGUE);
    add_exit(NFLATS_DIR + "nflats19", "south", 0, NFLATS_FATIGUE);
    add_exit(NFLATS_DIR + "nflats18", "southwest", 0, NFLATS_FATIGUE);
    add_exit(NFLATS_DIR + "nflats21", "west", 0, NFLATS_FATIGUE);
}
