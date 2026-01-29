inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

void
create_room()
{
    ::create_room();

    set_short("Bedroom");
    set_long(BS("\nBedroom 2.\n\n"));

    add_exit(FARM(ghouse/hall3), "north", 0, 0, 0);
/*    add_exit(FARM(ghouse/attic), "up", @@secret, 0, 0); */

    add_prop(ROOM_I_INSIDE, 1);
}

