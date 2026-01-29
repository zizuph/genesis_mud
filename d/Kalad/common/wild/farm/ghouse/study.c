inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

void
create_room()
{
    ::create_room();

    set_short("Study");
    set_long(BS("\nStudy.\n\n"));

    add_exit(FARM(ghouse/hall2), "east", 0, 0, 0);

    add_prop(ROOM_I_INSIDE, 1);
}

