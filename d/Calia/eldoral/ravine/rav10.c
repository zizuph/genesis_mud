#include "defs.h"

inherit RAVBASE;

public void
create_room()
{
    create_ravine();
    create_wall("west");
    add_exit(RAVINE + "rav9", "north");
    add_exit(RAVINE + "rav6", "east");
    add_exit(RAVINE + "rav12", "south");
    add_exit(RAVINE + "rav11", "west");
}
