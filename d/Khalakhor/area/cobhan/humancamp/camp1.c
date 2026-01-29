/* File:          /d/Khalakhor/cobhan/humancamp/camp1.c
 * Creator:       Teth
 * Date:          Dec 25 2001
 * Modifications:
 * Purpose:       This is a human camp room in the area.
 * Related Files: /d/Khalakhor/cobhan/
 * Comments:
 */

#pragma save_binary
#pragma strict_types

#include "../local.h"

inherit CSTD + "humancamp_base";

public void
reset_humancamp_room()
{
}

public void
create_humancamp_room()
{
    set_up_humancamp();
    set_long("@@my_long");
    add_my_desc("Entrance to human camp. West to road. \n");

    add_exit(SROAD + "sroad3", "west", "@@enter_road", 2);
    add_exit(HUMANCAMP + "camp2", "northeast", 0, 2);
    add_exit(HUMANCAMP + "camp4", "east", 0, 2);
    add_exit(HUMANCAMP + "camp5", "southeast", 0, 2);
}

