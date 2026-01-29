#include "defs.h"

inherit MONASTERY_BASE;

nomask void
create_monastery_room()
{
    set_short("Bedroom");
    set_long("Bedroom\n");

    add_exit("m3_40", "south");
}
