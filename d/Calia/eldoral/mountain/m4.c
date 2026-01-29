#pragma strict_types

#include "defs.h"

inherit MOUNTBASE;

public void
create_room()
{
    create_trail();
    add_exit(MOUNT + "m5", "northwest");
    add_exit(MOUNT + "m3", "southwest");
}
