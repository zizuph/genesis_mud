/* File:          /d/Khalakhor/cobhan/plains/p_4_12.c
 * Creator:       Teth
 * Date:          Dec 26 2001
 * Modifications:
 * Purpose:       This is a plains room in the area.
 * Related Files: /d/Khalakhor/cobhan/
 * Comments:
 */

#pragma save_binary
#pragma strict_types

#include "../local.h"

inherit CSTD + "plains_base";

public void
reset_plains_room()
{
}

public void
create_plains_room()
{
    set_up_plains();
    set_long("@@my_long");
    add_my_desc("Plains. Northeast to gate. \n");

    add_exit(PLAINS + "null", "west", "@@block_mountain", 2, 1);
    add_exit(PLAINS + "null", "northwest", "@@block_mountain", 2, 1);
    add_exit(PLAINS + "null", "north", "@@block_mountain", 2, 1);
    add_exit(NGATE + "ngate1", "northeast", "@@enter_ngate", 2, 1);
    add_exit(PLAINS + "p_5_12", "east", 0, 2, 1);
    add_exit(PLAINS + "p_5_11", "southeast", 0, 2, 1);
    add_exit(PLAINS + "p_4_11", "south", 0, 2, 1);
    add_exit(PLAINS + "null", "southwest", "@@block_mountain", 2, 1);
}

