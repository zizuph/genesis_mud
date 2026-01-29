#pragma strict_types

#include "defs.h"

inherit CATBASE;
inherit CRYPTDOORS;

public void
reset_room()
{
    ::reset_room();
    reset_doors();
}

void
create_room()
{
    create_catacomb();

    add_exit(RUIN + "n_catacomb_13", "north");
    add_crypt_door(RUIN + "crypt_1", "south");

    set_alarm(0.0, 0.0, reset_room);
}

public void
init()
{
    ::init();
    init_doors();
}

