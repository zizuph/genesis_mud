/* File:          /d/Khalakhor/se_speir/forest/room/f_21_6.c
 * Creator:       Teth
 * Date:          March 4, 1998
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
    add_my_desc("A stream flows to the west, while more of " +
      "this forest extends southwest. A path can be reached by " +
      "venturing south or east, or crossed by travelling " +
      "southeast. A small village rests to the north.\n");
    add_item("stream","The stream slowly flows through the forest. " +
      "A closer examination is possible by wading into it.\n");
    add_item("path","It is the path which leads through the forest.\n");
    add_item(({"village","small village"}),"The small village " +
      "appears to be the settlement of the local lumberjacks.\n");
    add_item("settlement","It rests to the north.\n");

    add_exit(FROOM + "s_20_6", "west", "@@enter_stream", 4, 1);
    add_exit(FROOM + "s_20_7", "northwest", "@@enter_stream", 4, 1);
    add_exit(FROOM + "v_21_7", "north", "@@enter_village", 4, 1);
    add_exit(FROOM + "v_22_7", "northeast", "@@enter_village", 4, 1);
    add_exit(FROOM + "p_22_6", "east", "@@enter_path", 4, 1);
    add_exit(FROOM + "p_21_5", "south", "@@enter_path", 4, 1);
    add_exit(FROOM + "f_20_5", "southwest", 0, 4, 1);
    add_exit(FROOM + "f_22_5", "southeast", "@@cross_path", 4, 1);
}

