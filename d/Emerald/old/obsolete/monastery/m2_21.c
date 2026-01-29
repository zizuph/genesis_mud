#include "defs.h"

inherit MONASTERY_BASE;

nomask void
create_monastery_room()
{
    set_short("Library");
    set_long("Library\n");

    add_door_exit(0, MONASTERY_DIR + "m2_31", "east");
    add_door_exit(0, MONASTERY_DIR + "m2_20", "south");
}
