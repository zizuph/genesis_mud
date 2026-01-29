#include "defs.h"

inherit MONASTERY_BASE;

nomask void
create_monastery_room()
{
    set_short("Guest bedroom");
    set_long("Guest bedroom\n");

    add_exit("m3_02", "north");

    load_clone_handler = 1;
}
