inherit "/std/room";

#include <stdproperties.h>

void create_room()
{
    set_short("A stone passageway");
    set_long("A narrow, stone passageway leading through the " +
        "underground portion of the temple.\n");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, -2);

    add_exit("altarroom", "up");
    add_exit("hall3", "north");
    add_exit("hall1", "south");
}
