inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

void
create_room()
{
    ::create_room();

    set_short("Dining room");
    set_long(BS("\nDining room.\n\n"));

    add_exit(FARM(ghouse/hall2), "south", 0, 0, 0);

    add_prop(ROOM_I_INSIDE, 1);
}

