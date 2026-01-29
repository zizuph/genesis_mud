inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

void
create_room()
{
    ::create_room();

    set_short("Bathroom");
    set_long(BS("\nBathroom.\n\n"));

    add_exit(FARM(ghouse/hall3), "west", 0, 0, 0);

    add_prop(ROOM_I_INSIDE, 1);
}

