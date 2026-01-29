#pragma strict_types

#include "defs.h"

inherit CATBASE;

void
create_room()
{
    create_catacomb();

    add_exit(RUIN + "n_catacomb_1", "north");
    add_exit(RUIN + "catacomb_hub", "east");
    add_exit(RUIN + "catacomb_1", "west");
}
