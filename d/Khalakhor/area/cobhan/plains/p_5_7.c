/* File:          /d/Khalakhor/cobhan/plains/p_5_7.c
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
    add_my_desc("Plains. Stream on south side with rubble from ruins. \n");

    add_exit(PLAINS + "p_4_7", "west", 0, 2, 1);
    add_exit(PLAINS + "p_4_8", "northwest", 0, 2, 1);
    add_exit(PLAINS + "p_5_8", "north", 0, 2, 1);
    add_exit(FOREST + "f_2_7", "northeast", "@@enter_forest", 3, 1);
    add_exit(FOREST + "f_2_6", "east", "@@enter_forest", 3, 1);
    add_exit(FOREST + "f_2_5", "southeast", "@@enter_forest_thru_stream", 4, 1);
    add_exit(PLAINS + "p_5_6", "south", "@@cross_stream", 4, 1);
    add_exit(PLAINS + "p_4_6", "southwest", "@@cross_stream", 4, 1);
}

