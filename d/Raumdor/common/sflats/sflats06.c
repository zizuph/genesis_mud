#include "defs.h"
inherit SFLATS_ROOM;

void
create_room()
{
    ::create_room();

    set_no_exit_msg(({"southeast", "east"}),
      "Mountains rise in that direction, preventing passage.\n");
    add_exit(FOREST_DIR + "wforest06", "northwest", 0, SFLATS_FATIGUE);
    add_exit(FOREST_DIR + "wforest07", "north", 0, SFLATS_FATIGUE);
    add_exit(FOREST_DIR + "wforest08", "northeast", 0, SFLATS_FATIGUE);
    add_exit(SFLATS_DIR + "sflats10", "south", 0, SFLATS_FATIGUE);
    add_exit(SFLATS_DIR + "sflats09", "southwest", 0, SFLATS_FATIGUE);
    add_exit(SFLATS_DIR + "sflats05", "west", 0, SFLATS_FATIGUE);
}
