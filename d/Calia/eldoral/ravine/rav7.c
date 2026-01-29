#include "defs.h"

inherit RAVBASE;

public void
create_room()
{
    create_ravine();
    create_wall("northeast");
    add_exit(RAVINE + "rav4", "south");
    add_exit(RAVINE + "rav6", "southwest");
    add_exit(RAVINE + "rav13", "west");
}
