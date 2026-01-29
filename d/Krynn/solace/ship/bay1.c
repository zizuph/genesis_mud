inherit "/std/room";
#include <stdproperties.h>

create_room()
{
    set_short("In a bay on Newsea");
    set_long("You are in the bay of the Newsea. Newports is " +
        "nearby, with piers for ships such as these.\n");
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
}
