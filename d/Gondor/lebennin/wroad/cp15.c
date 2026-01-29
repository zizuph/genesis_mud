/*
 *      /d/Gondor/lebennin/wroad/cp2.c
 *
 *      Path along the Gilrain river leading to a corsair camp
 *
 */

#pragma strict_types

#include "/d/Gondor/lebennin/std/defs.h"

inherit LEBENNIN_STD_DIR + "base";

void
create_lebennin_room()
{
    set_short("A small path");
    set_long("A small path next to the river Gilrain. The banks of the river " +
        "stands tall to the east, with dense bushes obscuring the view from " +
        "the plains above.\n");

    add_exit(AREA_DIR + "wroad/cp16", "east", 0, 1);
    add_exit(AREA_DIR + "wroad/cp9", "southwest", 0, 1);

    set_no_exit_msg(get_all_no_exits(({"w", "e"})),
        "Dense bushes block the way.\n");
}
