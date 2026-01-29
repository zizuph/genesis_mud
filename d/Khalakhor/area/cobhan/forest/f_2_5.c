/* File:          /d/Khalakhor/cobhan/forest/f_2_5.c
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
    add_my_desc("Deep forest. Rubble in stream which passes through " +
      "centre. \n");

    add_exit(PLAINS + "p_5_6", "west", "@@enter_plains_thru_stream", 4, 1);
    add_exit(PLAINS + "p_5_7", "northwest", "@@enter_plains_thru_stream", 4,
      1);
    add_exit(FOREST + "f_2_7", "north", 0, 3, 1);
    add_exit(FOREST + "f_3_6", "northeast", 0, 3, 1);
    add_exit(FOREST + "f_3_5", "east", 0, 3, 1);
    add_exit(FOREST + "f_3_4", "southeast", 0, 3, 1);
    add_exit(FOREST + "f_2_4", "south", 0, 3, 1);
    add_exit(FOREST + "f_1_4", "southwest", 0, 3, 1);
}

