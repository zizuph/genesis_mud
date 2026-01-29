#pragma strict_types

#include "defs.h"

inherit CATBASE;

void
create_room()
{
    create_catacomb();

    add_exit(RUIN + "n_catacomb_4", "north");
    add_exit(RUIN + "n_catacomb_1", "south");
}
