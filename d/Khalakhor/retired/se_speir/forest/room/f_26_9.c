/* File:          /d/Khalakhor/se_speir/forest/room/f_26_9.c
 * Creator:       Teth
 * Date:          March 5, 1998
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
    set_logged(1);
    set_up_forest();
    set_long("@@my_long");
    add_my_desc("Riverbank forest rests to the north, west, and " +
      "southeast, while more of the forest proper stretches in " +
      "most other directions.\n");
    add_item("river","The river cannot be seen from this vantage point.\n");
    add_item("riverbank forest","The riverbank forest is different " +
      "in composition from the rest of the forest.\n");

    add_exit(FROOM + "rb_25_9", "west", "@@enter_riverbank", 2, 1);
    add_exit(FROOM + "r_25_10", "northwest", "@@block_river", 2, 1);
    add_exit(FROOM + "rb_26_10", "north", "@@enter_riverbank", 2, 1);
    add_exit(FROOM + "f_27_10", "northeast", 0, 2, 1);
    add_exit(FROOM + "f_27_9", "east", 0, 2, 1);
    add_exit(FROOM + "rb_27_8", "southeast", "@@enter_riverbank", 2, 1);
    add_exit(FROOM + "f_26_8", "south", 0, 2, 1);
    add_exit(FROOM + "f_25_8", "southwest", 0, 2, 1);
}

