/* File:          /d/Khalakhor/se_speir/forest/room/f_20_3.c
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
    set_logged(3);
    set_up_forest();
    set_long("@@my_long");
    add_my_desc("A path can be reached by venturing west or north. " +
      "More forest exists in other directions, including a portion " +
      "which can be reached by crossing the path to the northwest.\n");
    add_item("path","It is the path which leads through the forest.\n");

    add_exit(FROOM + "p_19_3", "west", "@@enter_path", 4, 1);
    add_exit(FROOM + "f_19_4", "northwest", "@@cross_path", 4, 1);
    add_exit(FROOM + "p_20_4", "north", "@@enter_path", 4, 1);
    add_exit(FROOM + "f_21_4", "northeast", 0, 4, 1);
    add_exit(FROOM + "f_21_3", "east", 0, 4, 1);
    add_exit(FROOM + "f_21_2", "southeast", 0, 4, 1);
    add_exit(FROOM + "f_20_2", "south", 0, 4, 1);
    add_exit(FROOM + "f_19_2", "southwest", 0, 4, 1);
}

