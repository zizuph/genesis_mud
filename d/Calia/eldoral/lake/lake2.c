#include "defs.h"

inherit LAKEBASE;

public void
create_room()
{
    create_shore("south", 1);
    create_lake();

    add_exit(LAKE + "lake3", "north");
    add_exit(LAKE + "lake1", "south");
}
