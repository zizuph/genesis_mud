/* File:          /d/Khalakhor/cobhan/forest/f_3_6.c
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
    set_logged(1);
    set_up_forest();
    set_long("@@my_long");
    add_my_desc("Barely cut forest. \n");

    add_exit(FOREST + "f_2_6", "west", 0, 3, 1);
    add_exit(FOREST + "f_2_7", "northwest", 0, 3, 1);
    add_exit(FOREST + "f_3_7", "north", 0, 3, 1);
    add_exit(FOREST + "null", "northeast", "@@block_mountain", 3, 1);
    add_exit(FOREST + "f_4_6", "east", 0, 3, 1);
    add_exit(FOREST + "f_4_5", "southeast", 0, 3, 1);
    add_exit(FOREST + "f_3_5", "south", 0, 3, 1);
    add_exit(FOREST + "f_2_5", "southwest", 0, 3, 1);
}

