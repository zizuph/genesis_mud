/* File:          /d/Khalakhor/se_speir/forest/room/f_26_8.c
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
    add_my_desc("Riverbank forest rests to the east and also to the " +
      "northwest, while more of the forest proper stretches in " +
      "all other directions.\n");
    add_item("river","The river cannot be seen from this vantage point.\n");
    add_item("riverbank forest","The riverbank forest is different " +
      "in composition from the rest of the forest.\n");

    add_exit(FROOM + "f_25_8", "west", 0, 2, 1);
    add_exit(FROOM + "rb_25_9", "northwest", "@@enter_riverbank", 2, 1);
    add_exit(FROOM + "f_26_9", "north", 0, 2, 1);
    add_exit(FROOM + "f_27_9", "northeast", 0, 2, 1);
    add_exit(FROOM + "rb_27_8", "east", "@@enter_riverbank", 2, 1);
    add_exit(FROOM + "f_27_7", "southeast", 0, 2, 1);
    add_exit(FROOM + "f_26_7", "south", 0, 2, 1);
    add_exit(FROOM + "f_25_7", "southwest", 0, 2, 1);
}

