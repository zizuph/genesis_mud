#include "defs.h"
inherit SFLATS_ROOM;

void
create_room()
{
    ::create_room();

    set_no_exit_msg(({"south", "southeast", "east", "northeast"}),
      "Mountains rise in that direction, preventing passage.\n");
    add_exit(SFLATS_DIR + "sflats06", "north", 0, SFLATS_FATIGUE);
    add_exit(SFLATS_DIR + "sflats05", "northwest", 0, SFLATS_FATIGUE);
    add_exit(SFLATS_DIR + "sflats12", "southwest", 0, SFLATS_FATIGUE);
    add_exit(SFLATS_DIR + "sflats09", "west", 0, SFLATS_FATIGUE);
}
