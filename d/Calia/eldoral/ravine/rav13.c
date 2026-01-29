#include "defs.h"

inherit RAVBASE;

public void
create_room()
{
    create_ravine();
    create_wall("north");
    add_exit(RAVINE + "rav8", "north");
    add_exit(RAVINE + "rav7", "east");
    add_exit(RAVINE + "rav6", "south");
    add_exit(RAVINE + "rav9", "west");
}
