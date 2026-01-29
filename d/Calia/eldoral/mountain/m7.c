#pragma strict_types

#include "defs.h"

inherit MOUNTBASE;

public void
create_room()
{
    create_ruins(2);
    create_trail();
    add_exit(MOUNT + "m8", "northwest");
    add_exit(MOUNT + "m9", "north");
    add_exit(MOUNT + "m10", "northeast");
    add_exit(MOUNT + "m6", "southwest");
}
