/* File:          /d/Khalakhor/se_speir/forest/room/f_22_2.c
 * Creator:       Teth
 * Date:          February 17, 1998
 * Modifications:
 * Purpose:       This is a forest room in the area.
 * Related Files: /d/Khalakhor/se_speir/forest/
 * Comments:
 */

#pragma save_binary
#pragma strict_types

#include "../forest.h"

inherit FSTD + "forest_base";

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
    add_my_desc("The surrounding forest continues in all " +
      "directions.\n");

    add_exit(FROOM + "f_21_2", "west", 0, 2, 1);
    add_exit(FROOM + "f_21_3", "northwest", 0, 2, 1);
    add_exit(FROOM + "f_22_3", "north", 0, 2, 1);
    add_exit(FROOM + "f_23_3", "northeast", 0, 2, 1);
    add_exit(FROOM + "f_23_2", "east", 0, 2, 1);
    add_exit(FROOM + "f_23_1", "southeast", 0, 2, 1);
    add_exit(FROOM + "f_22_1", "south", 0, 2, 1);
    add_exit(FROOM + "f_21_1", "southwest", 0, 2, 1);
}

