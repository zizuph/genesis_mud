#include "defs.h"

inherit LAKEBASE;

public void
create_room()
{
    create_lake();

    add_exit(LAKE + "lake7", "north");
    add_exit(LAKE + "lake5", "south");
}
