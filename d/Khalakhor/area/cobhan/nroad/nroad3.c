/* File:          /d/Khalakhor/cobhan/nroad/nroad3.c
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

inherit CSTD + "nroad_base";

public void
reset_nroad_room()
{
}

public void
create_nroad_room()
{
    set_up_nroad();
    set_long("@@my_long");
    add_my_desc("End of the north road. \n");

    add_exit(NROAD + "null", "north", "@@block_road", 2);
    add_exit(NROAD + "nroad2", "south", 0, 2);
}

