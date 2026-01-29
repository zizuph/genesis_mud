#pragma strict_types

#include "defs.h"

inherit MOUNTBASE;

public void
create_room()
{
    create_trail();
    add_exit(MOUNT + "m3", "north");
    add_exit(MOUNT + "m1", "southeast");
}
