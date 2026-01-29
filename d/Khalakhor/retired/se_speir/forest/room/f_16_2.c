/* File:          /d/Khalakhor/se_speir/forest/room/f_16_2.c
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
    set_logged(2);
    set_up_forest();
    set_long("@@my_long");
    add_my_desc("A stream rests to the northeast, while more " +
      "forest extends to the northwest and east. A path " +
      "leading east and west exists to the south.\n");
    add_item("stream","A gentle stream, it winds its way through " +
      "the forest. You'd need to venture northeast to examine it " +
      "in more detail.\n");
    add_item("path","It is the path which leads through the forest.\n");

    add_exit(FROOM + "f_15_2", "west", "@@block_forest", 3, 1);
    add_exit(FROOM + "f_15_3", "northwest", "@@block_forest", 3, 1);
    add_exit(FROOM + "f_16_3", "north", "@@block_forest", 3, 1);
    add_exit(FROOM + "s_17_3", "northeast", "@@enter_stream", 3, 1);
    add_exit(FROOM + "f_17_2", "east", 0, 3, 1);
    add_exit(FROOM + "p_17_1", "southeast", "@@enter_path", 3, 1);
    add_exit(FROOM + "p_16_1", "south", "@@enter_path", 3, 1);
    add_exit(FROOM + "p_15_1", "southwest", "@@enter_path", 3, 1);
}

