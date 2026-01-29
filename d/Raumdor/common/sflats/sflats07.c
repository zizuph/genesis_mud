#include "defs.h"
inherit SFLATS_ROOM;

void
create_room()
{
    ::create_room();

    set_no_exit_msg(({"west", "southwest", "south"}),
      "Mountains rise in that direction, preventing passage.\n");
    add_exit(SFLATS_DIR + "sflats02", "northwest", 0, SFLATS_FATIGUE);
    add_exit(SFLATS_DIR + "sflats03", "north", 0, SFLATS_FATIGUE);
    add_exit(SFLATS_DIR + "sflats04", "northeast", 0, SFLATS_FATIGUE);
    add_exit(SFLATS_DIR + "sflats08", "east", 0, SFLATS_FATIGUE);
    add_exit(SFLATS_DIR + "sflats11", "southeast", 0, SFLATS_FATIGUE);
    add_exit(SFLATS_DIR + "sflats02", "northwest", 0, SFLATS_FATIGUE);
}
