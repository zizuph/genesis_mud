
#pragma save_binary

inherit "/std/room";

#include "../goblins.h"

create_room()
{
    set_short("Goblin Chief Throneroom");
    set_long(BSNN("This is a magnificent throneroom."));

    add_exit(GOBLIN_CAVERN_DIR + "tunnel3", "north", "@@turns", 0);
}

turns()
{
    write(BSN("The tunnel turns southwest."));
}