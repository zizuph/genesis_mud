#include "defs.h"
inherit NFLATS_ROOM;

void
create_room()
{
    ::create_room();

    set_no_exit_msg(({"west", "northwest", "north", "northeast"}),
      "Mountains rise in that direction, preventing passage.\n");
    add_exit(NFLATS_DIR + "nflats10", "east", 0, NFLATS_FATIGUE);
    add_exit(NFLATS_DIR + "nflats03", "southeast", 0, NFLATS_FATIGUE);
    add_exit(NFLATS_DIR + "nflats02", "south", 0, NFLATS_FATIGUE);
    add_exit(NFLATS_DIR + "nflats01", "southwest", 0, NFLATS_FATIGUE);
}
