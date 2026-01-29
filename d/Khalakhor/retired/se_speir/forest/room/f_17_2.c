/* File:          /d/Khalakhor/se_speir/forest/room/f_17_2.c
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
    add_my_desc("A stream babbles to the north. More forest extends " +
      "to the northeast and west. A path can be reached by venturing " +
      "south, southwest or east, or it can be crossed by travelling " +
      "southeast.\n");
    add_item("riverbank forest","The riverbank forest is different " +
      "in composition from the rest of the forest.\n");
    add_item("path","It is the path which leads through the forest.\n");
    add_item("stream","It appears to be a refreshing stream. To " +
      "explore it further, you'd have to travel north.\n");

    add_exit(FROOM + "f_16_2", "west", 0, 4, 1);
    add_exit(FROOM + "f_16_3", "northwest", "@@block_forest", 4, 1);
    add_exit(FROOM + "s_17_3", "north", "@@enter_stream", 4, 1);
    add_exit(FROOM + "f_18_3", "northeast", 0, 4, 1);
    add_exit(FROOM + "p_18_2", "east", "@@enter_path", 4, 1);
    add_exit(FROOM + "f_18_1", "southeast", "@@cross_path", 4, 1);
    add_exit(FROOM + "p_17_1", "south", "@@enter_path", 4, 1);
    add_exit(FROOM + "p_16_1", "southwest", "@@enter_path", 4, 1);
}

