#pragma strict_types

#include "defs.h"

inherit CATBASE;

void
create_room()
{
    create_catacomb();

    add_exit(RUIN + "n_catacomb_9", "east");
    add_exit(RUIN + "n_catacomb_10", "south");
    add_exit(RUIN + "n_catacomb_6", "west");
}
