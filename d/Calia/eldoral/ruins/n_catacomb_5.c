#pragma strict_types

#include "defs.h"

inherit CATBASE;

void
create_room()
{
    create_catacomb();

    add_exit(RUIN + "n_catacomb_6", "east");
    add_exit(RUIN + "n_catacomb_7", "south");
    add_exit(RUIN + "n_catacomb_4", "west");
}
