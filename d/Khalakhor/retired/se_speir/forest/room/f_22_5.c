/* File:          /d/Khalakhor/se_speir/forest/room/f_22_5.c
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
      "More forest exists in other directions.\n");
    add_item("path","It is the path which leads through the forest.\n");

    add_exit(FROOM + "p_21_5", "west", "@@enter_path", 4, 1);
    add_exit(FROOM + "f_21_6", "northwest", "@@cross_path", 4, 1);
    add_exit(FROOM + "p_22_6", "north", "@@enter_path", 4, 1);
    add_exit(FROOM + "f_23_6", "northeast", 0, 4, 1);
    add_exit(FROOM + "f_23_5", "east", 0, 4, 1);
    add_exit(FROOM + "f_23_4", "southeast", 0, 4, 1);
    add_exit(FROOM + "f_22_4", "south", 0, 4, 1);
    add_exit(FROOM + "f_21_4", "southwest", 0, 4, 1);
}

