inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>

public void
create_room()
{
   set_short("Open sea");
    set_long("   You are on the open sea, the blue green waters " +
        "sparkling with white as the wind blasts surf up.\n");
   add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
}
