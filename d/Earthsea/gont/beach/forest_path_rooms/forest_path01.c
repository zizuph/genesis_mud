/*
 * Path from beach to Ten Alders South Path
 * by Ckrik Nov 1997
 */

#pragma strict_types
#pragma no_clone

#include "default.h"

inherit PATH;

#include "air_smell.h"

public void
create_path()
{
    add_my_desc("The beach is very close now. The gentle " +
                "sea breeze brings in cool fresh air from " +
                "the beach. You can hear the waves crashing " +
                "on to the beach.\n");
    add_item("slope",
        "A gentle down slope heading down to beach.\n");

    add_exit("forest_path02", "north");
    add_exit(BEACH_DIR + "beach05", "south");
}
