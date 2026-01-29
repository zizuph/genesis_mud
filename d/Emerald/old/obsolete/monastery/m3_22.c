#include "defs.h"

inherit MONASTERY_BASE;

nomask void
create_monastery_room()
{
    set_short("Kitchen");
    set_long("Kitchen\n");

    add_exit("m3_23", "north");
}
