#include "defs.h"
inherit NFLATS_ROOM;

void
create_room()
{
    ::create_room();

    set_no_exit_msg(({"west", "northwest", "north", "northeast", "east"}),
      "Mountains rise in that direction, preventing passage.\n");
    add_exit(NFLATS_DIR + "nflats22", "southeast", 0, NFLATS_FATIGUE);
    add_exit(NFLATS_DIR + "nflats21", "south", 0, NFLATS_FATIGUE);
    add_exit(NFLATS_DIR + "nflats20", "southwest", 0, NFLATS_FATIGUE);

    //clone_object("/d/Raumdor/common/obj/nexus_app")->move(TO, 1);
}
