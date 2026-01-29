#pragma strict_types

#include "defs.h"

inherit MOUNTBASE;

public void
create_room()
{
    create_ruins(1);
    create_trail();
    add_exit(MOUNT + "m7", "northeast");
    add_exit(MOUNT + "m5", "east");
}
