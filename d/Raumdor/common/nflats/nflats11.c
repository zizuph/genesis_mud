#include "defs.h"
inherit NFLATS_ROOM;

void
create_room()
{
    ::create_room();

    set_no_exit_msg(({"northwest", "north"}),
      "Mountains rise in that direction, preventing passage.\n");
    add_exit(NFLATS_DIR + "nflats16", "northeast", 0, NFLATS_FATIGUE);
    add_exit(NFLATS_DIR + "nflats12", "east", 0, NFLATS_FATIGUE);
    add_exit(NFLATS_DIR + "nflats05", "southeast", 0, NFLATS_FATIGUE);
    add_exit(NFLATS_DIR + "nflats04", "south", 0, NFLATS_FATIGUE);
    add_exit(NFLATS_DIR + "nflats03", "southwest", 0, NFLATS_FATIGUE);
    add_exit(NFLATS_DIR + "nflats10", "west", 0, NFLATS_FATIGUE);
}
