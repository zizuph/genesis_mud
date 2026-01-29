/* File:          /d/Khalakhor/se_speir/forest/room/f_18_3.c
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
      "by going southeast.\n");
    add_item("stream","The stream can be entered and examined " +
      "more closely by stepping into it.\n");
    add_item("path","It is the path which leads through the forest.\n");

    add_exit(FROOM + "s_17_3", "west", "@@enter_stream", 4, 1);
    add_exit(FROOM + "f_17_4", "northwest", "@@cross_stream", 4, 1);
    add_exit(FROOM + "s_18_4", "north", "@@enter_stream", 4, 1);
    add_exit(FROOM + "f_19_4", "northeast", 0, 4, 1);
    add_exit(FROOM + "p_19_3", "east", "@@enter_path", 4, 1);
    add_exit(FROOM + "f_19_2", "southeast", "@@cross_path", 4 ,1);
    add_exit(FROOM + "p_18_2", "south", "@@enter_path", 4, 1);
    add_exit(FROOM + "f_17_2", "southwest", 0, 4, 1);
}

