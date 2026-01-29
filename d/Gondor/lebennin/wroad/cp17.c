/*
 *      /d/Gondor/lebennin/wroad/cp2.c
 *
 *      Path along the Gilrain river leading to a corsair camp
 *
 */

#pragma strict_types

#include "/d/Gondor/lebennin/std/defs.h"
inherit LEBENNIN_STD_DIR + "base";

static int _corsairs = 9;

void
create_lebennin_room()
{
    set_items_corsair_camp();

    set_short("A small path");
    set_long("A small path next to the river Gilrain. The banks of the river " +
        "stands tall to the east, with dense bushes obscuring the view from " +
        "the plains above.\n");

    add_exit(AREA_DIR + "wroad/cp22", "northwest", 0, 1);
    add_exit(AREA_DIR + "wroad/cp23", "north", 0, 1);
    add_exit(AREA_DIR + "wroad/cp24", "northeast", 0, 1);
    add_exit(AREA_DIR + "wroad/cp18", "east", 0, 1);
    add_exit(AREA_DIR + "wroad/cp21", "southeast", 0, 1);
    add_exit(AREA_DIR + "wroad/cp20", "south", 0, 1);
    add_exit(AREA_DIR + "wroad/cp19", "southwest", 0, 1);
    add_exit(AREA_DIR + "wroad/cp16", "west", 0, 1);

    add_npc(AREA_DIR + "wroad/npc/corsair_base", 3);
}
