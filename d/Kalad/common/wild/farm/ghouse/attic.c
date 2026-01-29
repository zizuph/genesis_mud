inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

void
create_room()
{
    ::create_room();

    set_short("Attic");
    set_long(BS("\nAttic.\n\n"));

    add_exit(FARM(ghouse/hall3), "down", 0, 0, 0);

    add_prop(ROOM_I_INSIDE, 1);
}

