#include "defs.h"

inherit MIST_PROMINENCE_BASE;

public void
create_prominence_room()
{
    add_exit("prominence05", "west");
    add_exit("prominence08", "north");

    set_tower_dir("west");
}
