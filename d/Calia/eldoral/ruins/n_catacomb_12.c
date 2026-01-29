#pragma strict_types

#include "defs.h"

inherit CATBASE;

void
create_room()
{
    create_catacomb();

    add_exit(RUIN + "n_catacomb_10", "north");
    add_exit(RUIN + "n_catacomb_13", "east");
}
