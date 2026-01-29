#include "defs.h"
inherit SFLATS_ROOM;

void
create_room()
{
    ::create_room();

    add_exit(SFLATS_DIR + "sflats03", "northwest", 0, SFLATS_FATIGUE);
    add_exit(SFLATS_DIR + "sflats04", "north", 0, SFLATS_FATIGUE);
    add_exit(SFLATS_DIR + "sflats05", "northeast", 0, SFLATS_FATIGUE);
    add_exit(SFLATS_DIR + "sflats09", "east", 0, SFLATS_FATIGUE);
    add_exit(SFLATS_DIR + "sflats12", "southeast", 0, SFLATS_FATIGUE);
    add_exit(SFLATS_DIR + "sflats11", "south", 0, SFLATS_FATIGUE);
    add_exit(SFLATS_DIR + "sflats10", "southwest", 0, SFLATS_FATIGUE);
    add_exit(SFLATS_DIR + "sflats07", "west", 0, SFLATS_FATIGUE);
}
