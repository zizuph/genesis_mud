#pragma strict_types

#include "defs.h"

inherit MOUNTBASE;

public void
create_room()
{
    create_trail();
    add_exit(MOUNT + "m12", "northwest");
    add_exit(MOUNT + "m13", "north");
    add_exit(MOUNT + "m14", "northeast");
    add_exit(MOUNT + "m10", "southeast");
    add_exit(MOUNT + "m9", "south");
    add_exit(MOUNT + "m8", "southwest");
}
