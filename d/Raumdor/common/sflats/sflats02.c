#include "defs.h"
inherit SFLATS_ROOM;

void
create_room()
{
    ::create_room();

    set_no_exit_msg(({"southwest", "south"}),
      "Mountains rise in that direction, preventing passage.\n");
    add_exit(FOREST_DIR + "wforest02", "northwest", 0, SFLATS_FATIGUE);
    add_exit(FOREST_DIR + "wforest03", "north", 0, SFLATS_FATIGUE);
    add_exit(FOREST_DIR + "wforest04", "northeast", 0, SFLATS_FATIGUE);
    add_exit(SFLATS_DIR + "sflats03", "east", 0, SFLATS_FATIGUE);
    add_exit(SFLATS_DIR + "sflats07", "southeast", 0, SFLATS_FATIGUE);
    add_exit(SFLATS_DIR + "sflats01", "west", 0, SFLATS_FATIGUE);
}
