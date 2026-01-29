#pragma strict_types

#include "defs.h"

inherit MOUNTBASE;

public void
create_room()
{
    create_close_shore();
    create_trail();
    add_exit(MOUNT + "mshore2", "north");
    add_exit(MOUNT + "m17", "east");
    add_exit(MOUNT + "m15", "west");
    add_exit(MOUNT + "m13", "south");
}
