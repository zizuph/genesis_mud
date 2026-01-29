/* File:          /d/Khalakhor/se_speir/forest/room/p_14_1.c
 * Creator:       Teth
 * Date:          April 17, 1998
 * Modifications:
 * Purpose:       This is a path room in the area.
 * Related Files: /d/Khalakhor/se_speir/forest/
 * Comments:
 */

#pragma save_binary
#pragma strict_types

#include "../forest.h"

inherit FSTD + "path_base";

public void
reset_forest_room()
{
}

public void
create_forest_room()
{
    set_long("@@my_long");
    add_my_desc("The path continues east and south. Plains can " +
       "entered to the southwest, and bush to the southeast.\n");
    add_item("plains","The plains to the southwest are vast, " +
       "and worthy of exploration.\n");
    add_item("bush","The bush to the southeast is the border between " +
       "the forest and the eastern plains.\n");
    add_item(({"east plains","eastern plains","southwest plains"}),
       "The plains in all directions are expansive.\n");
    add_item("forest","The forest to the east is Coille Cagairean.\n");

    add_exit(FROOM + "p_15_1", "east", "@@continue_path", 0);
    add_exit(FROOM + "b_15_0", "southeast", "@@enter_bush", 0, 1);
    add_exit(PROOM + "plains_13_1", "south", 0, 0);
    add_exit(PROOM + "plains_12_1", "southwest", "@@enter_plains", 0, 1);
}

