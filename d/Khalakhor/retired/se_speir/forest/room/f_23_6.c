/* File:          /d/Khalakhor/se_speir/forest/room/f_23_6.c
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
    add_my_desc("A path can be reached by venturing west. " +
      "A small village rests to the north, while more forest exists " +
      "in all other directions.\n");
    add_item("path","It is the path which leads through the forest.\n");
    add_item(({"village","small village"}),"The small village " +
      "appears to be the settlement of the local lumberjacks.\n");
    add_item("settlement","It rests to the north.\n");

    add_exit(FROOM + "p_22_6", "west", "@@enter_path", 4, 1);
    add_exit(FROOM + "v_22_7", "northwest", "@@enter_village", 4, 1);
    add_exit(FROOM + "v_23_7", "north", "@@enter_village", 4, 1);
    add_exit(FROOM + "f_24_7", "northeast", 0, 4, 1);
    add_exit(FROOM + "f_24_6", "east", 0, 4, 1);
    add_exit(FROOM + "f_24_5", "southeast", 0, 4, 1);
    add_exit(FROOM + "f_23_5", "south", 0, 4, 1);
    add_exit(FROOM + "f_22_5", "southwest", 0, 4, 1);
}

