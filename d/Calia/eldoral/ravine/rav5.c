#include "defs.h"

inherit RAVBASE;

public void
create_room()
{
    create_ravine();
    create_wall("east");
    add_exit(RAVINE + "rav4", "west");
}
