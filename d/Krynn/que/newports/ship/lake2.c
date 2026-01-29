inherit "/std/room";
#include <stdproperties.h>

create_room()
{
    set_short("On Newsea");
    set_long("You are somewhere out on Newsea.\n");
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
}
