#pragma strict_types

#include "defs.h"

inherit CATBASE;

void
create_room()
{
    create_catacomb();

    add_exit(RUIN + "n_catacomb_8", "north");
    add_exit(RUIN + "n_catacomb_11", "east");
    add_exit(RUIN + "n_catacomb_12", "south");
}
