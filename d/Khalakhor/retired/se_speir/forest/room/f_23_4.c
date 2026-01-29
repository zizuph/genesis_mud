/* File:          /d/Khalakhor/se_speir/forest/room/f_23_4.c
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
    set_logged(1);
    set_up_forest();
    set_long("@@my_long");
    add_my_desc("The surrounding forest continues in all " +
      "directions.\n");

    add_exit(FROOM + "f_22_4", "west", 0, 2, 1);
    add_exit(FROOM + "f_22_5", "northwest", 0, 2, 1);
    add_exit(FROOM + "f_23_5", "north", 0, 2, 1);
    add_exit(FROOM + "f_24_5", "northeast", 0, 2, 1);
    add_exit(FROOM + "f_24_4", "east", 0, 2, 1);
    add_exit(FROOM + "f_24_3", "southeast", 0, 2, 1);
    add_exit(FROOM + "f_23_3", "south", 0, 2, 1);
    add_exit(FROOM + "f_22_3", "southwest", 0, 2, 1);
}

