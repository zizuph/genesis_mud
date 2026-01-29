inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

void
create_room()
{
    ::create_room();

    set_short("");
    set_long(BS("\n.\n\n"));

    add_exit(FARM(), "", 0, 0, 0);

    add_prop(ROOM_I_INSIDE, 1);
}

