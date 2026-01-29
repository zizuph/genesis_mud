/* File:          /d/Khalakhor/cobhan/plains/p_5_8.c
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

    add_exit(PLAINS + "p_4_8", "west", 0, 2, 1);
    add_exit(PLAINS + "p_4_9", "northwest", 0, 2, 1);
    add_exit(PLAINS + "p_5_9", "north", 0, 2, 1);
    add_exit(FOREST + "f_2_8", "northeast", "@@enter_forest", 3, 1);
    add_exit(FOREST + "f_2_7", "east", "@@enter_forest", 3, 1);
    add_exit(FOREST + "f_2_6", "southeast", "@@enter_forest", 3, 1);
    add_exit(PLAINS + "p_5_7", "south", 0, 2, 1);
    add_exit(PLAINS + "p_4_7", "southwest", 0, 2, 1);
}

