/* File:          /d/Khalakhor/se_speir/forest/room/f_26_6.c
 * Creator:       Teth
 * Date:          February 25, 1998
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
    set_logged(0);
    set_up_forest();
    set_long("@@my_long");
    add_my_desc("The surrounding forest continues in all " +
      "directions.\n");

    add_exit(FROOM + "f_25_6", "west", 0, 2, 1);
    add_exit(FROOM + "f_25_7", "northwest", 0, 2, 1);
    add_exit(FROOM + "f_26_7", "north", 0, 2, 1);
    add_exit(FROOM + "f_27_7", "northeast", 0, 2, 1);
    add_exit(FROOM + "f_27_6", "east", 0, 2, 1);
    add_exit(FROOM + "f_27_5", "southeast", 0, 2, 1);
    add_exit(FROOM + "f_26_5", "south", 0, 2, 1);
    add_exit(FROOM + "f_25_5", "southwest", 0, 2, 1);
}

