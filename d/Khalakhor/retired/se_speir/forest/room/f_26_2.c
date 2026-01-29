/* File:          /d/Khalakhor/se_speir/forest/room/f_26_2.c
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

    add_exit(FROOM + "f_25_2", "west", 0, 2, 1);
    add_exit(FROOM + "f_25_3", "northwest", 0, 2, 1);
    add_exit(FROOM + "f_26_3", "north", 0, 2, 1);
    add_exit(FROOM + "f_27_3", "northeast", 0, 2, 1);
    add_exit(FROOM + "f_27_2", "east", 0, 2, 1);
    add_exit(FROOM + "f_27_1", "southeast", 0, 2, 1);
    add_exit(FROOM + "f_26_1", "south", 0, 2, 1);
    add_exit(FROOM + "f_25_1", "southwest", 0, 2, 1);
}

