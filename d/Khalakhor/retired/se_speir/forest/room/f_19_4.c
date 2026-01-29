/* File:          /d/Khalakhor/se_speir/forest/room/f_19_4.c
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
      "can be reached by venturing south or east, or crossed " +
      "to the southeast.\n");
    add_item("stream","The stream can be examined further by " +
      "wading into it.\n");
    add_item("path","It is the path which leads through the forest.\n");

    add_exit(FROOM + "s_18_4", "west", "@@enter_stream", 4, 1);
    add_exit(FROOM + "s_18_5", "northwest", "@@cross_stream", 4, 1);
    add_exit(FROOM + "s_19_5", "north", "@@enter_stream", 4, 1);
    add_exit(FROOM + "f_20_5", "northeast", 0, 4, 1);
    add_exit(FROOM + "p_20_4", "east", "@@enter_path", 4, 1);
    add_exit(FROOM + "f_20_3", "southeast", "@@cross_path", 4, 1);
    add_exit(FROOM + "p_19_3", "south", "@@enter_path", 4, 1);
    add_exit(FROOM + "f_18_3", "southwest", 0, 4, 1);
}

