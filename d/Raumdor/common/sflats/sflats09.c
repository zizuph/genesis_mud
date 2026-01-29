#include "defs.h"
inherit SFLATS_ROOM;

void
create_room()
{
    ::create_room();

    add_exit(SFLATS_DIR + "sflats04", "northwest", 0, SFLATS_FATIGUE);
    add_exit(SFLATS_DIR + "sflats05", "north", 0, SFLATS_FATIGUE);
    add_exit(SFLATS_DIR + "sflats06", "northeast", 0, SFLATS_FATIGUE);
    add_exit(SFLATS_DIR + "sflats10", "east", 0, SFLATS_FATIGUE);
    add_exit(SFLATS_DIR + "sflats12", "south", 0, SFLATS_FATIGUE);
    add_exit(SFLATS_DIR + "sflats11", "southwest", 0, SFLATS_FATIGUE);
    add_exit(SFLATS_DIR + "sflats08", "west", 0, SFLATS_FATIGUE);
}
