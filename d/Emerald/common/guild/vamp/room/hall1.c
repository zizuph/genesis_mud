#include "../guild.h"

inherit VAMP_ROOM_DIR + "vamp_room";

#include <stdproperties.h>

void create_vamp_room()
{
    set_short("A stone passageway");
    set_long("A narrow, stone passageway leading through the " +
        "underground portion of the temple.\n");

    add_exit("hall2", "north");
    add_exit("start", "down");
}
