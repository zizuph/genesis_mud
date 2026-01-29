#include "defs.h"

inherit LAKEBASE;

public void
create_room()
{
    create_lake();

    add_exit(LAKE + "lake5", "north");
    add_exit(LAKE + "lake3", "south");
}
