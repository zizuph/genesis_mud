/* File:          /d/Khalakhor/se_speir/forest/room/f_20_5.c
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
    add_my_desc("A stream flows to the north and west. " +
      "More forest extends to the northeast and southwest. A path " +
      "can be reached by venturing south or east, or crossed to the " +
      "southeast.\n");
    add_item("stream", "The stream babbles as it flows. It can " +
      "examined in more detail by wading into it.\n");
    add_item("path","It is the path which leads through the forest.\n");

    add_exit(FROOM + "s_19_5", "west", "@@enter_stream", 4, 1);
    add_exit(FROOM + "s_19_6", "northwest", "@@cross_stream", 4, 1);
    add_exit(FROOM + "s_20_6", "north", "@@enter_stream", 4, 1);
    add_exit(FROOM + "f_21_6", "northeast", 0, 4, 1);
    add_exit(FROOM + "p_21_5", "east", "@@enter_path", 4, 1);
    add_exit(FROOM + "f_21_4", "southeast", "@@cross_path", 4, 1);
    add_exit(FROOM + "p_20_4", "south", "@@enter_path", 4, 1);
    add_exit(FROOM + "f_19_4", "southwest", 0, 4, 1);
}

