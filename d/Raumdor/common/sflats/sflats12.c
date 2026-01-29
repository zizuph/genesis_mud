#include "defs.h"
inherit SFLATS_ROOM;

void
create_room()
{
    ::create_room();
    
    seteuid(getuid());

    set_no_exit_msg(({"southwest", "south", "southeast", "east"}),
      "Mountains rise in that direction, preventing passage.\n");
    add_exit(SFLATS_DIR + "sflats08", "northwest", 0, SFLATS_FATIGUE);
    add_exit(SFLATS_DIR + "sflats09", "north", 0, SFLATS_FATIGUE);
    add_exit(SFLATS_DIR + "sflats10", "northeast", 0, SFLATS_FATIGUE);
    add_exit(SFLATS_DIR + "sflats11", "west", 0, SFLATS_FATIGUE);
    
    add_npc("/d/Raumdor/common/npc/spy", 1);
}
