#include "defs.h"
inherit SFLATS_ROOM;

void
create_room()
{
    ::create_room();

    add_exit(FOREST_DIR + "wforest03", "northwest", 0, SFLATS_FATIGUE);
    add_exit(FOREST_DIR + "wforest04", "north", 0, SFLATS_FATIGUE);
    add_exit(FOREST_DIR + "wforest05", "northeast", 0, SFLATS_FATIGUE);
    add_exit(SFLATS_DIR + "sflats04", "east", 0, SFLATS_FATIGUE);
    add_exit(SFLATS_DIR + "sflats08", "southeast", 0, SFLATS_FATIGUE);
    add_exit(SFLATS_DIR + "sflats07", "south", 0, SFLATS_FATIGUE);
    add_exit(SFLATS_DIR + "sflats02", "west", 0, SFLATS_FATIGUE);
}
