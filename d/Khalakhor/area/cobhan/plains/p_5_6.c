/* File:          /d/Khalakhor/cobhan/plains/p_5_6.c
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
    add_my_desc("Plains. Stream on north side with ruins rubble. \n");

    add_exit(PLAINS + "p_4_6", "west", 0, 2, 1);
    add_exit(PLAINS + "p_4_7", "northwest", "@@cross_stream", 4, 1);
    add_exit(PLAINS + "p_5_7", "north", "@@cross_stream", 4, 1);
    add_exit(FOREST + "f_2_6", "northeast", "@@enter_forest_thru_stream", 4, 1);
    add_exit(FOREST + "f_2_5", "east", "@@enter_forest_thru_stream", 4, 1);
    add_exit(FOREST + "f_2_4", "southeast", "@@enter_forest", 3, 1);
    add_exit(FOREST + "f_1_4", "south", "@@enter_forest", 3, 1);
    add_exit(PLAINS + "p_4_5", "southwest", 0, 2, 1);
}

