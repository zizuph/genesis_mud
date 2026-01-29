#pragma strict_types

#include "defs.h"

inherit MOUNTBASE;

public void
create_room()
{
    create_ruins(1);
    create_ruins(2);
    create_trail();
    add_exit(MOUNT + "m15", "north");
    add_exit(MOUNT + "m13", "east");
    add_exit(MOUNT + "m11", "southeast");
}
