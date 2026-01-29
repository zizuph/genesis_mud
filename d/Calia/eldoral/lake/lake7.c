#include "defs.h"

inherit LAKEBASE;

public void
create_room()
{
    create_shore("north", 1);
    create_lake();

    add_exit(LAKE + "lake8", "north");
    add_exit(LAKE + "lake6", "south");
}
