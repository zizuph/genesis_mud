#pragma strict_types

#include "defs.h"

inherit CATBASE;

void
create_room()
{
    create_catacomb();

    add_exit(RUIN + "catacomb_2", "east");
    add_exit(RUIN + "w_tunnel_2", "west");
}
