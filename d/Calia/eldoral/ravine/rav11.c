#include "defs.h"

inherit RAVBASE;

public void
create_room()
{
    create_ravine();
    create_wall("west");
    add_exit(RAVINE + "rav10", "east");
}
