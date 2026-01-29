/*
 *      /d/Gondor/lebennin/wroad/cp2.c
 *
 *      Path along the Gilrain river leading to a corsair camp
 *
 */

#pragma strict_types

#include "/d/Gondor/lebennin/std/defs.h"

inherit AREA_DIR + "wroad/patrol_path";

void
create_lebennin_room()
{
    set_items_patrol();

    set_short("A small path");
    set_long("A small path next to the river Gilrain. The banks of the river " +
        "stands tall to the east, with dense bushes obscuring the view from " +
        "the plains above.\n");

    add_exit(AREA_DIR + "wroad/cp6", "north", 0, 1);
    add_exit(AREA_DIR + "wroad/cp15", "northeast", 0, 1);
    add_exit(AREA_DIR + "wroad/cp10", "east", 0, 1);
    add_exit(AREA_DIR + "wroad/cp11", "southeast", 0, 1);

    set_no_exit_msg(get_all_no_exits(({"n", "ne", "e", "se"})),
        "Dense bushes block the way.\n");
}
