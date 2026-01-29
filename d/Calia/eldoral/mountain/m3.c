#pragma strict_types

#include "defs.h"

inherit MOUNTBASE;

public void
create_room()
{
    create_trail();
    add_exit(MOUNT + "m4", "northeast");
    add_exit(MOUNT + "m2", "south");
}
