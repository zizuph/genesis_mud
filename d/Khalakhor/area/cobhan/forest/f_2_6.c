/* File:          /d/Khalakhor/cobhan/forest/f_2_6.c
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
    set_logged(2);
    set_up_forest();
    set_long("@@my_long");
    add_my_desc("Cut forest. \n");
    add_item("plains","The plains cannot be seen from here.\n");

    add_exit(PLAINS + "p_5_7", "west", "@@enter_plains", 3, 1);
    add_exit(PLAINS + "p_5_8", "northwest", "@@enter_plains", 3, 1);
    add_exit(FOREST + "f_2_7", "north", 0, 3, 1);
    add_exit(FOREST + "f_3_7", "northeast", 0, 3, 1);
    add_exit(FOREST + "f_3_6", "east", 0, 3, 1);
    add_exit(FOREST + "f_3_5", "southeast", 0, 3, 1);
    add_exit(FOREST + "f_2_5", "south", 0, 3, 1);
    add_exit(PLAINS + "p_5_6", "southwest", "@@enter_plains_thru_stream", 4, 1);
}

