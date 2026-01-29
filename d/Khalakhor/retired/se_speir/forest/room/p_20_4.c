/* File:          /d/Khalakhor/se_speir/forest/room/p_20_4.c
 * Creator:       Teth
 * Date:          April 18, 1998
 * Modifications:
 * Purpose:       This is a path room in the area.
 * Related Files: /d/Khalakhor/se_speir/forest/
 * Comments:
 */

#pragma save_binary
#pragma strict_types

#include "../forest.h"

inherit FSTD + "path_base";

public void
reset_forest_room()
{
}

public void
create_forest_room()
{
    set_long("@@my_long");
    add_my_desc("The path continues northeast and southwest. " +
       "The forest can be seen in all other directions.\n");
    add_item("forest","The surrounding forest is Coille Cagairean. " +
       "It beckons you to explore it further.\n");

    add_exit(FROOM + "f_19_4", "west" ,"@@enter_forest", 3, 1);
    add_exit(FROOM + "s_19_5", "northwest", "@@enter_stream", 3, 1);
    add_exit(FROOM + "f_20_5", "north", "@@enter_forest", 3, 1);
    add_exit(FROOM + "p_21_5" ,"northeast", "@@continue_path", 0);
    add_exit(FROOM + "f_21_4", "east", "@@enter_forest", 3, 1);
    add_exit(FROOM + "f_21_3", "southeast", "@@enter_forest", 3, 1);
    add_exit(FROOM + "f_20_3", "south", "@@enter_forest", 3, 1);
    add_exit(FROOM + "p_19_3", "southwest", "@@continue_path", 0);
}

