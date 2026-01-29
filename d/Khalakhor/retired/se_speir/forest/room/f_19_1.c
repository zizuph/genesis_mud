/* File:          /d/Khalakhor/se_speir/forest/room/f_19_1.c
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
    set_logged(2);
    set_up_forest();
    set_long("@@my_long");
    add_my_desc("A path can be reached by venturing northwest. " +
      "Forest extends in all other directions, although to the south " +
      "it is edge forest.\n");
    add_item("path","It is the path which leads through the forest.\n");
    add_item("edge forest","The edge forest exists where the forest " +
      "meets the plains.\n");
    add_item("plains","Judging by the direction of the edge forest, " +
      "the unseen plains must be to the south.\n");

    add_exit(FROOM + "f_18_1", "west", 0, 3, 1);
    add_exit(FROOM + "p_18_2", "northwest", "@@enter_path", 3, 1);
    add_exit(FROOM + "f_19_2", "north", 0, 3, 1);
    add_exit(FROOM + "f_20_2", "northeast", 0, 3, 1);
    add_exit(FROOM + "f_20_1", "east", 0, 3, 1);
    add_exit(FROOM + "b_20_0", "southeast", "@@enter_bush", 3, 1);
    add_exit(FROOM + "b_19_0", "south", "@@enter_bush", 3, 1);
    add_exit(FROOM + "b_18_0", "southwest", "@@enter_bush", 3, 1);
}

