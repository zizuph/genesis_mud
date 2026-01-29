/* File:          /d/Khalakhor/cobhan/ironmine/mine1.c
 * Creator:       Teth
 * Date:          Dec 26 2001
 * Modifications:
 * Purpose:       This is a mine room in the area.
 * Related Files: /d/Khalakhor/cobhan/
 * Comments:
 */

#pragma save_binary
#pragma strict_types

#include "../local.h"

inherit CSTD + "ironmine_base";

public void
reset_ironmine_room()
{
}

public void
create_ironmine_room()
{
    set_up_ironmine();
    set_long("@@my_long");

    add_my_desc("A mine. \n");

    add_exit(IRONMINE + "null", "west", "@@block_mine", 2);
    add_exit(SROAD + "sroad6", "east", "@@enter_road", 2);
}

