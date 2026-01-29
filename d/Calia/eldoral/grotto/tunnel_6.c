#include "../caverns/defs.h"

inherit CAVBASE;

public void
create_room()
{
    create_cavern(2);
    dir_up = ({"north"});
    create_base();

    add_exit(GROTTO + "tunnel_5", "north");
    add_exit(GROTTO + "bot_stairs", "up");
}
