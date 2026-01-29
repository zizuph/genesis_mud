#include "defs.h"

inherit LAKEBASE;

public void
create_room()
{
    create_shore("north");
    create_lake();

    add_exit(SHORE + "shore1", "north");
    add_exit(LAKE + "lake7", "south");
}
