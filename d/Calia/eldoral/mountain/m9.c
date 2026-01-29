#pragma strict_types

#include "defs.h"

inherit MOUNTBASE;

public void
create_room()
{
    create_ruins(3);
    create_trail();
    add_exit(MOUNT + "m11", "north");
    add_exit(MOUNT + "m7", "south");
}
