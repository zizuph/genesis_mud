/* File:          /d/Khalakhor/cobhan/forest/f_2_8.c
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
    set_logged(3);
    set_up_forest();
    set_long("@@my_long");
    add_my_desc("Ravaged forest. \n");

    add_exit(PLAINS + "p_5_9", "west", "@@enter_plains", 3, 1);
    add_exit(PLAINS + "p_5_10", "northwest", "@@enter_plains", 3, 1);
    add_exit(PLAINS + "p_6_10", "north", "@@enter_plains", 3, 1);
    add_exit(FOREST + "null", "northeast", "@@block_mountain", 3, 1);
    add_exit(FOREST + "null", "east", "@@block_mountain", 3, 1);
    add_exit(FOREST + "f_3_7", "southeast", 0, 3, 1);
    add_exit(FOREST + "f_2_7", "south", 0, 3, 1);
    add_exit(PLAINS + "p_5_8", "southwest", "@@enter_plains", 3, 1);
}

