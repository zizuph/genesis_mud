/* File:          /d/Khalakhor/cobhan/sgate/sgate1.c
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

inherit CSTD + "sgate_base";

public void
reset_sgate_room()
{
}

public void
create_sgate_room()
{
    set_up_sgate();
    set_long("@@my_long");
    add_my_desc("The main south gate. Needs to act as a real gate. \n");

    add_exit(SGATE + "sgate2", "west");
    add_exit(PLAINS + "p_2_1", "northwest", "@@enter_plains", 2, 1);
    add_exit(PLAINS + "p_3_1", "north", "@@enter_plains", 2);
    add_exit(PLAINS + "p_4_1", "northeast", "@@enter_plains", 2, 1);
    add_exit(SGATE + "sgate3", "east");
    add_exit(SROAD + "sroad1", "south", "@@enter_road", 2);
}

