#include "defs.h"

inherit RAVBASE;

public void
create_room()
{
    create_ravine();
    set_long(main + "\n\n");
    add_exit(RAVINE + "rav13", "north");
    add_exit(RAVINE + "rav7", "northeast");
    add_exit(RAVINE + "rav4", "east");
    add_exit(RAVINE + "rav3", "southeast");
    add_exit(RAVINE + "rav2", "south");
    add_exit(RAVINE + "rav12", "southwest");
    add_exit(RAVINE + "rav10", "west");
    add_exit(RAVINE + "rav9", "northwest");
}
