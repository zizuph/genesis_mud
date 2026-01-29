/* File:          /d/Khalakhor/se_speir/forest/room/f_28_5.c
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
    add_my_desc("The forest continues to the west directions. " +
      "Riverbank forest can be reached by venturing most other " +
      "directions.\n");
    add_item("river","The river cannot be seen from this vantage point.\n");
    add_item("riverbank forest","The riverbank forest is different " +
      "in composition from the rest of the forest.\n");
    add_item("slope","Steep slopes prevent passage in some directions.\n");

    add_exit(FROOM + "f_27_5", "west", 0, 2, 1);
    add_exit(FROOM + "f_27_6", "northwest", 0, 2, 1);
    add_exit(FROOM + "rb_28_6", "north", "@@enter_riverbank", 2, 1);
    add_exit(FROOM + "r_29_6", "northeast", "@@block_river", 2, 1);
    add_exit(FROOM + "rb_29_5", "east", "@@enter_riverbank", 2, 1);
    add_exit(FROOM + "r_29_4", "southeast", "@@block_river", 2, 1);
    add_exit(FROOM + "rb_28_4", "south", "@@enter_riverbank", 2, 1);
    add_exit(FROOM + "f_28_4", "southwest", 0, 2, 1);
}

