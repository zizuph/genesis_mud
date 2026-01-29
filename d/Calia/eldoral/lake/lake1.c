#include "defs.h"

inherit LAKEBASE;

public void
create_room()
{
    create_shore("south");
    create_lake();

    add_exit(LAKE + "lake2", "north");
    add_exit(MOUNT + "mshore2", "south");
}
