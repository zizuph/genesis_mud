/* File:          /d/Khalakhor/cobhan/ngate/ngate1.c
 * Creator:       Teth
 * Date:          Dec 26 2001
 * Modifications:
 * Purpose:       This is a gate room in the area.
 * Related Files: /d/Khalakhor/cobhan/
 * Comments:
 */

#pragma save_binary
#pragma strict_types

#include "../local.h"

inherit CSTD + "ngate_base";

public void
reset_ngate_room()
{
}

public void
create_ngate_room()
{
    set_up_ngate();
    set_long("@@my_long");
    add_my_desc("North to road. South to plains. \n");

    add_exit(NGATE + "ngate2", "west");
    add_exit(NROAD + "nroad1", "north", "@@enter_road", 2);
    add_exit(NGATE + "ngate3", "east");
    add_exit(PLAINS + "p_6_12", "southeast", "@@enter_plains", 2, 1);
    add_exit(PLAINS + "p_5_12", "south", "@@enter_plains", 2);
    add_exit(PLAINS + "p_4_12", "southwest", "@@enter_plains", 2, 1);
}

