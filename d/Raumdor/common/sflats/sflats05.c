#include "defs.h"
inherit SFLATS_ROOM;

void
create_room()
{
    ::create_room();

    add_exit(FOREST_DIR + "wforest05", "northwest", 0, SFLATS_FATIGUE);
    add_exit(FOREST_DIR + "wforest06", "north", 0, SFLATS_FATIGUE);
    add_exit(FOREST_DIR + "wforest07", "northeast", 0, SFLATS_FATIGUE);
    add_exit(SFLATS_DIR + "sflats06", "east", 0, SFLATS_FATIGUE);
    add_exit(SFLATS_DIR + "sflats10", "southeast", 0, SFLATS_FATIGUE);
    add_exit(SFLATS_DIR + "sflats09", "south", 0, SFLATS_FATIGUE);
    add_exit(SFLATS_DIR + "sflats08", "southwest", 0, SFLATS_FATIGUE);
    add_exit(SFLATS_DIR + "sflats04", "west", 0, SFLATS_FATIGUE);
}
