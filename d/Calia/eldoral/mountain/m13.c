#pragma strict_types

#include "defs.h"

inherit MOUNTBASE;

public void
create_room()
{
    create_ruins(3);
    create_trail();
    add_exit(MOUNT + "m16", "north");
    add_exit(MOUNT + "m14", "east");
    add_exit(MOUNT + "m12", "west");
    add_exit(MOUNT + "m11", "south");
}
