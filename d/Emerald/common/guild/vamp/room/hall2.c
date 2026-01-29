#include "../guild.h"

inherit VAMP_ROOM_DIR + "vamp_room";

void create_vamp_room()
{
    set_short("A stone passageway");
    set_long("A narrow, stone passageway leading through the " +
        "underground portion of the temple.\n");

    add_exit("altarroom", "up");
    add_exit("hall3", "north");
    add_exit("hall1", "south");
    add_exit("library", "west");
}
