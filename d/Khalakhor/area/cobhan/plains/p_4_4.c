/* File:          /d/Khalakhor/cobhan/plains/p_4_4.c
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

    add_exit(PLAINS + "p_3_4", "west", 0, 2, 1);
    add_exit(PLAINS + "p_3_5", "northwest", 0, 2, 1);
    add_exit(PLAINS + "p_4_5", "north", 0, 2, 1);
    add_exit(FOREST + "f_1_4", "northeast", "@@enter_forest", 3, 1);
    add_exit(FOREST + "f_1_3", "east", "@@enter_forest", 3, 1);
    add_exit(FOREST + "f_1_2", "southeast", "@@enter_forest", 3, 1);
    add_exit(PLAINS + "p_4_3", "south", 0, 2, 1);
    add_exit(PLAINS + "p_3_3", "southwest", 0, 2, 1);
}

