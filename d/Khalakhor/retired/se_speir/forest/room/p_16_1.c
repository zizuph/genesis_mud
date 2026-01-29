/* File:          /d/Khalakhor/se_speir/forest/room/p_16_1.c
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
    add_my_desc("The path continues east and west. Bush rests to " +
       "the south.\n");
    add_item("bush","The bush to the south is the border between " +
       "the forest and the eastern plains.\n");
    add_item(({"east plains","eastern plains"}),
       "The plains are expansive and worthy of exploration.\n");
    add_item("forest","The forest to the east is Coille Cagairean.\n");

    add_exit(FROOM + "p_15_1", "west" ,"@@continue_path", 0);
    add_exit(FROOM + "f_16_2", "north", "@@enter_forest", 3, 1);
    add_exit(FROOM + "f_17_2" ,"northeast", "@@enter_forest", 3, 1);
    add_exit(FROOM + "p_17_1", "east", "@@continue_path", 0);
    add_exit(FROOM + "b_17_0", "southeast", "@@enter_bush", 0, 1);
    add_exit(FROOM + "b_16_0", "south", "@@enter_bush", 0, 1);
    add_exit(FROOM + "b_15_0", "southwest", "@@enter_bush", 0, 1);
}

