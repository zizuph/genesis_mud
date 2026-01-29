/* File:          /d/Khalakhor/se_speir/forest/room/f_27_6.c
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
      "it is riverbank forest to the east and northeast.\n");
    add_item("river","The river cannot be seen from this vantage point.\n");
    add_item("riverbank forest","The riverbank forest is different " +
      "in composition from the rest of the forest.\n");

    add_exit(FROOM + "f_26_6", "west", 0, 2, 1);
    add_exit(FROOM + "f_26_7", "northwest", 0, 2, 1);
    add_exit(FROOM + "f_27_7", "north", 0, 2, 1);
    add_exit(FROOM + "rb_28_7", "northeast", "@@enter_riverbank", 2, 1);
    add_exit(FROOM + "rb_28_6", "east", "@@enter_riverbank", 2, 1);
    add_exit(FROOM + "f_28_5", "southeast", 0, 2, 1);
    add_exit(FROOM + "f_27_5", "south", 0, 2, 1);
    add_exit(FROOM + "f_26_5", "southwest", 0, 2, 1);
}

