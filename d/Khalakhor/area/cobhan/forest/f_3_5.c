/* File:          /d/Khalakhor/cobhan/forest/f_3_5.c
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
    add_my_desc("Deep forest. Base of ruined tower arching over stream. " +
      "Rubble. \n");

    add_exit(FOREST + "f_2_5", "west", 0, 3, 1);
    add_exit(FOREST + "f_2_6", "northwest", 0, 3, 1);
    add_exit(FOREST + "f_3_6", "north", 0, 3, 1);
    add_exit(FOREST + "f_4_6", "northeast", 0, 3, 1);
    add_exit(FOREST + "f_4_5", "east", 0, 3, 1);
    add_exit(FOREST + "f_4_4", "southeast", 0, 3, 1);
    add_exit(FOREST + "f_3_4", "south", 0, 3, 1);
    add_exit(FOREST + "f_2_4", "southwest", 0, 3, 1);
}

