inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

void
create_room()
{
    ::create_room();

    set_short("Corridor");
    set_long(BS("\nHall 3.\n\n"));

    add_exit(FARM(ghouse/bed1), "north", 0, 0, 0);
    add_exit(FARM(ghouse/bed2), "south", 0, 0, 0);
    add_exit(FARM(ghouse/bath), "east", 0, 0, 0);
    add_exit(FARM(ghouse/hall2), "down", 0, 0, 0);

    add_prop(ROOM_I_INSIDE, 1);
}

