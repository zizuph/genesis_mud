/* File:          /d/Khalakhor/se_speir/forest/room/p_22_6.c
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
    add_my_desc("The path continues north into a village and southwest. " +
       "The forest can be seen in all other directions.\n");
    add_item("village","The village is most likely inhabited by " +
       "lumberjacks and their families, considering the setting.\n");
    add_item("forest","The surrounding forest is Coille Cagairean. " +
       "It beckons you to explore it further.\n");

    add_exit(FROOM + "f_21_6", "west" ,"@@enter_forest", 3, 1);
    add_exit(FROOM + "v_21_7", "northwest", "@@enter_village", 1, 1);
    add_exit(FROOM + "v_22_7", "north", "@@enter_village", 1, 1);
    add_exit(FROOM + "v_23_7" ,"northeast", "@@enter_village", 1, 1);
    add_exit(FROOM + "f_23_6", "east", "@@enter_forest", 3, 1);
    add_exit(FROOM + "f_23_5", "southeast", "@@enter_forest", 3, 1);
    add_exit(FROOM + "f_22_5", "south", "@@enter_forest", 3, 1);
    add_exit(FROOM + "p_21_5", "southwest", "@@continue_path", 0);
}

