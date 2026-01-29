#include "defs.h"

inherit RAVBASE;

public void
create_room()
{
    create_ravine();
    create_wall("northwest");
    add_exit(RAVINE + "rav13", "east");
    add_exit(RAVINE + "rav6", "southeast");
    add_exit(RAVINE + "rav10", "south");
}
