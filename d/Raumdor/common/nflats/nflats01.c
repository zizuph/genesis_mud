#include "defs.h"
inherit NFLATS_ROOM;

void
create_room()
{
    ::create_room();

    set_no_exit_msg(
      "west", "Cold waters dissuade you from proceeding that way.\n");
    set_no_exit_msg(({"northwest", "north"}),
      "Mountains rise in that direction, preventing passage.\n");
    add_exit(NFLATS_DIR + "nflats09", "northeast", 0, NFLATS_FATIGUE);
    add_exit(NFLATS_DIR + "nflats02", "east", 0, NFLATS_FATIGUE);
    add_exit(FOREST_DIR + "wforest73", "south", 0, NFLATS_FATIGUE);
    add_exit(FOREST_DIR + "wforest74", "southeast", 0, NFLATS_FATIGUE);
}
