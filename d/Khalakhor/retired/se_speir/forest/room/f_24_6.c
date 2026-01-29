/* File:          /d/Khalakhor/se_speir/forest/room/f_24_6.c
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
    add_my_desc("A village can be reached by venturing northwest. " +
      "Forest extends in all other directions.\n");
    add_item("village","It is a small settlement within the " +
      "forest.\n");
    add_item(({"small settlement","settlement"}),"It is where " +
      "the local foresters live.\n"); 
    add_item("path","It is the path which leads through the forest.\n");

    add_exit(FROOM + "f_23_6", "west", 0, 4, 1);
    add_exit(FROOM + "v_23_7", "northwest", "@@enter_village", 4, 1);
    add_exit(FROOM + "f_24_7", "north", 0, 4, 1);
    add_exit(FROOM + "f_25_7", "northeast", 0, 4, 1);
    add_exit(FROOM + "f_25_6", "east", 0, 4, 1);
    add_exit(FROOM + "f_25_5", "southeast", 0, 4, 1);
    add_exit(FROOM + "f_24_5", "south", 0, 4, 1);
    add_exit(FROOM + "f_23_5", "southwest", 0, 4, 1);
}

