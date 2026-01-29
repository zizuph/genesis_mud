#include "defs.h"

inherit MONASTERY_BASE;

nomask void
create_monastery_room()
{
    set_short("Library");
    set_long("Library\n");

    add_door_exit(0, MONASTERY_DIR + "m2_32", "east");
    add_door_exit(0, MONASTERY_DIR + "m2_23", "north");
}
