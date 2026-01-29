#include "defs.h"

inherit MONASTERY_BASE;

nomask void
create_monastery_room()
{
    set_short("Guest bedroom");
    set_long("Guest bedroom\n");

    add_exit("m3_03", "north");
    add_exit("m3_01", "south");

    load_clone_handler = 1;
}
