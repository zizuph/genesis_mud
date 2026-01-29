#include "/d/Emerald/defs.h"
#include "coramar.h"

inherit "/std/room";

void
create_room()
{
    set_short("You are asleep.");
    set_long("You are asleep.\n");

    add_prop(ROOM_I_LIGHT, -1);
   
    add_prop(ROOM_S_DARK_LONG, "You are asleep.\n");
    add_prop(ROOM_S_DARK_MSG, "You are sleeping, so you cannot");
}
