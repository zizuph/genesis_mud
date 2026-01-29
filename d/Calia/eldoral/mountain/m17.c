#pragma strict_types

#include "defs.h"

inherit MOUNTBASE;

public void
create_room()
{
    create_ruins(3);
    create_close_shore();
    create_trail();
    add_exit(MOUNT + "mshore3", "north");
    add_exit(MOUNT + "m16", "west");
    add_exit(MOUNT + "m14", "south");
}
