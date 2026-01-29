/* File:          /d/Khalakhor/cobhan/ngate/ngate7.c
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
    add_my_desc("The north gate. \n");

    add_exit(NGATE + "ngate3", "southwest");
}

