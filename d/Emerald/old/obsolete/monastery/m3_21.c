#include "defs.h"

inherit MONASTERY_BASE;

nomask void
create_monastery_room()
{
    set_short("Unknown");
    set_long("Unknown\n");

    add_exit("m3_20", "south");
}
