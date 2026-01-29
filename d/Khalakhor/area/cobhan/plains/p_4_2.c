/* File:          /d/Khalakhor/cobhan/plains/p_4_2.c
 * Creator:       Teth
 * Date:          Dec 26 2001
 * Modifications:
 * Purpose:       This is a plains room in the area.
 * Related Files: /d/Khalakhor/cobhan/
 * Comments:
 */

#pragma save_binary
#pragma strict_types

#include "../local.h"

inherit CSTD + "plains_base";

public void
reset_plains_room()
{
}

public void
create_plains_room()
{
    set_up_plains();
    set_long("@@my_long");
    add_my_desc("Plains. \n");

    add_exit(PLAINS + "p_3_2", "west", 0, 2, 1);
    add_exit(PLAINS + "p_3_3", "northwest", 0, 2, 1);
    add_exit(PLAINS + "p_4_3", "north", 0, 2, 1);
    add_exit(FOREST + "f_1_2", "northeast", "@@enter_forest", 3, 1);
    add_exit(PLAINS + "p_5_2", "east", 0, 2, 1);
    add_exit(PLAINS + "null", "southeast", "@@block_mountain", 2, 1);
    add_exit(PLAINS + "p_4_1", "south", 0, 2, 1);
    add_exit(PLAINS + "p_3_1", "southwest", 0, 2, 1);
}

