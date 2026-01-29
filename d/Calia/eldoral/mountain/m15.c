#pragma strict_types

#include "defs.h"

inherit MOUNTBASE;

public void
create_room()
{
    create_ruins(2);
    create_close_shore();
    create_trail();
    add_exit(MOUNT + "mshore1", "north");
    add_exit(MOUNT + "m16", "east");
    add_exit(MOUNT + "m12", "south");
}
