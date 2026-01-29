inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

void
create_room()
{
    ::create_room();

    set_short("Kitchen");
    set_long(BS("\nKitchen.\n\n"));

    add_exit(FARM(ghouse/hall2), "west", 0, 0, 0);

    add_prop(ROOM_I_INSIDE, 1);
}

