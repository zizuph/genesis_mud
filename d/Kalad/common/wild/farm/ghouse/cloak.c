inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

void
create_room()
{
    ::create_room();

    set_short("Cloakroom");
    set_long(BS("\nThis is more of a large cupboard than a room.  A rack of "
       +"pegs is fixed to one wall.\n\n"));

    add_exit(FARM(ghouse/hall1), "west", 0, 0, 0);

    add_prop(ROOM_I_INSIDE, 1);

}

