/* File:          /d/Khalakhor/se_speir/forest/room/f_21_1.c
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
    add_my_desc("South, edge forest leads out to the plains, while " +
      "the forest proper stretches out in all other directions \n");
    add_item("plains","The plains cannot be seen from here.\n");
    add_item("edge forest","It is the bushy terrain bordering " +
      "the forest and the plains.\n");

    add_exit(FROOM + "f_20_1", "west", 0, 2, 1);
    add_exit(FROOM + "f_20_2", "northwest", 0, 2, 1);
    add_exit(FROOM + "f_21_2", "north", 0, 2, 1);
    add_exit(FROOM + "f_22_2", "northeast", 0, 2, 1);
    add_exit(FROOM + "f_22_1", "east", 0, 2, 1);
    add_exit(FROOM + "b_22_0", "southeast", "@@enter_bush", 2, 1);
    add_exit(FROOM + "b_21_0", "south", "@@enter_bush", 2, 1);
    add_exit(FROOM + "b_20_0", "southwest", "@@enter bush", 2, 1);
}

