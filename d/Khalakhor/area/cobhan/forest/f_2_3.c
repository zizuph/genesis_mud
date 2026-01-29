/* File:          /d/Khalakhor/cobhan/forest/f_2_3.c
 * Creator:       Teth
 * Date:          Dec 25 2001
 * Modifications:
 * Purpose:       This is a forest room in the area.
 * Related Files: /d/Khalakhor/cobhan/
 * Comments:
 */

#pragma save_binary
#pragma strict_types

#include "../local.h"

inherit CSTD + "forest_base";

public void
reset_forest_room()
{
}

public void
create_forest_room()
{
    set_logged(0);
    set_up_forest();
    set_long("@@my_long");
    add_my_desc("Contains tree with dryad. \n");

    add_exit(FOREST + "f_1_3", "west", 0, 3, 1);
    add_exit(FOREST + "f_1_4", "northwest", 0, 3, 1);
    add_exit(FOREST + "f_2_4", "north", 0, 3, 1);
    add_exit(FOREST + "f_3_4", "northeast", 0, 3, 1);
    add_exit(FOREST + "f_3_3", "east", 0, 3, 1);
    add_exit(FOREST + "f_3_2", "southeast", 0, 3, 1);
    add_exit(FOREST + "f_2_2", "south", 0, 3, 1);
    add_exit(FOREST + "f_1_2", "southwest", 0, 3, 1);
}

