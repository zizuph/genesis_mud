/* File:          /d/Khalakhor/se_speir/forest/room/f_29_1.c
 * Creator:       Teth
 * Date:          March 26, 1998
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
    add_my_desc("Edge forest rests to the south, while riverbank " +
      "forest exists to the east and north. More of the continuous " +
      "forest sits to west and northwest.\n");
    add_item("riverbank forest","The riverbank forest is different " +
      "in composition from the rest of the forest.\n");
    add_item("plains","The plains cannot be seen from here.\n");
    add_item("edge forest","It is the bushy terrain bordering " +
      "the forest and the plains.\n");
    add_item("river","The river cannot be seen from here.\n");
    add_item("riverbank","The riverbank cannot be seen from here, " +
      "although you can walk toward it.\n");

    add_exit(FROOM + "f_28_1", "west", 0, 2, 1);
    add_exit(FROOM + "f_28_2", "northwest", 0, 2, 1);
    add_exit(FROOM + "rb_29_2", "north", "@@enter_riverbank", 3, 1);
    add_exit(FROOM + "r_30_2", "northeast", "@@block_river", 1, 1);
    add_exit(FROOM + "rb_30_1", "east", "@@enter_riverbank", 3, 1);
    add_exit(FROOM + "b_30_0", "southeast", "@@enter_bush", 2, 1);
    add_exit(FROOM + "b_29_0", "south", "@@enter_bush", 2, 1);
    add_exit(FROOM + "b_28_0", "southwest", "@@enter_bush", 2, 1);
}

