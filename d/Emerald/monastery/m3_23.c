#include "defs.h"

inherit MONASTERY_BASE;

nomask void
create_monastery_room()
{
    set_short("Hallway");
    set_long("Hallway\n");

    add_exit("m3_33", "east");
    add_exit("m3_13", "west");
    add_exit("m3_22", "south");
}
