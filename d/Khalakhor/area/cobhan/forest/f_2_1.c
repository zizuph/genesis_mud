/* File:          /d/Khalakhor/cobhan/forest/f_2_1.c
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

    add_exit(PLAINS + "p_5_2", "west", "@@enter_plains", 3, 1);
    add_exit(FOREST + "f_1_2", "northwest", 0, 3, 1);
    add_exit(FOREST + "f_2_2", "north", 0, 3, 1);
    add_exit(FOREST + "f_3_2", "northeast", 0, 3, 1);
    add_exit(FOREST + "null", "east", "@@block_mountain", 3, 1);
    add_exit(FOREST + "null", "southeast", "@@block_mountain", 3, 1);
    add_exit(FOREST + "null", "south", "@@block_mountain", 3, 1);
    add_exit(FOREST + "null", "southwest", "@@block_mountain", 3, 1);
}

