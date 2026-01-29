inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

void
create_room()
{
    ::create_room();

    set_short("Bedroom");
    set_long(BS("\nBedroom 1.\n\n"));

    add_exit(FARM(ghouse/hall3), "south", 0, 0, 0);

    add_prop(ROOM_I_INSIDE, 1);
}

