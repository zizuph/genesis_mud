/*
 * Path from beach to Ten Alders South Path
 * by Ckrik Nov 1997
 */

#pragma strict_types
#pragma no_clone

#include "default.h"

inherit PATH;

public void
create_path()
{
    add_my_desc("You are high up on the slope.\n");
    add_item("slope",
        "A gentle down slope heading down to the beach.\n");

    add_exit("/d/Earthsea/gont/tenalders/south_path/south_path_24", "north");
    add_exit("forest_path05", "south");
}
