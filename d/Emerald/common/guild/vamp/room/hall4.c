#include "../guild.h"

inherit VAMP_ROOM_DIR + "vamp_room";

public int
north_block()
{
    if (this_player()->query_vamp_coven() != "Emerald")
    {
        write("Some force prevents you from entering.\n");
        return 1;
    }

    return 0;
}

void create_vamp_room()
{
    set_short("A stone passageway");
    set_long("A narrow, stone passageway leading through the " +
        "underground portion of the temple.\n");

    add_exit("hall3", "east");
    add_exit("storage", "north", north_block);
}
