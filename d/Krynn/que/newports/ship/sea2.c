inherit "/std/room";
#include <stdproperties.h>

create_room()
{
    set_short("In the Ergothian Seas");
    set_long("You are far out in the Ergothian Seas. You see no land anywhere.\n");
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
}
