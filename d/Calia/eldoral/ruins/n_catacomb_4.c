#pragma strict_types

#include "defs.h"

inherit CATBASE;

void
create_room()
{
    create_catacomb();

    add_exit(RUIN + "n_catacomb_5", "east");
    add_exit(RUIN + "n_catacomb_2", "south");
}
