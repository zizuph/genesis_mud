#include "defs.h"

inherit MONASTERY_BASE;

nomask void
create_monastery_room()
{
    set_short("Hallway");
    set_long("Hallway\n");

    add_exit("m2_03", "down");
    add_exit("m3_13", "east");
    add_exit("m3_02", "south");
}
