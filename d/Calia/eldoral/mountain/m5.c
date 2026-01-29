#pragma strict_types

#include "defs.h"

inherit MOUNTBASE;

public void
create_room()
{
    create_trail();
    add_exit(MOUNT + "m6", "west");
    add_exit(MOUNT + "m4", "southeast");
}
