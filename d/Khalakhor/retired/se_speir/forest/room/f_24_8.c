/* File:          /d/Khalakhor/se_speir/forest/room/f_24_8.c
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
    add_my_desc("A village can be reached by venturing southwest or " +
      "west. Forest extends in most other directions, although it is " +
      "riverbank forest to the north and northeast.\n");
    add_item("village","It is a small settlement within the " +
      "forest.\n");
    add_item(({"small settlement","settlement"}),"It is where " +
      "the local foresters live.\n"); 
    add_item("river","The river cannot be seen from this vantage point.\n");
    add_item("riverbank forest","The riverbank forest is different " +
      "in composition from the rest of the forest.\n");
    add_item("slope","The steep slope to the northwest is too difficult " +
      "to descend.\n");

    add_exit(FROOM + "v_23_8", "west", "@@enter_village", 4, 1);
    add_exit(FROOM + "r_23_9", "northwest", "@@block_river", 4, 1);
    add_exit(FROOM + "rb_24_9", "north", "@@enter_riverbank", 4, 1);
    add_exit(FROOM + "rb_25_9", "northeast", "@@enter_riverbank", 4, 1);
    add_exit(FROOM + "f_25_8", "east", 0, 4, 1);
    add_exit(FROOM + "f_25_7", "southeast", 0, 4, 1);
    add_exit(FROOM + "f_24_7", "south", 0, 4, 1);
    add_exit(FROOM + "v_23_7", "southwest", "@@enter_village", 4, 1);
}

