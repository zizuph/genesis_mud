inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

void
create_room()
{
    ::create_room();

    set_short("Hall");
    set_long(BS("\nHall 2.\n\n"));

    add_exit(FARM(ghouse/dining), "north", 0, 0, 0);
    add_exit(FARM(ghouse/hall1), "south", 0, 0, 0);
    add_exit(FARM(ghouse/study), "west", 0, 0, 0);
    add_exit(FARM(ghouse/kitchen), "east", 0, 0, 0);
    add_exit(FARM(ghouse/hall3), "up", 0, 0, 0);

    add_prop(ROOM_I_INSIDE, 1);
}

