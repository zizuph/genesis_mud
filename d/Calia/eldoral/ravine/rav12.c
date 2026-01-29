#include "defs.h"

inherit RAVBASE;

public void
create_room()
{
    create_ravine();
    create_wall("southwest");
    add_exit(RAVINE + "rav10", "north");
    add_exit(RAVINE + "rav6", "northeast");
    add_exit("rav2", "east");
}
