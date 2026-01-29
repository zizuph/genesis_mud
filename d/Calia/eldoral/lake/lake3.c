#include "defs.h"

inherit LAKEBASE;

public void
create_room()
{
    create_lake();

    add_exit(LAKE + "lake4", "north");
    add_exit(LAKE + "lake2", "south");
}
