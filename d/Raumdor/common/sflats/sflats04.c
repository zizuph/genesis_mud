#include "defs.h"
inherit SFLATS_ROOM;

void
create_room()
{
    ::create_room();

    add_exit(FOREST_DIR + "wforest04", "northwest", 0, SFLATS_FATIGUE);
    add_exit(FOREST_DIR + "wforest05", "north", 0, SFLATS_FATIGUE);
    add_exit(FOREST_DIR + "wforest06", "northeast", 0, SFLATS_FATIGUE);
    add_exit(SFLATS_DIR + "sflats05", "east", 0, SFLATS_FATIGUE);
    add_exit(SFLATS_DIR + "sflats09", "southeast", 0, SFLATS_FATIGUE);
    add_exit(SFLATS_DIR + "sflats08", "south", 0, SFLATS_FATIGUE);
    add_exit(SFLATS_DIR + "sflats07", "southwest", 0, SFLATS_FATIGUE);
    add_exit(SFLATS_DIR + "sflats03", "west", 0, SFLATS_FATIGUE);
}
