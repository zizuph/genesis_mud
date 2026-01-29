/* File:          /d/Khalakhor/se_speir/forest/room/f_25_1.c
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

    add_exit(FROOM + "f_24_1", "west", 0, 2, 1);
    add_exit(FROOM + "f_24_2", "northwest", 0, 2, 1);
    add_exit(FROOM + "f_25_2", "north", 0, 2, 1);
    add_exit(FROOM + "f_26_2", "northeast", 0, 2, 1);
    add_exit(FROOM + "f_26_1", "east", 0, 2, 1);
    add_exit(FROOM + "b_26_0", "southeast", "@@enter_bush", 2, 1);
    add_exit(FROOM + "b_25_0", "south", "@@enter_bush", 2, 1);
    add_exit(FROOM + "b_24_0", "southwest", "@@enter_bush", 2, 1);
}

