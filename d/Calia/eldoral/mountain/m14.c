#pragma strict_types

#include "defs.h"

inherit MOUNTBASE;

public void
create_room()
{
    create_trail();
    add_exit(MOUNT + "m17", "north");
    add_exit(MOUNT + "m13", "west");
    add_exit(MOUNT + "m11", "southwest");
}
