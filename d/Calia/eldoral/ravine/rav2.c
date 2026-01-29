#include "defs.h"

inherit RAVBASE;

public void
create_room()
{
    create_ravine();
    create_wall("south");
    add_exit(RAVINE + "rav6", "north");
    add_exit(RAVINE + "rav3", "east");
    add_exit(RAVINE + "rav1", "south");
    add_exit(RAVINE + "rav12", "west");
}
