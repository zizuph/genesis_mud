#include "defs.h"
inherit NFLATS_ROOM;

void
create_room()
{
    ::create_room();

    set_no_exit_msg(({"west", "northwest", "north"}),
      "Mountains rise in that direction, preventing passage.\n");
    add_exit(NFLATS_DIR + "nflats20", "northeast", 0, NFLATS_FATIGUE);
    add_exit(NFLATS_DIR + "nflats17", "east", 0, NFLATS_FATIGUE);
    add_exit(NFLATS_DIR + "nflats13", "southeast", 0, NFLATS_FATIGUE);
    add_exit(NFLATS_DIR + "nflats12", "south", 0, NFLATS_FATIGUE);
    add_exit(NFLATS_DIR + "nflats11", "southwest", 0, NFLATS_FATIGUE);
}
