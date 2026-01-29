/* File:          /d/Khalakhor/cobhan/sroad/sroad7.c
 * Creator:       Teth
 * Date:          Dec 26 2001
 * Modifications:
 * Purpose:       This is a road room in the area.
 * Related Files: /d/Khalakhor/cobhan/
 * Comments:
 */

#pragma save_binary
#pragma strict_types

#include "../local.h"

inherit CSTD + "sroad_base";

public void
reset_sroad_room()
{
}

public void
create_sroad_room()
{
    set_up_sroad();
    set_long("@@my_long");
    add_my_desc("End of the road - blocked to the south. \n");

    add_exit(SROAD + "sroad6", "north", 0, 2);
    add_exit(SROAD + "null", "south", "@@block_sroad", 2);
}

