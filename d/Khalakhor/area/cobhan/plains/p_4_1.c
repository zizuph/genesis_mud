/* File:          /d/Khalakhor/cobhan/plains/p_4_1.c
 * Creator:       Teth
 * Date:          Dec 25 2001
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
    add_my_desc("Plains. \n");

    add_exit(PLAINS + "p_3_1", "west", 0, 2, 1);
    add_exit(PLAINS + "p_3_2", "northwest", 0, 2, 1);
    add_exit(PLAINS + "p_4_2", "north", 0, 2, 1);
    add_exit(PLAINS + "p_5_2", "northeast", 0, 2, 1);
    add_exit(PLAINS + "null", "east", "@@block_mountain", 2, 1);
    add_exit(PLAINS + "null", "southeast", "@@block_mountain", 2, 1);
    add_exit(PLAINS + "null", "south", "@@block_mountain", 2, 1);
    add_exit(SGATE + "sgate1", "southwest", "@@enter_sgate", 2, 1);
}

