/* File:          /d/Khalakhor/se_speir/forest/room/f_27_3.c
 * Creator:       Teth
 * Date:          March 30, 1998
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
    add_my_desc("The forest continues in all directions, although it "+
      "it is riverbank forest to the northeast.\n");
    add_item("river","The river cannot be seen from this vantage point.\n");
    add_item("riverbank forest","The riverbank forest is different " +
      "in composition from the rest of the forest.\n");

    add_exit(FROOM + "f_26_3", "west", 0, 2, 1);
    add_exit(FROOM + "f_26_4", "northwest", 0, 2, 1);
    add_exit(FROOM + "f_27_4", "north", 0, 2, 1);
    add_exit(FROOM + "rb_28_4", "northeast", "@@enter_riverbank", 2, 1);
    add_exit(FROOM + "f_28_3", "east", 0, 2, 1);
    add_exit(FROOM + "f_28_2", "southeast", 0, 2, 1);
    add_exit(FROOM + "f_27_2", "south", 0, 2, 1);
    add_exit(FROOM + "f_26_2", "southwest", 0, 2, 1);
}

