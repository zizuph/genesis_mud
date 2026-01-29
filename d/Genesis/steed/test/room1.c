inherit "/std/room";
#include <stdproperties.h>

create_room()
{
    set_short("Steed test room 1. You are inside.");
    set_long("Steed test room 1. You are inside.\n");
    add_prop(ROOM_I_INSIDE, 1);
    add_exit("/d/Genesis/steed/test/room2", "out");
}
