#include "defs.h"

inherit RAVBASE;

public void
create_room()
{
    create_ravine();
    create_wall("southeast");
    add_exit(RAVINE + "rav4", "north");
    add_exit(RAVINE + "rav2", "west");
    add_exit(RAVINE + "rav6", "northwest");
}
