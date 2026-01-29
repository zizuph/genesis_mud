#include "defs.h"

inherit RAVBASE;

public void
create_room()
{
    create_ravine();
    create_wall("north");
    add_exit(RAVINE + "rav13", "south");
}
