#include "defs.h"

inherit RAVBASE;

public void
create_room()
{
    create_ravine();
    create_wall("east");
    add_exit(RAVINE + "rav7", "north");
    add_exit(RAVINE + "rav5", "east");
    add_exit(RAVINE + "rav3", "south");
    add_exit(RAVINE + "rav6", "west");
}
