/* File:          /d/Khalakhor/se_speir/forest/room/f_26_7.c
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
    set_logged(1);
    set_up_forest();
    set_long("@@my_long");
    add_my_desc("Riverbank forest rests to the northeast, while more " +
      "of the forest proper stretches in all other directions.\n");
    add_item("river","The river cannot be seen from this vantage point.\n");
    add_item("riverbank forest","The riverbank forest is different " +
      "in composition from the rest of the forest.\n");

    add_exit(FROOM + "f_25_7", "west", 0, 2, 1);
    add_exit(FROOM + "f_25_8", "northwest", 0, 2, 1);
    add_exit(FROOM + "f_26_8", "north", 0, 2, 1);
    add_exit(FROOM + "rb_27_8", "northeast", "@@enter_riverbank", 2, 1);
    add_exit(FROOM + "f_27_7", "east", 0, 2, 1);
    add_exit(FROOM + "f_27_6", "southeast", 0, 2, 1);
    add_exit(FROOM + "f_26_6", "south", 0, 2, 1);
    add_exit(FROOM + "f_25_6", "southwest", 0, 2, 1);
}

