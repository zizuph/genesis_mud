#include "defs.h"
inherit SFLATS_ROOM;

void
create_room()
{
    ::create_room();

    set_no_exit_msg(
      "west", "Cold waters dissuade you from proceeding that way.\n");
    set_no_exit_msg(({"southwest", "south", "southeast"}),
      "Mountains rise in that direction, preventing passage.\n");
    add_exit(FOREST_DIR + "wforest01", "northwest", 0, SFLATS_FATIGUE);
    add_exit(FOREST_DIR + "wforest02", "north", 0, SFLATS_FATIGUE);
    add_exit(FOREST_DIR + "wforest03", "northeast", 0, SFLATS_FATIGUE);
    add_exit(SFLATS_DIR + "sflats02", "east", 0, SFLATS_FATIGUE);
}
