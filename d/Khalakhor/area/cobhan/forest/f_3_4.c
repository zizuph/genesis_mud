/* File:          /d/Khalakhor/cobhan/forest/f_3_4.c
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
    add_my_desc("Deep forest. \n");

    add_exit(FOREST + "f_2_4", "west", 0, 3, 1);
    add_exit(FOREST + "f_2_5", "northwest", 0, 3, 1);
    add_exit(FOREST + "f_3_5", "north", 0, 3, 1);
    add_exit(FOREST + "f_4_5", "northeast", 0, 3, 1);
    add_exit(FOREST + "f_4_4", "east", 0, 3, 1);
    add_exit(FOREST + "f_4_3", "southeast", 0, 3, 1);
    add_exit(FOREST + "f_3_3", "south", 0, 3, 1);
    add_exit(FOREST + "f_2_3", "southwest", 0, 3, 1);
}

