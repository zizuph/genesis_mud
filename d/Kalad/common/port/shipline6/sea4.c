#include <stdproperties.h>
inherit "/std/room";

void
create_room()
{
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
    set_short("The sea");
    set_long("You are in the middle of the sea.\n");
}
